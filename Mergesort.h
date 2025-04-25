#pragma once
#include "Data.h"
template <typename T>
class MergeSortData : public Data<T>
{
public:
    MergeSortData() : Data<T>() {}
    MergeSortData(const MergeSortData<T> &other) : Data<T>(other) {}
    void sort() override
    {
        mergeSort(0, this->size - 1);
    }
    unique_ptr<Data<T>> clone() const override
    {
        return make_unique<MergeSortData<T>>(*this);
    }

private:
    void mergeSort(int left, int right)
    {
        if (left >= right)
            return;
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }

    void merge(int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<T> L(n1), R(n2);
        for (int i = 0; i < n1; ++i)
            L[i] = this->array[left + i];
        for (int i = 0; i < n2; ++i)
            R[i] = this->array[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
            this->array[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        while (i < n1)
            this->array[k++] = L[i++];
        while (j < n2)
            this->array[k++] = R[j++];
    }
};
