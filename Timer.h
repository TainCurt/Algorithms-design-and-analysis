#pragma once
#include <chrono>
using namespace std;

class Timer
{
private:
    bool running;
    chrono::high_resolution_clock::time_point start_time;
    chrono::high_resolution_clock::time_point stop_time;
    chrono::milliseconds elapsed;

public:
    Timer();
    //~Timer();
    void reset();
    int start();
    int stop();
    int result();
};
