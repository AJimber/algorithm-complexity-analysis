// include/ClaseTiempo.hpp

#ifndef CLASE_TIEMPO_HPP
#define CLASE_TIEMPO_HPP

#include <chrono>
#include <cassert>
#include <cstdint>

class Clock
{
private:
    using ClockType = std::chrono::steady_clock;

    ClockType::time_point startTime_;
    ClockType::time_point stopTime_;
    bool started_;

public:
    Clock() : started_(false) {}

    void start()
    {
        assert(!started_);
        startTime_ = ClockType::now();
        started_ = true;
    }

    void restart()
    {
        startTime_ = ClockType::now();
        started_ = true;
    }

    void stop()
    {
        assert(started_);
        stopTime_ = ClockType::now();
        started_ = false;
    }

    bool isStarted() const
    {
        return started_;
    }

    std::uint64_t elapsed() const
    {
        assert(!started_);

        return static_cast<std::uint64_t>(
            std::chrono::duration_cast<std::chrono::microseconds>(
                stopTime_ - startTime_
            ).count()
        );
    }
};

#endif