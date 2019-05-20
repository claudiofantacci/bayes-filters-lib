#include "BayesFilters/ParameterContainer.h"

#include "BayesFilters/utils.h"

#include <unordered_map>

using namespace bfl;


struct ParameterContainer::ImplData
{
    std::unordered_map<std::string, Parameter> data;
};


ParameterContainer::ParameterContainer() noexcept :
    pimpl_(utils::make_unique<ImplData>())
{ }


ParameterContainer::~ParameterContainer() noexcept = default;


ParameterContainer::ParameterContainer(const ParameterContainer& parameter_container) :
    pimpl_(utils::make_unique<ImplData>())
{
    if (parameter_container.pimpl_)
        pimpl_ = utils::make_unique<ImplData>(*parameter_container.pimpl_);
}


ParameterContainer& ParameterContainer::operator=(const ParameterContainer& parameter_container)
{
    if (!parameter_container.pimpl_)
        pimpl_.reset();
    else if (!pimpl_)
        pimpl_ = utils::make_unique<ImplData>(*parameter_container.pimpl_);
    else
        *pimpl_ = *parameter_container.pimpl_;

    return *this;
}


ParameterContainer::ParameterContainer(ParameterContainer&& parameter_container) = default;


ParameterContainer& ParameterContainer::operator=(ParameterContainer&& parameter_container) = default;


Parameter& ParameterContainer::operator[](const std::string& label)
{
    return pimpl_->data[label];
}


Parameter& ParameterContainer::operator[](std::string&& label)
{
    return pimpl_->data[std::move(label)];
}
