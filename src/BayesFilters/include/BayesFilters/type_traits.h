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
 * \file traits.hpp
 * \date October 2014
 * \author Jan Issac (jan.issac@gmail.com)
 *
 * \file type_traits.h
 * \date July 2019
 * \author Claudio Fantacci (claudio.fantacci@gmail.com)
 */
#ifndef TYPETRAITS_H
#define TYPETRAITS_H

#include <Eigen/Dense>


namespace bfl
{

/**
 * \ingroup traits
 * \brief Returns the compile time size of a matrix or vector.
 *
 * \tparam EigenMatrixType A valid Eigen::Matrix type.
 *
 * SizeOf<M>() is shorthand for M::SizeAtCompileTime
 */
template<typename EigenMatrixType>
struct SizeOf
{
    enum : std::size_t
    {
        value = EigenMatrixType::SizeAtCompileTime
    };


    constexpr operator int() const
    {
        return value;
    }
};


/**
 * \ingroup traits
 *
 * \tparam EigenMatrixType A valid Eigen::Matrix type.
 *
 * Defines the second moment type of a given Eigen Matrix type.
 */
template<typename EigenMatrixType>
struct SecondMomentOf
{
    enum : std::size_t
    {
        dimension = SizeOf<EigenMatrixType>::value
    };


    using type = Eigen::Matrix<double, dimension, dimension>;
};


/**
 * \ingroup traits
 *
 * Defines the second moment type of a double-type random variable.
 */
template<>
struct SecondMomentOf<double>
{
    using type = double;
};


/**
 * \ingroup traits
 *
 * \tparam EigenMatrixType A valid Eigen::Matrix type.
 *
 * Defines the diagonal second moment type of a given Eigen Matrix type.
 */
template<typename EigenMatrixType>
struct DiagonalSecondMomentOf
{
    enum : std::size_t
    {
        dimension = SizeOf<EigenMatrixType>::value
    };


    using type = Eigen::DiagonalMatrix<double, dimension>;
};


/**
 * \ingroup traits
 *
 * \brief \c IsFixed<std::size_t> trait for static fixed-size checks.
 *
 * Generic IsFixed<std::size_t> definition which evaluates to true.
 * This traits is the opposite of IsDynamic.
 *
 * Examples
 *
 * static_assert(IsFixed<MyEigenMatrixType::SizeAtCompileTime>::value, "");
 *
 * // overloaded operator bool ()
 * if (IsFixed<MyEigenMatrixType::SizeAtCompileTime>()) ...
 */
template<std::size_t size>
struct IsFixed
{
    static_assert(size > Eigen::Dynamic, "Invalid static size");


    static constexpr bool value = true;


    constexpr operator bool() const
    {
        return value;
    }
};


/**
 * \ingroup traits
 * \brief \c IsFixed<-1> or \c IsFixed<Eigen::Dynamic> trait for static
 * fixed-size checks.
 *
 * A specialization IsFixed<Eigen::Dynamic> definition which evaluates to
 * false. This traits is the opposite of IsDynamic<Eigen::Dynamic>.
 *
 * Examples
 *
 * static_assert(!IsFixed<MyEigenMatrixType::SizeAtCompileTime>(), "");
 *
 * if (!IsFixed<MyEigenMatrixType::SizeAtCompileTime>::value) ...
 */
template<>
struct IsFixed<Eigen::Dynamic>
{
    static constexpr bool value = false;


    constexpr operator bool() const
    {
        return value;
    }
};


/**
 * \ingroup traits
 *
 * \brief Maps Eigen::Dynamic onto 0.
 *
 * For any type matrix or column vector the dimension is the number of rows,
 * i.e. Matrix::RowsAtCompileTime. If the Matrix::SizeAtCompileTime enum is not
 * equal Eigen::Dynamic (i.e. -1) the dimension is set to Matrix::RowsAtCompileTime.
 * Otherwise, 0 is returned.
 *
 * Examples
 *
 * static_assert(DimensionOf<MyEigenMatrixType>() > 0, "Dim must be greater than 0");
 *
 * static_assert(DimensionOf<MyEigenMatrixType>::value > 0, "Dim must be grater than 0");
 *
 * Eigen::VectorXd vector(DimensionOf<MyEigenMatrixType>());
 */
template<typename EigenMatrixType, std::enable_if<!std::is_arithmetic<EigenMatrixType>::value, int>::type = 0>
struct DimensionOf
{
    enum : std::size_t
    {
        value = IsFixed<EigenMatrixType::SizeAtCompileTime>() ? EigenMatrixType::RowsAtCompileTime : 0
    };


    constexpr operator std::size_t() const
    {
        return value;
    }
};

}

#endif /* TYPETRAITS_H */
