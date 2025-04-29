#include <vector>      // Kontener vector
#include <random>      // Generowanie liczb losowych
#include <type_traits> // Sprawdzanie typu w czasie kompilacji (is_integral, is_floating_point)
#include <memory>      // Smart pointers
#include "Data.h"      // Własna baza danych
#include <fstream>     // Obsługa plików
#include <string>      // Stringi

using namespace std;

// Funkcja generująca wektor losowych wartości typu T
template <typename T>
vector<T> generate_base(int count, T min, T max)
{
    vector<T> base;
    base.reserve(count); // Rezerwujemy pamięć z góry dla wektora
    random_device rd;
    mt19937 gen(rd()); // Generator liczb losowych

    // Jeśli T jest typem całkowitym
    if constexpr (is_integral<T>::value)
    {
        uniform_int_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++)
        {
            base.push_back(dist(gen)); // Dodajemy losową liczbę całkowitą
        }
    }
    // Jeśli T jest typem zmiennoprzecinkowym
    else if constexpr (is_floating_point<T>::value)
    {
        uniform_real_distribution<T> dist(min, max);
        for (int i = 0; i < count; i++)
        {
            base.push_back(dist(gen)); // Dodajemy losową liczbę rzeczywistą
        }
    }

    return base; // Zwracamy wygenerowany wektor
}

// Funkcja tworząca obiekt typu U (pochodnego od Data) i wypełniająca go losowymi danymi
template <typename T, class U>
unique_ptr<U> create_and_fill(int count, T min, T max)
{
    auto values = generate_base<T>(count, min, max); // Generujemy losowe dane
    auto obj = make_unique<U>();                     // Tworzymy unikalny wskaźnik do obiektu typu U
    for (const auto &val : values)
    {
        obj->fill(val); // Wypełniamy obiekt danymi
    }
    return obj; // Zwracamy wskaźnik
}

// Funkcja tworząca obiekt typu U na podstawie danych wczytanych z pliku
template <typename T, class U>
unique_ptr<U> create_and_fill(int count, string path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Failed to open file."; // Obsługa błędu otwarcia pliku
        return nullptr;
    }
    vector<T> data;
    data.resize(count); // Przygotowujemy odpowiednią ilość miejsca
    auto obj = make_unique<U>();
    for (int i = 0; i < count; i++)
    {
        file >> data[i]; // Wczytujemy dane z pliku
        obj->fill(data[i]);
    }
    return obj; // Zwracamy obiekt
}

// Funkcja przygotowująca kilka kopii istniejącego obiektu Data
template <typename T>
vector<unique_ptr<Data<T>>> prepare_copies(const unique_ptr<Data<T>> &original, int count)
{
    vector<unique_ptr<Data<T>>> result;
    result.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        result.push_back(original->clone()); // Klonujemy oryginalny obiekt
    }
    return result;
}

// Funkcja zapisująca dane do pliku
template <typename T>
string save_data(vector<T> data, string path)
{
    ofstream file(path);
    if (!file.is_open())
    {
        return "Failed to open file."; // Obsługa błędu zapisu
    }
    for (size_t i = 0; i < 1000000; ++i)
    {
        file << data[i] << '\n'; // Zapisujemy dane do pliku linia po linii
    }

    file.close();
    return "Data saved successfully."; // Komunikat o sukcesie
}

// Funkcja generująca losowy wektor liczb całkowitych
template <typename T>
vector<T> set_common_data(int size)
{
    vector<T> commonData;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> dist(0, 2000000); // Losowe liczby z zakresu [0, 2_000_000]
    for (int i = 0; i < size; i++)
    {
        commonData.push_back(dist(gen));
    }
    return commonData;
}

// Funkcja generująca wektor liczb całkowitych w kolejności malejącej
template <typename T>
vector<T> set_common_data_reversed(int size)
{
    vector<T> commonData;
    for (int i = size; i >= 0; i--)
    {
        commonData.push_back(i);
    }
    return commonData;
}
