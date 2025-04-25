#pragma once
#include <iostream>
#include <memory>
template <typename T>
class Data
{
protected:
    T *array;
    int size;
    int capacity;

public:
    Data();
    ~Data();
    Data(const Data &other);
    int getsize();
    int getcapacity();
    void fill(T value);
    void show();
    virtual unique_ptr<Data<T>> clone() const = 0;
    virtual void sort() = 0;
    virtual void sort_p(int part) = 0;
};

template <typename T>
Data<T>::Data() : size(0), capacity(1000000)
{
    array = new T[capacity];
}

template <typename T>
Data<T>::Data(const Data &other) : size(other.size), capacity(other.capacity)
{
    array = new T[capacity];
    for (int i = 0; i < size; ++i)
        array[i] = other.array[i];
}

template <typename T>
Data<T>::~Data()
{
    delete[] array;
}

template <typename T>
int Data<T>::getcapacity() { return capacity; }

template <typename T>
int Data<T>::getsize() { return size; }

template <typename T>
void Data<T>::fill(T value)
{
    if (size < capacity)
        array[size++] = value;
    else
        std::cout << "Brak miejsca!\n";
}

template <typename T>
void Data<T>::show()
{
    for (int i = 0; i < size; ++i)
        std::cout << " -> " << array[i];
    std::cout << '\n';
}
