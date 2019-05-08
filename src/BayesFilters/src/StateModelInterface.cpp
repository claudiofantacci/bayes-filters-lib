/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#include <BayesFilters/StateModelInterface.h>

using namespace bfl;
using namespace Eigen;


StateModelInterface::~StateModelInterface() noexcept
{ }


Eigen::MatrixXd StateModelInterface::getJacobian()
{
    throw std::runtime_error("ERROR::STATEMODEL::GETJACOBIAN\nERROR:\n\tMethod not implemented.");
}


Eigen::VectorXd StateModelInterface::getTransitionProbability(const Ref<const MatrixXd>& prev_states, const Ref<const MatrixXd>& cur_states)
{
    throw std::runtime_error("ERROR::STATEMODEL::TRANSITIONPROBABILITY\nERROR:\n\tMethod not implemented.");
}


Eigen::MatrixXd StateModelInterface::getNoiseCovarianceMatrix()
{
    throw std::runtime_error("ERROR::STATEMODEL::GETNOISECOVARIANCEMATRIX\nERROR:\n\tMethod not implemented.");
}


Eigen::MatrixXd StateModelInterface::getNoiseSample(const std::size_t num)
{
    throw std::runtime_error("ERROR::STATEMODEL::GETNOISESAMPLE\nERROR:\n\tMethod not implemented.");
}
