/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef SIMULATEDLINEARSENSOR_H
#define SIMULATEDLINEARSENSOR_H

#include <BayesFilters/LinearModel.h>
#include <BayesFilters/SimulatedStateModel.h>

#include <memory>

namespace bfl {
    class SimulatedLinearSensor;
}


class bfl::SimulatedLinearSensor : public LinearModel
{
public:
    SimulatedLinearSensor(std::unique_ptr<bfl::SimulatedStateModel> simulated_state_model, const LinearMatrixComponent& linear_matrix_component, const Eigen::Ref<const Eigen::MatrixXd>& noise_covariance_matrix, const unsigned int seed);

    SimulatedLinearSensor(std::unique_ptr<bfl::SimulatedStateModel> simulated_state_model, const LinearMatrixComponent& linear_matrix_component, const Eigen::Ref<const Eigen::MatrixXd>& noise_covariance_matrix);

    virtual ~SimulatedLinearSensor() noexcept;

    bool freeze() override;

    std::pair<bool, bfl::Data> measure(const Data& data = Data()) const override;

    std::pair<std::size_t, std::size_t> getOutputSize() const override;


protected:
    std::unique_ptr<bfl::SimulatedStateModel> simulated_state_model_;

    Eigen::MatrixXd measurement_;

    std::size_t dim_linear_;

    std::size_t dim_circular_;

    void log() override;
};

#endif /* SIMULATEDLINEARSENSOR_H */
