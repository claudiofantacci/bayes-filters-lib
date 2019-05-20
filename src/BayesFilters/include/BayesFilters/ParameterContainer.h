/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef PARAMETERCONTAINER_H
#define PARAMETERCONTAINER_H

#include <BayesFilters/Parameter.h>

namespace bfl {
    class ParameterContainer;
}


/**
 * This class provides facilities to store and retrieve data (e.g. parameters) of different type, each associated to a unique string (associative container like).
 * In particular, an object ParameterContainer can store bool, int, unsigned int, double and std::string.
 */
class bfl::ParameterContainer
{
public:
    /**
     * Creates an empty object.
     */
    ParameterContainer() noexcept;


    /**
     * Deletes the content stored in the object.
     */
    ~ParameterContainer() noexcept;


    /**
     * Creates an object as a copy of the input.
     *
     * @param parameter_container The object to copy from.
     */
    ParameterContainer(const ParameterContainer& parameter_container);


    /**
     * Copy the input data in the object.
     *
     * @param parameter_container The object to copy from.
     */
    ParameterContainer& operator=(const ParameterContainer& parameter_container);


    /**
     * Creates an object moving the input data.
     *
     * @param parameter_container The object to move from.
     */
    ParameterContainer(ParameterContainer&& parameter_container);


    /**
     * Move the input data in the object.
     *
     * @param parameter_container The object to move from.
     */
    ParameterContainer& operator=(ParameterContainer&& parameter_container);


    /**
     * Returns a reference to the value that is mapped to label, performing an insertion if such key does not already exist.
     *
     * @param label The unique label associated to the parameter.
     */
    Parameter& operator[](const std::string& label);


    /**
     * Returns a reference to the value that is mapped to label, performing an insertion if such key does not already exist.
     *
     * @param label The unique label associated to the parameter.
     */
    Parameter& operator[](std::string&& label);


private:
    /**
     * The stored content of an object.
     */
    struct ImplData;

    std::unique_ptr<ImplData> pimpl_;
};

#endif /* PARAMETERCONTAINER_H */
