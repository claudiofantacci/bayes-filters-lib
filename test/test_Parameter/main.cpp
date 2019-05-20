/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#include <iostream>
#include <thread>

#include <BayesFilters/ParameterContainer.h>

using namespace bfl;


int main()
{
    std::cout << "[Test 1] ParameterContainer creation" << std::endl;

    std::cout << "Creating a ParameterContainer...";

    ParameterContainer parameter_container;

    std::cout << "done." << std::endl;

    /* -------------------------------------------------- */

    std::cout << "[Test 2] Bool" << std::endl;
    bool bool_content = false;

    std::cout << "Assigning a bool using ctor...";

    parameter_container["bool"] = Parameter(true);

    bool_content = parameter_container["bool"].as_bool();
    if (bool_content != true)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["bool"] << std::endl;


    std::cout << "Assigning a bool using assignment operator...";

    parameter_container["bool"] = false;

    bool_content = parameter_container["bool"].as_bool();
    if (bool_content != false)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["bool"] << std::endl;

    /* -------------------------------------------------- */

    std::cout << "[Test 3] Int" << std::endl;
    int int_content = 0;

    std::cout << "Assigning an int using ctor...";

    parameter_container["int"] = Parameter(1);

    int_content = parameter_container["int"].as_int();
    if (int_content != 1)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["int"] << std::endl;


    std::cout << "Assigning an int using assignment operator...";

    parameter_container["int"] = -1;

    int_content = parameter_container["int"].as_int();
    if (int_content != -1)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["int"] << std::endl;


    /* -------------------------------------------------- */

    std::cout << "[Test 4] Unsigned int" << std::endl;
    unsigned int uint_content = 0;

    std::cout << "Assigning an unsigned int using ctor...";

    parameter_container["uint"] = Parameter(1u);

    uint_content = parameter_container["uint"].as_uint();
    if (uint_content != 1)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["uint"] << std::endl;


    std::cout << "Assigning an unsigend int using assignment operator...";

    parameter_container["uint"] = 2u;

    uint_content = parameter_container["uint"].as_uint();
    if (uint_content != 2)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["uint"] << std::endl;

    /* -------------------------------------------------- */

    std::cout << "[Test 5] Float" << std::endl;
    float float_content = 0.0f;

    std::cout << "Assigning a float using ctor...";

    parameter_container["float"] = Parameter(1.1f);

    float_content = parameter_container["float"].as_float();
    if (float_content != 1.1f)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["float"] << std::endl;


    std::cout << "Assigning a float using assignment operator...";

    parameter_container["float"] = -1.1f;

    float_content = parameter_container["float"].as_float();
    if (float_content != -1.1f)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["float"] << std::endl;

    /* -------------------------------------------------- */

    std::cout << "[Test 6] Double" << std::endl;
    double double_content = 0.0;

    std::cout << "Assigning a double using ctor...";

    parameter_container["double"] = Parameter(1.1);

    double_content = parameter_container["double"].as_double();
    if (double_content != 1.1)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["double"] << std::endl;


    std::cout << "Assigning a double using assignment operator...";

    parameter_container["double"] = -1.1;

    double_content = parameter_container["double"].as_double();
    if (double_content != -1.1)
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["double"] << std::endl;

    /* -------------------------------------------------- */

    std::cout << "[Test 7] String" << std::endl;
    std::string string_content;

    std::cout << "Assigning a std::string using ctor...";

    parameter_container["string"] = Parameter(std::string("content"));

    string_content = parameter_container["string"].as_string();
    if (string_content != "content")
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["string"] << std::endl;


    std::cout << "Assigning a string using assignment operator...";

    parameter_container["string"] = std::string("another_content");

    string_content = parameter_container["string"].as_string();
    if (string_content != "another_content")
    {
        std::cout << "failed." << std::endl;

        return EXIT_FAILURE;
    }

    std::cout << "done. Value is: " << parameter_container["string"] << std::endl;

    /* -------------------------------------------------- */

    std::cout << "[Test 8] Empty parameter creation" << std::endl;

    std::cout << "Creating a Parameter...";

    Parameter parameter;

    std::cout << "done. Value: " << parameter << std::endl;

    /* -------------------------------------------------- */

    std::cout << "\nAll tests completed succesfully." << std::endl;


    return EXIT_SUCCESS;
}
