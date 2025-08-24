#pragma once

#ifndef _BENCH_MARK_TIMER_H
#define _BENCH_MARK_TIMER_H

#include <chrono>

class BenchmarkTimer 
{
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    BenchmarkTimer() { Start(); }
    ~BenchmarkTimer() { Stop(); }

    // Start timer.
    void Start()
    {
        startTime = Clock::now();
    }

    // Stop timer and return elapsed time in milliseconds.
    long long Stop()
    {
        endTime = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        return duration.count();
    }

    // Get elapsed time (in milliseconds) without pausing the timer.
    long long Elapsed() const 
    {
        auto now = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);
        return duration.count();
    }

private:
    TimePoint startTime;
    TimePoint endTime;
};

#endif // !_BENCH_MARK_TIMER_H