/*
 * This is part of the fl library, a C++ Bayesian filtering library
 * (https://github.com/filtering-library)
 *
 * Copyright (c) 2015 Max Planck Society,
 * 				 Autonomous Motion Department,
 * 			     Institute for Intelligent Systems
 *
 * This Source Code Form is subject to the terms of the MIT License (MIT).
 * A copy of the license can be found in the LICENSE file distributed with this
 * source code.
 */

/**
 * \file discrete_distribution.hpp
 * \date 05/25/2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 */
#pragma once


#include <Eigen/Core>

#include <vector>

#include <fl/util/types.hpp>
#include <fl/util/traits.hpp>
#include <fl/util/assertions.hpp>
#include <fl/distribution/interface/moments.hpp>
#include <fl/distribution/interface/standard_gaussian_mapping.hpp>

namespace fl
{

template <typename VariateType, int Locations = Eigen::Dynamic>
class DiscreteDistribution
    : public Moment<typename FirstMomentOf<VariateType>::type>,
      public StandardNormalDistributionMap<VariateType, 1>
{
public:
    typedef Moment<typename FirstMomentOf<VariateType>::type>  MomentsInterface;
    typedef typename MomentsInterface::VariateType              Mean;
    typedef typename MomentsInterface::SecondMoment         Covariance;

    typedef Eigen::Array<Real,    Locations, 1> Function;
    typedef Eigen::Array<VariateType, Locations, 1> LocationArray;

    typedef StandardNormalDistributionMap<VariateType, 1> StdGaussianMapping;
    typedef typename StdGaussianMapping::StandardVariate StandardVariate;

public:
    /// constructor and destructor *********************************************
    explicit
    DiscreteDistribution(int size = MaxOf<Locations, 1>::value)
    {
        set_uniform(size);
    }

    virtual ~DiscreteDistribution() noexcept { }

    /// non-const functions ****************************************************

    // set ---------------------------------------------------------------------
    virtual void log_unnormalized_prob_mass(const Function& log_prob_mass)
    {
        // rescale for numeric stability
        log_prob_mass_ = log_prob_mass - log_prob_mass.maxCoeff();

        // copy to prob mass
        prob_mass_ = log_prob_mass_.exp();
        Real sum = prob_mass_.sum();

        // normalize
        prob_mass_ /= sum;
        log_prob_mass_ -= std::log(sum);

        // compute cdf
        cumul_distr_.resize(log_prob_mass_.size());

        cumul_distr_[0] = prob_mass_[0];
        for(int i = 1; i < cumul_distr_.size(); i++)
        {
            cumul_distr_[i] = cumul_distr_[i-1] + prob_mass_[i];
        }

        // resize locations
        locations_.resize(log_prob_mass_.size());
    }

    virtual void delta_log_prob_mass(const Function& delta)
    {
        log_unnormalized_prob_mass(log_prob_mass_ + delta);
    }

    virtual void set_uniform(int new_size = -1)
    {
        if (new_size == -1) new_size = size();

        log_unnormalized_prob_mass(Function::Zero(new_size));
    }

    virtual VariateType& location(int i)
    {
        return locations_[i];
    }

    template <typename Distribution>
    void from_distribution(const Distribution& distribution, const int& new_size)
    {
        // we first create a local array to sample to. this way, if this
        // is passed as an argument the locations and pmf are not overwritten
        // while sampling
        LocationArray new_locations(new_size);

        for(int i = 0; i < new_size; i++)
        {
            new_locations[i] = distribution.sample();
        }

        set_uniform(new_size);
        locations_ = new_locations;
    }



    /// const functions ********************************************************

    // sampling ----------------------------------------------------------------
    virtual VariateType map_standard_normal(const StandardVariate& gaussian_sample,
                                        int& index) const
    {
        StandardVariate scaled_sample = gaussian_sample / std::sqrt(2.0);
        StandardVariate uniform_sample = 0.5 * (1.0 + std::erf(scaled_sample));

        return map_standard_uniform(uniform_sample, index);
    }

    virtual VariateType map_standard_uniform(const StandardVariate& uniform_sample,
                                         int& index) const
    {
        index = 0;
        for (index = 0; index < cumul_distr_.size(); ++index)
        {
            if (cumul_distr_[index] >= uniform_sample) break;
        }

        return locations_[index];
    }

    using StdGaussianMapping::sample;

    virtual VariateType sample(int& index) const
    {
        return map_standard_normal(this->standard_gaussian_.sample(), index);
    }

    virtual VariateType map_standard_normal(const StandardVariate& gaussian_sample) const
    {
        int index;
        return map_standard_normal(gaussian_sample, index);
    }

    virtual VariateType map_standard_uniform(const StandardVariate& uniform_sample) const
    {
        int index;
        return map_standard_uniform(uniform_sample, index);
    }


    // get ---------------------------------------------------------------------
    virtual const VariateType& location(int i) const
    {
        return locations_[i];
    }

    virtual const LocationArray& locations() const
    {
        return locations_;
    }

    virtual Real log_prob_mass(const int& i) const
    {
        return log_prob_mass_(i);
    }

    virtual Function log_prob_mass() const
    {
        return log_prob_mass_;
    }

    virtual Real prob_mass(const int& i) const
    {
        return prob_mass_(i);
    }

    virtual Function prob_mass() const
    {
        return prob_mass_;
    }

    virtual int size() const
    {
        return locations_.size();
    }

    virtual int dimension() const
    {
        return locations_[0].rows();
    }


    // compute properties ------------------------------------------------------
    virtual const Mean& mean() const
    {
        mean_ = Mean::Zero(dimension());

        for(int i = 0; i < locations_.size(); i++)
        {
            mean_ += prob_mass(i) * locations_[i].template cast<Real>();
        }

        return mean_;
    }

    virtual const VariateType& max() const
    {
        int max_index;
        log_prob_mass_.maxCoeff(&max_index);

        return locations_(max_index);
    }



    virtual const Covariance& covariance() const
    {
        Mean mu = mean();
        covariance_ = Covariance::Zero(dimension(), dimension());
        for(int i = 0; i < locations_.size(); i++)
        {
            Mean delta = (locations_[i].template cast<Real>()-mu);
            covariance_ += prob_mass(i) * delta * delta.transpose();
        }

        return covariance_;
    }

    virtual Real entropy() const
    {
        return - log_prob_mass_.cwiseProduct(prob_mass_).sum();
    }

    // implements KL(p||u) where p is this distr, and u is the uniform distr
    virtual Real kl_given_uniform() const
    {
        return std::log(Real(size())) - entropy();
    }


protected:
    /// member variables *******************************************************
    LocationArray locations_;

    Function log_prob_mass_;
    Function prob_mass_;
    Function cumul_distr_;

    mutable Mean mean_;
    mutable Covariance covariance_;
};

}
