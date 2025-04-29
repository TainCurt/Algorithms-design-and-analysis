#pragma once
#include <iostream>
#include <memory>

// Szablon klasy Data przechowującej dane typu T
template <typename T>
class Data
{
protected:
    T *array;     // Wskaźnik na dynamiczną tablicę elementów typu T
    int size;     // Aktualna liczba elementów w tablicy
    int capacity; // Maksymalna pojemność tablicy

public:
    Data();                                             // Konstruktor domyślny
    ~Data();                                            // Destruktor
    Data(const Data &other);                            // Konstruktor kopiujący
    int getsize();                                      // Zwraca aktualny rozmiar (ilość elementów)
    int getcapacity();                                  // Zwraca pojemność tablicy
    void fill(T value);                                 // Dodaje nowy element do tablicy
    void show();                                        // Wyświetla wszystkie elementy
    virtual std::unique_ptr<Data<T>> clone() const = 0; // Wirtualna funkcja klonująca
    virtual void sort() = 0;                            // Wirtualna funkcja sortująca wszystkie elementy
    virtual void sort_p(int part) = 0;                  // Wirtualna funkcja sortująca część elementów
};

template <typename T>
Data<T>::Data() : size(0), capacity(1000000) // Domyślna pojemność: 1 milion
{
    array = new T[capacity];
}

// Implementacja konstruktora kopiującego
template <typename T>
Data<T>::Data(const Data &other) : size(other.size), capacity(other.capacity)
{
    array = new T[capacity];
    for (int i = 0; i < size; ++i)
        array[i] = other.array[i];
}

// Implementacja destruktora
template <typename T>
Data<T>::~Data()
{
    delete[] array;
}

// Zwraca pojemność tablicy
template <typename T>
int Data<T>::getcapacity() { return capacity; }

// Zwraca aktualny rozmiar tablicy
template <typename T>
int Data<T>::getsize() { return size; }

// Dodaje element do tablicy
template <typename T>
void Data<T>::fill(T value)
{
    if (size < capacity)
        array[size++] = value; // Dodanie elementu i zwiększenie rozmiaru
    else
        std::cout << "No more space!\n"; // Informacja o braku miejsca
}

// Wyświetla wszystkie elementy tablicy
template <typename T>
void Data<T>::show()
{
    for (int i = 0; i < size; ++i)
        std::cout << " -> " << array[i];
    std::cout << '\n';
}
