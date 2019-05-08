/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef STATEMODELDECORATOR_H
#define STATEMODELDECORATOR_H

#include <BayesFilters/StateModelInterface.h>
#include <BayesFilters/StateModel.h>

#include <memory>

namespace bfl {
    class StateModelDecorator;
}


class bfl::StateModelDecorator : public StateModelInterface
{
    friend class StateModel;


public:
    void propagate(const Eigen::Ref<const Eigen::MatrixXd>& cur_states, Eigen::Ref<Eigen::MatrixXd> prop_states) override;

    void motion(const Eigen::Ref<const Eigen::MatrixXd>& cur_states, Eigen::Ref<Eigen::MatrixXd> mot_states) override;

    Eigen::MatrixXd getJacobian() override;

    Eigen::VectorXd getTransitionProbability(const Eigen::Ref<const Eigen::MatrixXd>& prev_states, const Eigen::Ref<const Eigen::MatrixXd>& cur_states) override;

    Eigen::MatrixXd getNoiseCovarianceMatrix() override;

    Eigen::MatrixXd getNoiseSample(const std::size_t num) override;

    bool setProperty(const std::string& property) override;

    std::pair<std::size_t, std::size_t> getOutputSize() const override;


protected:
    StateModelDecorator() noexcept = default;

    StateModelDecorator(const StateModelDecorator& state_model) noexcept = delete;

    StateModelDecorator& operator=(const StateModelDecorator& state_model) noexcept = delete;

    StateModelDecorator(StateModelDecorator&& state_model) noexcept = default;

    StateModelDecorator& operator=(StateModelDecorator&& state_model) noexcept = default;

    virtual ~StateModelDecorator() noexcept = default;


private:
    void set_state_model(std::unique_ptr<StateModelInterface> state_model) noexcept;

    std::unique_ptr<StateModelInterface> state_model_ = nullptr;
};

#endif /* STATEMODELDECORATOR_H */
