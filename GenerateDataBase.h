#include <vector>
#include <random>
#include <type_traits>
#include <memory>
#include "Data.h"
#include <fstream>
#include <string>

using namespace std;

template <typename T>
vector<T> generate_base(int count, T min, T max)
{
    vector<T> base;
    base.reserve(count);
    random_device rd;
    mt19937 gen(rd());

    if constexpr (is_integral<T>::value)
    {
        uniform_int_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++)
        {
            base.push_back(dist(gen));
        }
    }
    else if constexpr (is_floating_point<T>::value)
    {
        uniform_real_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++)
        {
            base.push_back(dist(gen));
        }
    }

    return base;
}

template <typename T, class U>
unique_ptr<U> create_and_fill(int count, T min, T max)
{
    auto values = generate_base<T>(count, min, max);
    auto obj = make_unique<U>();
    for (const auto &val : values)
    {
        obj->fill(val);
    }
    return obj;
}

template <typename T, class U>
unique_ptr<U> create_and_fill(int count, string path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Failed to open file.";
        return nullptr;
    }
    vector<T> data;
    data.resize(count);
    auto obj = make_unique<U>();
    for (int i = 0; i < count; i++)
    {
        file >> data[i];
        obj->fill(data[i]);
    }
    return obj;
}

template <typename T>
vector<unique_ptr<Data<T>>> prepare_copies(const unique_ptr<Data<T>> &original, int count)
{
    vector<unique_ptr<Data<T>>> result;
    result.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(original->clone());
    }
    return result;
}

template <typename T>
string save_data(vector<T> data, string path)
{
    ofstream file(path);
    if (!file.is_open())
    {
        return "Failed to open file.";
    }
    for (size_t i = 0; i < 1000000; ++i)
    {
        file << data[i] << '\n';
    }

    file.close();
    return "Data saved successfully.";
}

template <typename T>
vector<T> set_common_data(int size)
{
    vector<int> commonData;
    // srand(time(0));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> dist(0, 2000000);
    for (int i = 0; i < size; i++)
    {
        // commonData.push_back(rand() % 2000000);
        commonData.push_back(dist(gen));
    }
    return commonData;
}

template <typename T>
vector<T> set_common_data_reversed(int size)
{
    vector<int> commonData;

    for (int i = size; i >= 0; i--)
    {
        commonData.push_back(i);
    }
    return commonData;
}
