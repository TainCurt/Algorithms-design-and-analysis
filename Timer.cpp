#include "Timer.h"

// Konstruktor domyślny - od razu resetuje timer
Timer::Timer()
{
    reset();
}

// Funkcja resetująca timer do stanu początkowego
void Timer::reset()
{
    running = false;                                          // Timer nie działa
    elapsed = chrono::milliseconds(0);                        // Zresetowany czas na
    start_time = chrono::high_resolution_clock::time_point(); // Zerowanie punktu startowego
    stop_time = chrono::high_resolution_clock::time_point();  // Zerowanie punktu końcowego
}

// Funkcja rozpoczynająca pomiar czasu
// Zwraca 0 jeśli OK, -1 jeśli timer już działa
int Timer::start()
{
    if (running)
    {
        return -1; // Timer już działa, nie można uruchomić ponownie
    }

    running = true;
    start_time = chrono::high_resolution_clock::now(); // Zapisujemy aktualny czas jako początek
    return 0;
}

// Funkcja zatrzymująca pomiar czasu
// Zwraca 0 jeśli OK, -1 jeśli timer nie był uruchomiony
int Timer::stop()
{
    if (!running)
    {
        return -1; // Timer nie był uruchomiony
    }

    stop_time = chrono::high_resolution_clock::now();                                    // Zapisujemy aktualny czas jako koniec
    elapsed += std::chrono::duration_cast<chrono::milliseconds>(stop_time - start_time); // Dodajemy różnicę czasu do elapsed
    running = false;                                                                     // Timer przestaje działać
    return 0;
}

// Funkcja zwracająca zmierzony czas w milisekundach
int Timer::result()
{
    return static_cast<int>(elapsed.count());
}
