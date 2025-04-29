#pragma once
#include "Data.h"

// Szablon klasy MergeSortData dziedziczącej po Data<T>
// Implementuje sortowanie metodą Merge Sort
template <typename T>
class MergeSortData : public Data<T>
{
public:
    // Konstruktor domyślny
    MergeSortData() : Data<T>() {}

    // Konstruktor kopiujący
    MergeSortData(const MergeSortData<T> &other) : Data<T>(other) {}

    // Implementacja funkcji sortującej całą tablicę
    void sort() override
    {
        mergeSort(0, this->size - 1);
    }

    // Implementacja funkcji sortującej część tablicy
    void sort_p(int part) override
    {
        mergeSort(0, (this->size * part) / 1000 - 1);
    }

    // Funkcja klonująca obiekt
    std::unique_ptr<Data<T>> clone() const override
    {
        return std::make_unique<MergeSortData<T>>(*this);
    }

private:
    // Rekurencyjna funkcja Merge Sort
    void mergeSort(int left, int right)
    {
        if (left >= right)
        {
            return; // Warunek zakończenia rekurencji
        }
        int mid = (left + right) / 2;
        mergeSort(left, mid);      // Sortowanie lewej części
        mergeSort(mid + 1, right); // Sortowanie prawej części
        merge(left, mid, right);   // Scalanie posortowanych części
    }

    // Funkcja scalająca dwie posortowane części tablicy
    void merge(int left, int mid, int right)
    {
        int n1 = mid - left + 1; // Rozmiar pierwszej części
        int n2 = right - mid;    // Rozmiar drugiej części

        std::vector<T> L(n1), R(n2); // Pomocnicze tablice

        // Kopiowanie danych do tablic pomocniczych
        for (int i = 0; i < n1; ++i)
        {
            L[i] = this->array[left + i];
        }
        for (int i = 0; i < n2; ++i)
        {
            R[i] = this->array[mid + 1 + i];
        }
        int i = 0, j = 0, k = left;

        // Scalanie tablic pomocniczych z powrotem
        while (i < n1 && j < n2)
        {
            this->array[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        }

        // Kopiowanie pozostałych elementów
        while (i < n1)
        {
            this->array[k++] = L[i++];
        }
        while (j < n2)
        {
            this->array[k++] = R[j++];
        }
    }
};
