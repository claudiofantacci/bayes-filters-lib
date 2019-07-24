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
 * \file moments.hpp
 * \date May 2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 *
 * \file moments.h
 * \date July 2019
 * \author Claudio Fantacci (claudio.fantacci@gmail.com)
 */

#ifndef MOMENTS_H
#define MOMENTS_H

#include <BayesFilters/Distribution/ApproximateMoments.h>


namespace bfl
{

/* Forward declaration */
template<typename...>
class Moment;


/**
 * \ingroup distribution_interfaces
 *
 * \brief Represents the interface providing the first two moments.
 *
 * \tparam FirstMomentType Random variable type. This is equivalent to the first moment type.
 *
 * \tparam SecondMomentType Second moment type. The second moment is either the second uncentered moment
 *                          \f$Var(X) + X^2\f$ or simply the second central moment, the variance or
 *                          covariance \f$Var(X) = Cov(X, X)\f$. Both have the same type \c SecondMoment.
 *
 * The Moment interface provides access to the exact first moments of a distribution.
 */
template<typename FirstMomentType, typename SecondMomentType>
class Moment<FirstMomentType, SecondMomentType> : public ApproximateMoments<FirstMomentType, SecondMomentType>
{
public:
    /**
     * \brief first_moment_value_type Random variable type. This is equivalent to the first moment type.
     */
    using first_moment_value_type = FirstMomentType;

    /**
     * \brief second_moment_value_type Second moment type. The second moment is either the second uncentered moment
     *                                 \f$Var(X) + X^2\f$ or simply the second central moment, the variance or
     *                                 covariance \f$Var(X) = Cov(X, X)\f$. Both have the same type \c SecondMoment.
     */
    using second_moment_value_type = SecondMomentType;

    /**
     * \brief Overridable default destructor
     */
    virtual ~Moment() noexcept
    { }

    /**
     * \brief Returns the first moment of the underlying distribution, the mean
     *
     * \f$ \mu = \sum\limits_i x_i p(x_i)\f$
     */
    virtual const FirstMomentType& mean() const = 0;

    /**
     * \brief Returns the second centered moment of the underlying distribution,
     *         the covariance
     *
     * \f$ \Sigma = \sum\limits_i (x_i - \mu)(x_i - \mu)^T \f$
     */
    virtual const SecondMomentType& covariance() const = 0;


    const FirstMomentType& approximate_mean() const override
    {
        return mean();
    }


    const SecondMomentType& approximate_covariance() const override
    {
        return covariance();
    }
};


/**
 * \ingroup distribution_interfaces
 */
template<typename FirstMomentType>
class Moment<FirstMomentType> : public Moment<FirstMomentType, typename SecondMomentOf<FirstMomentType>::type>
{
public:
    /**
     * \brief Overridable default destructor
     */
    virtual ~Moment() noexcept
    { }
};


/**
 * \ingroup distribution_interfaces
 *
 */
template<>
class Moment<double> : public Moment<double, double>
{
public:
    /**
     * \brief Overridable default destructor
     */
    virtual ~Moment() noexcept
    { }
};

}


#endif /* MOMENTS_H */