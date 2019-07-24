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
 * \file approximate_moments.h
 * \date May 2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 *
 * \file ApproximateMoments.h
 * \date July 2019
 * \author Claudio Fantacci (claudio.fantacci@gmail.com)
 */

#ifndef APPROXIMATEMOMENTS_H
#define APPROXIMATEMOMENTS_H

#include <BayesFilters/type_traits.h>

#include <Eigen/Dense>


namespace bfl
{

/* Forward declaration */
template<typename...>
class ApproximateMoments;


/**
 * \ingroup distribution_interfaces
 *
 * \brief Represents the interface providing the first two central moments.
 *
 * \tparam FirstMomentType Random variable type. This is equivalent to the first moment type.
 *
 * \tparam SecondMomentType Second central moment type (e.g. Variance or the Covariance).
 *
 * The ApproximateMoments interface provides access to a numerical approximation of the first moments of a distribution.
 *
 */
template<typename FirstMomentType, typename SecondMomentType>
class ApproximateMoments<FirstMomentType, SecondMomentType>
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
    virtual ~ApproximateMoments() noexcept
    { }

    /**
     * \brief Returns the first moment approximation, the mean
     *
     * \f$ \mean_{approx} \approx \sum\limits_i x_i p(x_i)\f$
     */
    virtual const FirstMomentType& approximate_mean() const = 0;

    /**
     * \brief Returns the second centeral moment, the covariance
     *
     * \f$ \Sigma_{approx} \approx
     *     \sum\limits_i (x_i - \mu)(x_i - \mu)^T \f$
     */
    virtual const SecondMomentType& approximate_covariance() const = 0;
};


/**
 * \ingroup distribution_interfaces
 */
template<typename FirstMomentType>
class ApproximateMoments<FirstMomentType> : public ApproximateMoments<FirstMomentType, typename SecondMomentOf<FirstMomentType>::type>
{
public:
    /**
     * \brief Overridable default destructor
     */
    virtual ~ApproximateMoments() noexcept
    { }
};

/**
 * \ingroup distribution_interfaces
 */
template<>
class ApproximateMoments<double> : public ApproximateMoments<double, double>
{
public:
    /**
     * \brief Overridable default destructor
     */
    virtual ~ApproximateMoments() noexcept
    { }
};

}


#endif /* APPROXIMATEMOMENTS_H */