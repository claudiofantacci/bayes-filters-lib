/**
 * Copyright (C) 2015 Max Planck Society, Atonomous Motion Department, Institute for Intelligent Systems
 *
 * This Source Code Form is subject to the terms of the MIT License (MIT).
 * A copy of the license can be found in the LICENSETP file distributed with this source code.
 *
 *
 * Copyright (C) 2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

/**
 * \file standard_gaussian.hpp
 * \date May 2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 *
 * \file StandardNormalDistribution.h
 * \date July 2019
 * \author Claudio Fantacci (claudio.fantacci@gmail.com)
 */

#ifndef STANDARDNORMALDISTRIBUTION_H
#define STANDARDNORMALDISTRIBUTION_H


#include <BayesFilters/Distribution/Moments.h>
#include <BayesFilters/Distribution/Sampling.h>
#include <BayesFilters/type_traits.h>
#include <BayesFilters/utils.h>

#include <random>
#include <type_traits>

#include <Eigen/Dense>


namespace bfl
{

/**
 * \class StandardNormalDistribution
 * \ingroup distributions
 *
 * \brief Standard Normal Distribution (SND)
 *
 * The Standard Normal Distribution (SND) is a general purpose distribution representing a multi-variate \f${\cal N}(x; 0, 1.0)\f$.
 *
 * \tparam VariateType Random variate type used for sampling.
 */
template<typename VariateType>
class StandardNormalDistribution : public Sampling<VariateType>, public Moment<VariateType, typename DiagonalSecondMomentOf<VariateType>::type>
{
private:
    /**
     * The Standard Normal Distribution covariance type.
     */
    using CovarianceType = Moment<VariateType, typename DiagonalSecondMomentOf<VariateType>::type>::second_moment_value_type;

public:
    /**
     * \brief value_type Random variable type used for sampling.
     */
    using value_type = VariateType;

    /**
     * \brief sampling_value_type Distribution sampling interface type.
     */
    using sampling_value_type = Sampling<VariateType>;

    /**
     * \brief moment_value_type Represents the interface type providing the first two moments.
     */
    using moment_value_type = Moment<VariateType, typename DiagonalSecondMomentOf<VariateType>::type>;


    explicit StandardNormalDistribution(const unsigned int seed, std::size_t dim = DimensionOf<VariateType>()) :
        dimension_(dim),
        mean_(VariateType::Zero(dim, 1)),
        covariance_(CovarianceType(dim)),
        seed_(seed),
        generator_(seed_),
        distribution_(0.0, 1.0),
        gauss_rnd_sample_([&] { return (distribution_)(generator_); })
    {
        covariance_.setIdentity();
    }


    StandardNormalDistribution(std::size_t dim = DimensionOf<VariateType>()) :
        StandardNormalDistribution(1, dim)
    { }


    virtual ~StandardNormalDistribution() noexcept 
    { }


    virtual VariateType sample() const
    {
        VariateType gaussian_sample(dimension(), 1);

        for (std::size_t i = 0; i < dimension_; ++i)
            gaussian_sample(i, 0) = gauss_rnd_sample_();

        return gaussian_sample;
    }


    virtual int dimension() const
    {
        return dimension_;
    }


    /* FIXME
     * Maybe it's better to call this function resize(int).
     */
    virtual void dimension(const std::size_t new_dimension)
    {
        if (dimension_ == new_dimension)
            return;

        if (IsFixed<VariateType::SizeAtCompileTime>())
            throw utils::throw_message("STANDARDGAUSSIAN::DIMENSION", "Attempt to resize a fixed-size distribution.", "Eigen matrix size is: " + std::to_string(dimension_) + ". Requested is: " + std::to_string(new_dimension) + ".");

        dimension_ = new_dimension;
    }


    virtual const VariateType& mean() const
    {
        return mean_;
    }


    virtual const CovarianceType& covariance() const
    {
        return covariance_;
    }

protected:
    /**
     * The Standard Normal Distribution sample dimension.
     */
    std::size_t dimension_;

    /**
     * The Standard Normal Distribution mean.
     */
    VariateType mean_;

    /**
     * The Standard Normal Distribution covariance.
     */
    CovarianceType covariance_;

    /**
     * Seed of the random number generator.
     */
    unsigned int seed_;

    /**
     * Random number generator.
     */
    mutable std::mt19937_64 generator_;

    /**
     * Normal distribution for random number generation functions.
     */
    mutable std::normal_distribution<double> distribution_;

    /**
     * Random number generator function from a Normal distribution.
     * A call to `gauss_rnd_sample_()` returns a double-precision floating point random number.
     */
    std::function<double()> gauss_rnd_sample_;
};

/**
 * Floating point implementation for Scalar types float, double and long double
 */
template<>
class StandardNormalDistribution<double> : public Sampling<double>, public Moment<double, double>
{
public:
    /**
     * \brief value_type Random variable type used for sampling.
     */
    using value_type = double;

    /**
     * \brief sampling_value_type Distribution sampling interface type.
     */
    using sampling_value_type = Sampling<double>;

    /**
     * \brief moment_value_type Represents the interface type providing the first two moments.
     */
    using moment_value_type = Moment<double, double>;


    explicit StandardNormalDistribution(const unsigned int seed):
        dimension_(1),
        mean_(0.0),
        var_(1.0),
        seed_(seed),
        generator_(seed_),
        distribution_(0.0, 1.0),
        gauss_rnd_sample_([&] { return (distribution_)(generator_); })
    { }


    StandardNormalDistribution() :
        StandardNormalDistribution(1)
    { }


    double sample() const
    {
        return gauss_rnd_sample_();
    }


    virtual int dimension() const
    {
        return dimension_;
    }


    /* FIXME
     * Maybe it's better to call this function resize(int).
     */
    virtual void dimension(const std::size_t new_dimension)
    {
        static_cast<void>(new_dimension);

        throw utils::throw_message("STANDARDGAUSSIAN::DIMENSION", "Attempt to resize a scalar-valued distribution.");
    }


    virtual const double& mean() const
    {
        return mean_;
    }


    virtual const double& covariance() const
    {
        return var_;
    }

protected:
    /**
     * The Standard Normal Distribution sample dimension.
     */
    std::size_t dimension_;

    /**
     * The Standard Normal Distribution mean.
     */
    double mean_;

    /**
     * The Standard Normal Distribution covariance.
     */
    double var_;
    
    /**
     * Seed of the random number generator.
     */
    unsigned int seed_;

    /**
     * Random number generator.
     */
    mutable std::mt19937_64 generator_;

    /**
     * Normal distribution for random number generation functions.
     */
    mutable std::normal_distribution<double> distribution_;

    /**
     * Random number generator function from a Normal distribution.
     * A call to `gauss_rnd_sample_()` returns a double-precision floating point random number.
     */
    std::function<double()> gauss_rnd_sample_;
};

}


#endif /* STANDARDNORMALDISTRIBUTION_H */