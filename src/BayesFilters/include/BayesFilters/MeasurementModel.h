#ifndef MEASUREMENTMODEL_H
#define MEASUREMENTMODEL_H

#include <string>
#include <utility>

#include <Eigen/Dense>

namespace bfl {
    class MeasurementModel;
}


class bfl::MeasurementModel
{
public:
    virtual ~MeasurementModel() noexcept { };

    virtual std::pair<bool, Eigen::MatrixXf> measure(const Eigen::Ref<const Eigen::MatrixXf>& cur_states) const = 0;

    virtual std::pair<bool, Eigen::MatrixXf> innovation(const Eigen::Ref<const Eigen::MatrixXf>& predicted_measurements, const Eigen::Ref<const Eigen::MatrixXf>& measurements) const = 0;

    virtual bool bufferProcessMeasurements();

    virtual std::pair<bool, Eigen::MatrixXf> getProcessMeasurements() const;

    virtual std::pair<bool, Eigen::MatrixXf> predictedMeasure(const Eigen::Ref<const Eigen::MatrixXf>& cur_states) const = 0;

    virtual std::pair<bool, Eigen::MatrixXf> getNoiseSample(const int num) const;

    virtual std::pair<bool, Eigen::MatrixXf> getNoiseCovarianceMatrix() const;

    virtual bool setProperty(const std::string property);
};

#endif /* MEASUREMENTMODEL_H */
