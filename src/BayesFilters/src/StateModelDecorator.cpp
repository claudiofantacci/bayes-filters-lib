/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#include <BayesFilters/StateModelDecorator.h>

using namespace bfl;
using namespace Eigen;


void StateModelDecorator::propagate(const Ref<const MatrixXd>& cur_states, Ref<MatrixXd> prop_states)
{
    state_model_->propagate(cur_states, prop_states);
}


void StateModelDecorator::motion(const Ref<const MatrixXd>& cur_states, Ref<MatrixXd> mot_states)
{
    state_model_->motion(cur_states, mot_states);
}


MatrixXd StateModelDecorator::getJacobian()
{
    return state_model_->getJacobian();
}


VectorXd StateModelDecorator::getTransitionProbability(const Ref<const MatrixXd>& prev_states, const Ref<const MatrixXd>& cur_states)
{
    return state_model_->getTransitionProbability(prev_states, cur_states);
}


MatrixXd StateModelDecorator::getNoiseCovarianceMatrix()
{
    return state_model_->getNoiseCovarianceMatrix();
}


MatrixXd StateModelDecorator::getNoiseSample(const std::size_t num)
{
    return state_model_->getNoiseSample(num);
}


bool StateModelDecorator::setProperty(const std::string& property)
{
    return state_model_->setProperty(property);
}


std::pair<std::size_t, std::size_t> StateModelDecorator::getOutputSize() const
{
    return state_model_->getOutputSize();
}


void StateModelDecorator::set_state_model(std::unique_ptr<StateModelInterface> state_model) noexcept
{
    state_model_ = std::move(state_model);
}
