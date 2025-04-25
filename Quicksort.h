#pragma once
#include "Data.h"
#include <vector>
template <typename T>
class QuickSortData : public Data<T>
{
public:
    QuickSortData() : Data<T>() {}

    QuickSortData(const QuickSortData<T> &other) : Data<T>(other) {}

    void sort() override
    {
        quicksort(0, this->size - 1);
    }

    void sort_p(int part) override
    {
        quicksort(0, (this->size * part) / 1000 - 1);
    }

    unique_ptr<Data<T>> clone() const override
    {
        return make_unique<QuickSortData<T>>(*this);
    }

private:
    void quicksort(int low, int high)
    {
        if (low < high)
        {
            int pi = partition(low, high);
            quicksort(low, pi - 1);
            quicksort(pi + 1, high);
        }
    }

    T partition(int low, int high)
    {
        T pivot = this->array[high];
        int i = low - 1;
        for (int j = low; j < high; ++j)
        {
            if (this->array[j] < pivot)
            {
                ++i;
                std::swap(this->array[i], this->array[j]);
            }
        }
        std::swap(this->array[i + 1], this->array[high]);
        return i + 1;
    }
}

;