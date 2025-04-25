#pragma once
#include "Data.h"
#include <cmath>
#include <algorithm>

template <typename T>
class IntroSortData : public Data<T>
{
public:
    IntroSortData() : Data<T>() {}
    IntroSortData(const IntroSortData<T> &other) : Data<T>(other) {}

    void sort() override
    {
        Introsort(this->array, this->array + this->size - 1);
    }

    std::unique_ptr<Data<T>> clone() const override
    {
        return make_unique<IntroSortData<T>>(*this);
    }

private:
    void InsertionSort(T *begin, T *end)
    {
        for (T *i = begin + 1; i <= end; ++i)
        {
            T key = *i;
            T *j = i - 1;
            while (j >= begin && *j > key)
            {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }

    T *Partition(T *low, T *high)
    {
        T pivot = *high;
        T *i = low - 1;
        for (T *j = low; j < high; ++j)
        {
            if (*j <= pivot)
            {
                ++i;
                std::swap(*i, *j);
            }
        }
        std::swap(*(i + 1), *high);
        return i + 1;
    }

    T *MedianOfThree(T *a, T *b, T *c)
    {
        if ((*a < *b && *b < *c) || (*c <= *b && *b <= *a))
            return b;
        if ((*a < *c && *c <= *b) || (*b <= *c && *c < *a))
            return c;
        return a;
    }

    void IntroSortUtil(T *begin, T *end, int depthLimit)
    {
        int size = end - begin + 1;
        if (size < 16)
        {
            InsertionSort(begin, end);
            return;
        }

        if (depthLimit == 0)
        {
            std::make_heap(begin, end + 1);
            std::sort_heap(begin, end + 1);
            return;
        }

        T *pivot = MedianOfThree(begin, begin + size / 2, end);
        std::swap(*pivot, *end);
        T *partitionPoint = Partition(begin, end);

        IntroSortUtil(begin, partitionPoint - 1, depthLimit - 1);
        IntroSortUtil(partitionPoint + 1, end, depthLimit - 1);
    }

    void Introsort(T *begin, T *end)
    {
        int depthLimit = 2 * std::log(end - begin + 1);
        IntroSortUtil(begin, end, depthLimit);
    }
};
