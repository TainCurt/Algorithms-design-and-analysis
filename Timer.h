#pragma once
#include <chrono>

using namespace std;

// Klasa Timer - prosty stoper do mierzenia czasu działania
class Timer
{
private:
    bool running;                                         // Czy timer jest aktualnie uruchomiony?
    chrono::high_resolution_clock::time_point start_time; // Moment rozpoczęcia pomiaru
    chrono::high_resolution_clock::time_point stop_time;  // Moment zakończenia pomiaru
    chrono::milliseconds elapsed;                         // Przechowywany zmierzony czas

public:
    // Konstruktor domyślny
    Timer();

    //~Timer();

    // Resetuje timer do stanu początkowego
    void reset();

    // Rozpoczyna pomiar czasu
    int start();

    // Kończy pomiar czasu
    int stop();

    // Zwraca zmierzony czas
    int result();
};
