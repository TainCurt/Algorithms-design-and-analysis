#pragma once
#include "Data.h"
#include <cmath>
#include <algorithm>
#include <memory>

template <typename T>
class IntroSortData : public Data<T>
{
public:
    IntroSortData() : Data<T>() {}
    IntroSortData(const IntroSortData<T> &other) : Data<T>(other) {}

    void sort() override
    {
        Introsort(0, this->size - 1);
    }

    void sort_p(int part) override
    {
        Introsort(0, (this->size * part) / 1000 - 1);
    }

    std::unique_ptr<Data<T>> clone() const override
    {
        return std::make_unique<IntroSortData<T>>(*this);
    }

private:
    void InsertionSort(int begin, int end)
    {
        for (int i = begin + 1; i <= end; i++)
        {
            T key = this->array[i];
            int j = i - 1;
            while (j >= begin && this->array[j] > key)
            {
                this->array[j + 1] = this->array[j];
                j--;
            }
            this->array[j + 1] = key;
        }
    }

    int Partition(int low, int high)
    {
        T pivot = this->array[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (this->array[j] <= pivot)
            {
                ++i;
                std::swap(this->array[i], this->array[j]);
            }
        }
        std::swap(this->array[i + 1], this->array[high]);
        return i + 1;
    }

    int MedianOfThree(int a, int b, int c)
    {
        T &A = this->array[a];
        T &B = this->array[b];
        T &C = this->array[c];

        if ((A < B && B < C) || (C < B && B < A))
            return b;
        if ((B < A && A < C) || (C < A && A < B))
            return a;
        return c;
    }

    void IntroSortUtil(int begin, int end, int depthLimit)
    {
        int size = end - begin + 1;

        if (size < 16)
        {
            InsertionSort(begin, end);
            return;
        }

        if (depthLimit == 0)
        {
            std::make_heap(this->array + begin, this->array + end + 1);
            std::sort_heap(this->array + begin, this->array + end + 1);
            return;
        }

        int pivotIndex = MedianOfThree(begin, begin + size / 2, end);
        std::swap(this->array[pivotIndex], this->array[end]);

        int partitionPoint = Partition(begin, end);
        IntroSortUtil(begin, partitionPoint - 1, depthLimit - 1);
        IntroSortUtil(partitionPoint + 1, end, depthLimit - 1);
    }

    void Introsort(int begin, int end)
    {
        int depthLimit = 2 * std::log(end - begin + 1);
        IntroSortUtil(begin, end, depthLimit);
    }
};
