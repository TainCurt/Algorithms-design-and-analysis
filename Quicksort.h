#pragma once
#include "Data.h"
#include <vector>

// Szablon klasy QuickSortData dziedziczącej po Data<T>
// Implementuje sortowanie metodą QuickSort
template <typename T>
class QuickSortData : public Data<T>
{
public:
    // Konstruktor domyślny
    QuickSortData() : Data<T>() {}

    // Konstruktor kopiujący
    QuickSortData(const QuickSortData<T> &other) : Data<T>(other) {}

    // Funkcja sortująca całą tablicę
    void sort() override
    {
        quicksort(0, this->size - 1);
    }

    // Funkcja sortująca część tablicy
    void sort_p(int part) override
    {
        quicksort(0, (this->size * part) / 1000 - 1);
    }

    // Funkcja klonująca obiekt
    std::unique_ptr<Data<T>> clone() const override
    {
        return std::make_unique<QuickSortData<T>>(*this);
    }

private:
    // Rekurencyjna funkcja wykonująca QuickSort
    void quicksort(int low, int high)
    {
        if (low < high)
        {
            int pi = partition(low, high); // Znalezienie punktu podziału
            quicksort(low, pi - 1);        // Rekurencyjne sortowanie lewej części
            quicksort(pi + 1, high);       // Rekurencyjne sortowanie prawej części
        }
    }

    // Funkcja dzieląca tablicę na dwie części względem pivota
    int partition(int low, int high)
    {
        T pivot = this->array[high]; // Pivot to ostatni element
        int i = low - 1;

        // Przesuwanie elementów mniejszych niż pivot na lewą stronę
        for (int j = low; j < high; ++j)
        {
            if (this->array[j] < pivot)
            {
                ++i;
                std::swap(this->array[i], this->array[j]); // Zamiana miejscami
            }
        }
        // Umieszczenie pivota na właściwym miejscu
        std::swap(this->array[i + 1], this->array[high]);
        return i + 1;
    }
};
