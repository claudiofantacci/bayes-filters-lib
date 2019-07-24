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
 * \file joint_distribution_id.hpp
 * \date Febuary 2015
 * \author Jan Issac (jan.issac@gmail.com)
 */

#pragma once


#include <Eigen/Dense>

#include <fl/util/meta.hpp>
#include <fl/util/traits.hpp>
#include <fl/distribution/interface/moments.hpp>

namespace fl
{

// Forward declaration
template <typename...Distribution> class JointDistribution;

/**
 * \internal
 *
 * Traits of JointDistribution<Distribution...>
 */
template <typename...Distribution>
struct Traits<JointDistribution<Distribution...>>
{
    enum : signed int
    {
        JointSize = JoinSizes<SizeOf<typename Distribution::VariateType>::Value...>::Size
    };

    typedef typename FirstTypeIn<
                typename Distribution::VariateType...
            >::type::Scalar Scalar;

    typedef Eigen::Matrix<Scalar, JointSize, 1> VariateType;
};

/**
 * \ingroup distributions
 */
template <typename...Distribution>
class JointDistribution
    : public Moment<typename Traits<JointDistribution<Distribution...>>::VariateType>
{
public:
    typedef typename Traits<JointDistribution<Distribution...>>::VariateType VariateType;
    typedef typename Moment<VariateType>::SecondMoment SecondMoment;
    typedef std::tuple<Distribution...> MarginalDistributions;

public:
    JointDistribution(Distribution...distributions)
        : distributions_(distributions...)
    { }

    /**
     * \brief Overridable default destructor
     */
    virtual ~JointDistribution() noexcept { }

    virtual VariateType mean() const
    {
        VariateType mu = VariateType(dimension(), 1);

        mean_<sizeof...(Distribution)>(distributions_, mu);

        return mu;
    }

    virtual SecondMoment covariance() const
    {
        SecondMoment cov = SecondMoment::Zero(dimension(), dimension());

        covariance<sizeof...(Distribution)>(distributions_, cov);

        return cov;
    }

    virtual int dimension() const
    {
        return expend_dimension(CreateIndexSequence<sizeof...(Distribution)>());
    }

    MarginalDistributions& distributions()
    {
        return distributions_;
    }

    const MarginalDistributions& distributions() const
    {
        return distributions_;
    }

protected:
    MarginalDistributions distributions_;

private:
    template <int...Indices>
    int expend_dimension(IndexSequence<Indices...>) const
    {
        const auto& dims = { std::get<Indices>(distributions_).dimension()... };

        int joint_dim = 0;
        for (auto dim : dims) { joint_dim += dim; }

        return joint_dim;
    }

    template <int Size, int k = 0>
    void mean_(const MarginalDistributions& distr_tuple,
               VariateType& mu,
               int offset = 0) const
    {
        auto&& distribution = std::get<k>(distr_tuple);
        const int dim = distribution.dimension();

        mu.middleRows(offset, dim) = distribution.mean();

        if (Size == k + 1) return;

        mean_<Size, k + (k + 1 < Size ? 1 : 0)>(distr_tuple, mu, offset + dim);
    }

    template <int Size, int k = 0>
    void covariance(const MarginalDistributions& distr,
                    SecondMoment& cov,
                    const int offset = 0) const
    {
        auto& distribution = std::get<k>(distr);
        const int dim = distribution.dimension();

        cov.block(offset, offset, dim, dim) = distribution.covariance();

        if (Size == k + 1) return;

        covariance<Size, k + (k + 1 < Size ? 1 : 0)>(distr, cov, offset + dim);
    }
};

}
