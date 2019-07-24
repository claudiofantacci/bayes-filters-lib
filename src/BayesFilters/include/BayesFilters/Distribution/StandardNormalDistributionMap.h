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
 * \file standard_gaussian_mapping.hpp
 * \date May 2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
  *
 * \file StandardNormalDistributionMap.h
 * \date July 2019
 * \author Claudio Fantacci (claudio.fantacci@gmail.com)
 */

#ifndef STANDARDNORMALDISTRIBUTIONMAP_H
#define STANDARDNORMALDISTRIBUTIONMAP_H

#include <BayesFilters/type_traits.h>
#include <BayesFilters/Distribution/Sampling.h>
#include <BayesFilters/Distribution/StandardNormalDistribution.h>

#include <type_traits>

#include <Eigen/Dense>


namespace bfl
{

/**
 * \ingroup distribution_interfaces
 *
 * \brief Represents the interface that provides a mapping from a standard normal distribution
 *        onto the underlying distribution implemented through this interface.
 *
 * \tparam VariateType The distribution variate type. This is the type that is returned by the
 *                     mapping or sampling, respectively.
 */
template <typename VariateType>
class StandardNormalDistributionMap : public Sampling<VariateType>
{
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
     * StandardNormalDistributionMap constructor. It initializes the mapper
     *
     * \param snv_dimension Dimension of the standard normal variate
     */
    explicit StandardNormalDistributionMap(std::size_t snv_dimension = DimensionOf<VariateType>()) :
        standard_gaussian_(snv_dimension)
    { }

    /**
     * \brief Overridable default destructor
     */
    virtual ~StandardNormalDistributionMap() noexcept { }

    /**
     * \brief Mapps a standard normal variate onto a sample of the underlying
     *        distribution which implements this mapper
     *
     * \param sample  SNV sample which will be mapped onto a variate sampe
     *
     * \return A variate according to the underlying distribution
     */
    virtual VariateType map_standard_normal(const VariateType& sample) const = 0;

    /**
     * \return A variate according to the underlying distribution
     */
    virtual VariateType sample() const
    {
        return map_standard_normal(standard_gaussian_.sample());
    }

    /**
     * \return Dimension of the standard normal variate used for mapping
     */
    virtual int standard_variate_dimension() const
    {
        return standard_gaussian_.dimension();
    }

    /**
     * \brief Sets the dimension of the standard normal variate
     *
     * \param snv_dimension The new dimension of the SNV
     */
    virtual void standard_variate_dimension(int snv_dimension)
    {
        standard_gaussian_.dimension(snv_dimension);
    }

protected:
    /**
     * \brief SNV generator
     */
    mutable StandardNormalDistribution<VariateType> standard_gaussian_;
};


}


#endif /* STANDARDNORMALDISTRIBUTIONMAP_H */
