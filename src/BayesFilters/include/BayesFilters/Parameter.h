/*
* Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
*
* This software may be modified and distributed under the terms of the
* BSD 3-Clause license. See the accompanying LICENSE file for details.
*/

#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <memory>
#include <string>

namespace bfl {
    class Parameter;
    std::ostream& operator<<(std::ostream& out, const Parameter& parameter);
}


/**
 * This class provides facilities to store and retrieve a scalar datum (e.g. a parameter) of different type.
 * In particular, an object Parameter can store a bool, int, unsigned int, double or a std::string.
 */
class bfl::Parameter
{
public:
    /**
     * Creates an empty object.
     */
    Parameter() noexcept;


    /**
     * Construct an object with a `bool` value.
     */
    explicit Parameter(const bool datum);


    /**
     * Construct an object with a `int` value.
     */
    explicit Parameter(const int datum);


    /**
     * Construct an object with a `unsigned int` value.
     */
    explicit Parameter(const unsigned int datum);


    /**
     * Construct an object with a `float` value.
     */
    explicit Parameter(const float datum);


    /**
     * Construct an object with a `double` value.
     */
    explicit Parameter(const double datum);


    /**
     * Construct an object with a `std::string` value.
     */
    explicit Parameter(const std::string& datum);


    /**
     * Deletes the content stored in the object.
     */
    ~Parameter() noexcept;


    /**
     * Creates an object as a copy of the input.
     *
     * @param parameter_container The object to copy from.
     */
    Parameter(const Parameter& parameter_container);


    /**
     * Copy the input data in the object.
     *
     * @param parameter_container The object to copy from.
     */
    Parameter& operator=(const Parameter& parameter_container);


    /**
     * Creates an object moving the input data.
     *
     * @param parameter_container The object to move from.
     */
    Parameter(Parameter&& parameter_container);


    /**
     * Move the input data in the object.
     *
     * @param parameter_container The object to move from.
     */
    Parameter& operator=(Parameter&& parameter_container);


    /**
     * Store a `bool`.
     */
    Parameter& operator=(const bool datum);


    /**
     * Store an `int`.
     */
    Parameter& operator=(const int datum);


    /**
     * Store an `unsigned int`.
     */
    Parameter& operator=(const unsigned int datum);


    /**
     * Store a `float`.
     */
    Parameter& operator=(const float datum);


    /**
     * Store a `double`.
     */
    Parameter& operator=(const double datum);


    /**
     * Store a `std::string`.
     */
    Parameter& operator=(const std::string& datum);


    /**
     * Cast the parameter to `bool`.
     */
    bool as_bool() const;


    /**
     * Cast the parameter to `int`.
     */
    int as_int() const;


    /**
     * Cast the parameter to `unsigned int`.
     */
    unsigned int as_uint() const;


    /**
     * Cast the parameter to `float`.
     */
    float as_float() const;


    /**
     * Cast the parameter to `double`.
     */
    double as_double() const;


    /**
     * Cast the parameter to `std::string`.
     */
    std::string as_string() const;


    /**
     * Outstrem operator.
     */
    friend std::ostream& operator<<(std::ostream& out, const Parameter& parameter);


private:
    /**
     * The stored content of an object.
     */
    struct ImplData;

    std::unique_ptr<ImplData> pimpl_;
};

#endif /* PARAMETER_H */
