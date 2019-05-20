#include "BayesFilters/Parameter.h"

#include "BayesFilters/Data.h"
#include "BayesFilters/utils.h"

#include <type_traits>
#include <utility>

using namespace bfl;


struct Parameter::ImplData
{
    enum class DatumType
    {
        Bool,
        Int,
        UInt,
        Float,
        Double,
        String,
        Any,
        Empty
    };

    ImplData() :
        type_(DatumType::Empty)
    { }

    template<typename ValueType>
    explicit ImplData(ValueType&& value, const DatumType type) :
        datum_(std::forward<ValueType>(value)),
        type_(type)
    { }

    template<typename ValueType>
    explicit ImplData(ValueType&& value) :
        datum_(std::forward<ValueType>(value)),
        type_(DatumType::Any)
    { }

    Data datum_;

    DatumType type_;
};


Parameter::Parameter() noexcept :
    pimpl_(utils::make_unique<ImplData>())
{ }


Parameter::Parameter(const bool datum) :
    pimpl_(utils::make_unique<ImplData>(datum, ImplData::DatumType::Bool))
{ }


Parameter::Parameter(const int datum) :
    pimpl_(utils::make_unique<ImplData>(datum, ImplData::DatumType::Int))
{ }


Parameter::Parameter(const unsigned int datum) :
    pimpl_(utils::make_unique<ImplData>(datum, ImplData::DatumType::UInt))
{ }


Parameter::Parameter(const float datum) :
    pimpl_(utils::make_unique<ImplData>(datum, ImplData::DatumType::Float))
{ }


Parameter::Parameter(const double datum) :
    pimpl_(utils::make_unique<ImplData>(datum, ImplData::DatumType::Double))
{ }


Parameter::Parameter(const std::string& datum) :
    pimpl_(utils::make_unique<ImplData>(datum, ImplData::DatumType::String))
{ }


Parameter::~Parameter() noexcept = default;


Parameter::Parameter(const Parameter& parameter_container) :
    pimpl_(utils::make_unique<ImplData>())
{
    if (parameter_container.pimpl_)
        pimpl_ = utils::make_unique<ImplData>(*parameter_container.pimpl_);
}


Parameter& Parameter::operator=(const Parameter& parameter_container)
{
    if (!parameter_container.pimpl_)
        pimpl_.reset();
    else if (!pimpl_)
        pimpl_ = utils::make_unique<ImplData>(*parameter_container.pimpl_);
    else
        *pimpl_ = *parameter_container.pimpl_;

    return *this;
}


Parameter::Parameter(Parameter&& parameter_container) = default;


Parameter& Parameter::operator=(Parameter&& parameter_container) = default;


Parameter& Parameter::operator=(const bool datum)
{
    pimpl_->datum_ = datum;

    pimpl_->type_ = ImplData::DatumType::Bool;

    return *this;
}



Parameter& Parameter::operator=(const int datum)
{
    pimpl_->datum_ = datum;

    pimpl_->type_ = ImplData::DatumType::Int;

    return *this;
}


Parameter& Parameter::operator=(const unsigned int datum)
{
    pimpl_->datum_ = datum;

    pimpl_->type_ = ImplData::DatumType::UInt;

    return *this;
}


Parameter& Parameter::operator=(const float datum)
{
    pimpl_->datum_ = datum;

    pimpl_->type_ = ImplData::DatumType::Float;

    return *this;
}


Parameter& Parameter::operator=(const double datum)
{
    pimpl_->datum_ = datum;

    pimpl_->type_ = ImplData::DatumType::Double;

    return *this;
}



Parameter& Parameter::operator=(const std::string& datum)
{
    pimpl_->datum_ = datum;

    pimpl_->type_ = ImplData::DatumType::String;

    return *this;
}


template<typename DataType>
bool as_bool_helper(const Data& datum)
{
    DataType data = any::any_cast<DataType>(datum);

    if (data)
        return true;
    else
        return false;
}


template<>
bool as_bool_helper<std::string>(const Data& datum)
{
    std::string data = any::any_cast<std::string>(datum);

    return data.empty();
}


template<typename FromType, typename ToType>
ToType as_type_helper(const Data& datum)
{
    FromType data = any::any_cast<FromType>(datum);

    return static_cast<ToType>(data);
}


template<typename ToType>
ToType as_type_helper_from_string(const Data& datum)
{
    std::string data = any::any_cast<std::string>(datum);

    return static_cast<ToType>(std::stod(data));
}


template<typename FromType>
std::string as_type_helper_to_string(const Data& datum)
{
    FromType data = any::any_cast<FromType>(datum);

    return std::to_string(data);
}


/* FUTURE: C++17 Implementation
 *
 * template<typename FromType, typename ToType>
 * ToType as_type_helper(const Data& datum)
 * {
 *     FromType data = any::any_cast<FromType>(datum);
 *
 *     if constexpr (std::is_same<FromType, std::string>::value)
 *         return static_cast<ToType>(std::stod(data));
 *     else if constexpr (std::is_same<ToType, std::string>::value)
 *         return std::to_string(data);
 *     else
 *         return static_cast<ToType>(data);
 * }
 */


