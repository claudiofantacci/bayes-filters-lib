/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef STATEMODEL_H
#define STATEMODEL_H

#include <BayesFilters/StateModelInterface.h>
#include <BayesFilters/StateModelDecorator.h>

#include <memory>

namespace bfl {
    class StateModel;
}


class bfl::StateModel : public bfl::StateModelInterface
{
public:
    StateModel() noexcept;

    virtual ~StateModel() noexcept;

    void propagate(const Eigen::Ref<const Eigen::MatrixXd>& cur_states, Eigen::Ref<Eigen::MatrixXd> prop_states) override;

    void motion(const Eigen::Ref<const Eigen::MatrixXd>& cur_states, Eigen::Ref<Eigen::MatrixXd> mot_states) override;

    Eigen::MatrixXd getJacobian() override;

    Eigen::VectorXd getTransitionProbability(const Eigen::Ref<const Eigen::MatrixXd>& prev_states, const Eigen::Ref<const Eigen::MatrixXd>& cur_states) override;

    Eigen::MatrixXd getNoiseCovarianceMatrix() override;

    Eigen::MatrixXd getNoiseSample(const std::size_t num) override;

    bool setProperty(const std::string& property) override;

    std::pair<std::size_t, std::size_t> getOutputSize() const override;

    void decorate(std::unique_ptr<StateModelDecorator> decorator) noexcept;

    StateModelInterface& state_model() noexcept;


private:
    std::unique_ptr<StateModelInterface> state_model_impl_;
};

#endif /* STATEMODEL_H */
