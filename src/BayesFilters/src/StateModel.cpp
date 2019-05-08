/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#include <BayesFilters/StateModel.h>

using namespace bfl;
using namespace Eigen;


StateModel::StateModel() noexcept :
    state_model_impl_(this)
{ }


StateModel::~StateModel() noexcept
{ }


void StateModel::propagate(const Eigen::Ref<const Eigen::MatrixXd>& cur_states, Eigen::Ref<Eigen::MatrixXd> prop_states)
{
    state_model_impl_->propagate(cur_states, prop_states);
}


void StateModel::motion(const Eigen::Ref<const Eigen::MatrixXd>& cur_states, Eigen::Ref<Eigen::MatrixXd> mot_states)
{
    state_model_impl_->motion(cur_states, mot_states);
}


Eigen::MatrixXd StateModel::getJacobian()
{
    return state_model_impl_->getJacobian();
}


Eigen::VectorXd StateModel::getTransitionProbability(const Ref<const MatrixXd>& prev_states, const Ref<const MatrixXd>& cur_states)
{
    return state_model_impl_->getTransitionProbability(prev_states, cur_states);
}


Eigen::MatrixXd StateModel::getNoiseCovarianceMatrix()
{
    return state_model_impl_->getNoiseCovarianceMatrix();
}


Eigen::MatrixXd StateModel::getNoiseSample(const std::size_t num)
{
    return state_model_impl_->getNoiseSample(num);
}


bool StateModel::setProperty(const std::string& property)
{
    return state_model_impl_->setProperty(property);
}


std::pair<std::size_t, std::size_t> StateModel::getOutputSize() const
{
    return state_model_impl_->getOutputSize();
}


void StateModel::decorate(std::unique_ptr<StateModelDecorator> decorator) noexcept
{
    decorator->set_state_model(std::move(state_model_impl_));

    state_model_impl_ = std::move(decorator);
}


StateModelInterface& StateModel::state_model() noexcept
{
    return *state_model_impl_;
}
