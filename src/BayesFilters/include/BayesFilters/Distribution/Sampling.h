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
 * \file sampling.hpp
 * \date May 2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 *
 * \file Sampling.h
 * \date July 2019
 * \author Claudio Fantacci (claudio.fantacci@gmail.com)
 */

#ifndef SAMPLING_H
#define SAMPLING_H


namespace bfl
{

/**
 * \ingroup distribution_interfaces
 *
 * \brief Distribution sampling interface.
 *
 * \tparam VariateType Random variate type.
 */
template<typename VariateType>
class Sampling
{
public:
    /**
     * \brief value_type Random variable type.
     */
    using value_type = VariateType;

    /**
     * \brief Overridable default destructor
     */
    virtual ~Sampling() noexcept
    { }

    /**
     * \return A random sample of the underlying distribution \f[x \sim p(x)\f]
     */
    virtual VariateType sample() const = 0;
};

}


#endif /* SAMPLING_H */