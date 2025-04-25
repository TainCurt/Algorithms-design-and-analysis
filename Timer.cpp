#include "Timer.h"

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    running = false;
    elapsed = chrono::milliseconds(0);
    start_time = chrono::high_resolution_clock::time_point();
    stop_time = chrono::high_resolution_clock::time_point();
}

int Timer::start()
{
    if (running)
    {
        return -1;
    }

    running = true;
    start_time = chrono::high_resolution_clock::now();
    return 0;
}

int Timer::stop()
{
    if (!running)
    {
        return -1;
    }

    stop_time = chrono::high_resolution_clock::now();
    elapsed += std::chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);
    running = false;
    return 0;
}

int Timer::result()
{
    return static_cast<int>(elapsed.count());
}