bool Parameter::as_bool() const
{
    switch (pimpl_->type_)
    {
        case ImplData::DatumType::Bool:
            return any::any_cast<bool>(pimpl_->datum_);

        case ImplData::DatumType::Int:
            return as_bool_helper<int>(pimpl_->datum_);

        case ImplData::DatumType::UInt:
            return as_bool_helper<unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::Float:
            return as_bool_helper<float>(pimpl_->datum_);

        case ImplData::DatumType::Double:
            return as_bool_helper<double>(pimpl_->datum_);

        case ImplData::DatumType::String:
            return as_bool_helper<std::string>(pimpl_->datum_);

        default:
            throw std::runtime_error("ERROR::PARAMETER::OPERATOR::AS_BOOL\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");
    }
}


int Parameter::as_int() const
{
    switch (pimpl_->type_)
    {
        case ImplData::DatumType::Bool:
            return as_type_helper<bool, int>(pimpl_->datum_);

        case ImplData::DatumType::Int:
            return any::any_cast<int>(pimpl_->datum_);

        case ImplData::DatumType::UInt:
            return as_type_helper<unsigned int, int>(pimpl_->datum_);

        case ImplData::DatumType::Float:
            return as_type_helper<float, int>(pimpl_->datum_);

        case ImplData::DatumType::Double:
            return as_type_helper<double, int>(pimpl_->datum_);

        case ImplData::DatumType::String:
            return as_type_helper_from_string<int>(pimpl_->datum_);

        default:
            throw std::runtime_error("ERROR::PARAMETER::OPERATOR::AS_INT\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");
    }
}


unsigned int Parameter::as_uint() const
{
    switch (pimpl_->type_)
    {
        case ImplData::DatumType::Bool:
            return as_type_helper<bool, unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::Int:
            return as_type_helper<int, unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::UInt:
            return any::any_cast<unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::Float:
            return as_type_helper<float, unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::Double:
            return as_type_helper<double, unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::String:
            return as_type_helper_from_string<unsigned int>(pimpl_->datum_);

        default:
            throw std::runtime_error("ERROR::PARAMETER::OPERATOR::AS_UINT\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");
    }
}


float Parameter::as_float() const
{
    switch (pimpl_->type_)
    {
        case ImplData::DatumType::Bool:
            return as_type_helper<bool, float>(pimpl_->datum_);

        case ImplData::DatumType::Int:
            return as_type_helper<int, float>(pimpl_->datum_);

        case ImplData::DatumType::UInt:
            return as_type_helper<unsigned int, float>(pimpl_->datum_);

        case ImplData::DatumType::Float:
            return any::any_cast<float>(pimpl_->datum_);

        case ImplData::DatumType::Double:
            return as_type_helper<double, float>(pimpl_->datum_);

        case ImplData::DatumType::String:
            return as_type_helper_from_string<float>(pimpl_->datum_);

        default:
            throw std::runtime_error("ERROR::PARAMETER::OPERATOR::AS_FLOAT\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");
    }
}


double Parameter::as_double() const
{
    switch (pimpl_->type_)
    {
        case ImplData::DatumType::Bool:
            return as_type_helper<bool, double>(pimpl_->datum_);

        case ImplData::DatumType::Int:
            return as_type_helper<int, double>(pimpl_->datum_);

        case ImplData::DatumType::UInt:
            return as_type_helper<unsigned int, double>(pimpl_->datum_);

        case ImplData::DatumType::Float:
            return as_type_helper<float, double>(pimpl_->datum_);

        case ImplData::DatumType::Double:
            return any::any_cast<double>(pimpl_->datum_);

        case ImplData::DatumType::String:
            return as_type_helper_from_string<double>(pimpl_->datum_);

        default:
            throw std::runtime_error("ERROR::PARAMETER::OPERATOR::AS_DOUBLE\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");
    }
}


std::string Parameter::as_string() const
{
    switch (pimpl_->type_)
    {
        case ImplData::DatumType::Bool:
            return as_type_helper_to_string<bool>(pimpl_->datum_);

        case ImplData::DatumType::Int:
            return as_type_helper_to_string<int>(pimpl_->datum_);

        case ImplData::DatumType::UInt:
            return as_type_helper_to_string<unsigned int>(pimpl_->datum_);

        case ImplData::DatumType::Float:
            return as_type_helper_to_string<float>(pimpl_->datum_);

        case ImplData::DatumType::Double:
            return as_type_helper_to_string<double>(pimpl_->datum_);

        case ImplData::DatumType::String:
            return any::any_cast<std::string>(pimpl_->datum_);

        case ImplData::DatumType::Empty:
            return "Empty";

        default:
            throw std::runtime_error("ERROR::PARAMETER::OPERATOR::AS_STRING\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");
    }
}


std::ostream& bfl::operator<<(std::ostream& out, const Parameter& parameter)
{
    if (parameter.pimpl_->type_ == Parameter::ImplData::DatumType::Any)
        throw std::runtime_error("ERROR::PARAMETER::OPERATOR<<::\nERROR:\n\tType of datum is Unknown or Any. Cannot convert safely.");

    out << parameter.as_string();

    return out;
}
