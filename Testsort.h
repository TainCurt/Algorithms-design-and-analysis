#pragma once
#include "Data.h"

template <typename T>
class BubbleSortData : public Data<T>
{
public:
    BubbleSortData() : Data<T>() {}

    BubbleSortData(const BubbleSortData<T> &other) : Data<T>(other) {}

    void sort() override
    {
        for (int i = 0; i < this->size - 1; ++i)
            for (int j = 0; j < this->size - i - 1; ++j)
                if (this->array[j] > this->array[j + 1])
                    std::swap(this->array[j], this->array[j + 1]);
    }

    unique_ptr<Data<T>> clone() const override
    {
        return make_unique<BubbleSortData<T>>(*this);
    }
};
