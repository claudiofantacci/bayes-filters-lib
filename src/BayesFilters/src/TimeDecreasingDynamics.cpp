#include <BayesFilters/TimeDecreasingDynamics.h>
#include <BayesFilters/utils.h>

#include <iostream>
#include <limits>

using namespace bfl;
using namespace Eigen;


struct TimeDecreasingDynamics::ImplData
{
    enum class Modality
    {
        Iteration,
        Time
    };

    Modality modality_;

    unsigned int iterations_;

    unsigned int current_iterations_ = 0;

    double seconds_;

    double current_seconds_ = 0.0;

    utils::CpuTimer<> timer_;
};


constexpr TimeDecreasingDynamics::ImplData& TimeDecreasingDynamics::impl()
{
    return *pImpl_;
}


TimeDecreasingDynamics::TimeDecreasingDynamics(const unsigned int iterations) noexcept :
    pImpl_(std::unique_ptr<ImplData>(new ImplData))
{
    impl().modality_ = ImplData::Modality::Iteration;

    impl().iterations_ = iterations;

    impl().seconds_ = std::numeric_limits<double>::infinity();
}


TimeDecreasingDynamics::TimeDecreasingDynamics(const double seconds) noexcept :
    pImpl_(std::unique_ptr<ImplData>(new ImplData))
{
    impl().modality_ = ImplData::Modality::Time;

    impl().iterations_ = std::numeric_limits<unsigned int>::max();

    impl().seconds_ = std::abs(seconds);

    if (seconds < 0)
    {
        std::cerr << "WARNING::TIMEDECREASINGDYNAMICS::CTOR\n";
        std::cerr << "WARNING::LOG:\n\tInput parameter `seconds` is negative. Used as positive.\n";
        std::cerr << "WARNING::LOG:\n\tProvided: " << seconds << ". Used " << impl().seconds_ << "." << std::endl;
    }
}


TimeDecreasingDynamics::TimeDecreasingDynamics(TimeDecreasingDynamics&& state_model) noexcept :
    StateModelDecorator(std::move(state_model)),
    pImpl_(std::move(state_model.pImpl_))
{ }


TimeDecreasingDynamics::~TimeDecreasingDynamics() noexcept
{ }


TimeDecreasingDynamics& TimeDecreasingDynamics::operator=(TimeDecreasingDynamics&& state_model) noexcept
{
    StateModelDecorator::operator=(std::move(state_model));

    pImpl_ = std::move(state_model.pImpl_);

    return *this;
}


MatrixXd TimeDecreasingDynamics::getNoiseSample(const std::size_t num)
{
    double damper = 1.0;

    switch (impl().modality_)
    {
        case ImplData::Modality::Iteration:
        {
            damper = (impl().current_iterations_ <= impl().iterations_) ? std::exp(-impl().current_iterations_) : 0.0;

            break;
        }

        case ImplData::Modality::Time:
        {
            damper = (impl().current_seconds_ <= impl().seconds_) ? std::exp(-impl().current_seconds_) : 0.0;

            break;
        }

        default:
            return StateModelDecorator::getNoiseSample(num);
    }

    return StateModelDecorator::getNoiseSample(num) * damper;
}


bool TimeDecreasingDynamics::setProperty(const std::string& property)
{
    if (property == "tdd_reset")
    {
        switch (impl().modality_)
        {
            case ImplData::Modality::Iteration:
            {
                impl().current_iterations_ = 0;

                break;
            }

            case ImplData::Modality::Time:
            {
                impl().timer_.stop();

                break;
            }

            default:
                return false;
        }

        return true;
    }


    if (property == "tdd_advance")
    {
        switch (impl().modality_)
        {
            case ImplData::Modality::Iteration:
            {
                ++impl().current_iterations_;

                break;
            }

            case ImplData::Modality::Time:
            {
                impl().current_seconds_ = impl().timer_.elapsed() * 1000.0;

                if (!impl().timer_.is_running())
                    impl().timer_.start();

                break;
            }

            default:
                return false;
        }

        return true;
    }


    return StateModelDecorator::setProperty(property);
}
