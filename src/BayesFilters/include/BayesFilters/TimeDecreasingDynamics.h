#ifndef TIMEDECREASINGDYNAMICS_H
#define TIMEDECREASINGDYNAMICS_H

#include <BayesFilters/StateModelDecorator.h>

#include <memory>


namespace bfl {
    class TimeDecreasingDynamics;
}


class bfl::TimeDecreasingDynamics : public StateModelDecorator
{
public:
    TimeDecreasingDynamics(const unsigned int iterations) noexcept;

    TimeDecreasingDynamics(const double seconds) noexcept;

    TimeDecreasingDynamics(TimeDecreasingDynamics&& state_model) noexcept;

    TimeDecreasingDynamics& operator=(TimeDecreasingDynamics&& state_model) noexcept;

    virtual ~TimeDecreasingDynamics() noexcept;

    Eigen::MatrixXd getNoiseSample(const std::size_t num) override;

    bool setProperty(const std::string& property) override;


protected:
    struct ImplData;

    std::unique_ptr<ImplData> pImpl_;

    constexpr ImplData& impl();
};

#endif /* TIMEDECREASINGDYNAMICS_H */
