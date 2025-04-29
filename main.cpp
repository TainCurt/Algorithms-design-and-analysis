#include <iostream>
#include "Timer.h"
#include "Data.h"
#include "GenerateDataBase.h"
#include "Testsort.h"
#include "Mergesort.h"
#include "Quicksort.h"
#include "Introsort.h"
#include <chrono>
using namespace std;
using namespace std::chrono;
int main()
{
    int data_choice = 0;
    int size = 0;
    int sort_algorithm = 0;
    int prct = 0;
    string file_name = "1mData.txt"; // Domyślnie plik z losowymi danymi

    cout << "This program tests various sorting algorithms." << endl;
    cout << "Please choose your desired algorithm, data source, size, and sort percentage." << endl;

    cout << "Choose sorting algorithm: " << endl;
    cout << "1. Quick Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cout << "3. Intro Sort" << endl;
    cout << "Your choice: ";
    cin >> sort_algorithm;
    cout << endl;
    cout << "Enter desired data size (from 0 to 1,000,000): ";
    cin >> size;
    cout << endl;
    cout << "Choose your data source: " << endl;
    cout << "1. Random generated" << endl;
    cout << "2. Loaded from file" << endl;
    cout << "3. Sorted in reverse" << endl;
    cout << "Your choice: ";
    cin >> data_choice;

    // Wybór pliku na podstawie typu danych

    if (data_choice == 3)
    {
        file_name = "reversedData.txt";
    }

    if (data_choice == 1 || data_choice == 2)
    {
        cout << endl;
        cout << "Choose the percentage of data to be pre-sorted: " << endl;
        cout << "1. 0%" << endl;
        cout << "2. 25%" << endl;
        cout << "3. 50%" << endl;
        cout << "4. 75%" << endl;
        cout << "5. 95%" << endl;
        cout << "6. 99%" << endl;
        cout << "7. 99.7%" << endl;
        cout << "Your choice: ";
        cin >> prct;
    }

    // Przekształć wybór procentowy na wartość liczbową
    int percent[] = {0, 250, 500, 750, 950, 990, 997};
    float sorted_percent = 0.0f;
    if (data_choice == 1 || data_choice == 2)
    {
        if (prct >= 1 && prct <= 7)
        {
            sorted_percent = static_cast<float>(percent[prct - 1]) / 1000.0f;
        }
    }

    Timer timer;
    int repetitions = 100;

    if (sort_algorithm == 1)
    {
        unique_ptr<Data<int>> quicksort;
        if (data_choice == 1)
        {
            quicksort = create_and_fill<int, QuickSortData<int>>(size, 0, 1000000);
        }
        else
        {
            quicksort = create_and_fill<int, QuickSortData<int>>(size, file_name);
        }
        auto tests = prepare_copies<>(quicksort, repetitions);

        for (int k = 0; k < repetitions; k++)
        {
            if (data_choice != 3 && percent[prct - 1] != 0)
            {
                tests[k]->sort_p(percent[prct - 1]);
            }

            timer.start();
            tests[k]->sort();
            timer.stop();
        }
        cout << "QuickSort: " << size << " elements, sorted " << sorted_percent * 100 << "%. Avg time: " << timer.result() / repetitions << " ms" << endl;
    }
    else if (sort_algorithm == 2)
    {
        unique_ptr<Data<int>> mergesort;
        if (data_choice == 1)
        {
            mergesort = create_and_fill<int, QuickSortData<int>>(size, 0, 1000000);
        }
        else
        {
            mergesort = create_and_fill<int, MergeSortData<int>>(size, file_name);
        }
        auto tests = prepare_copies(mergesort, repetitions);

        for (int k = 0; k < repetitions; k++)
        {
            if (data_choice != 3 && percent[prct - 1] != 0)
            {
                tests[k]->sort_p(percent[prct - 1]);
            }

            timer.start();
            tests[k]->sort();
            timer.stop();
        }
        cout << "MergeSort: " << size << " elements, sorted " << sorted_percent * 100 << "%. Avg time: " << timer.result() / repetitions << " ms" << endl;
    }
    else if (sort_algorithm == 3)
    {
        unique_ptr<Data<int>> introsort;
        if (data_choice == 1)
        {
            introsort = create_and_fill<int, QuickSortData<int>>(size, 0, 1000000);
        }
        else
        {
            introsort = create_and_fill<int, MergeSortData<int>>(size, file_name);
        }
        auto tests = prepare_copies(introsort, repetitions);

        for (int k = 0; k < repetitions; k++)
        {
            if (data_choice != 3 && percent[prct - 1] != 0)
            {
                tests[k]->sort_p(percent[prct - 1]);
            }

            timer.start();
            tests[k]->sort();
            timer.stop();
        }
        cout << "IntroSort: " << size << " elements, sorted " << sorted_percent * 100 << "%. Avg time: " << timer.result() / repetitions << " ms" << endl;
    }
    else
    {
        cout << "Invalid sorting algorithm selected." << endl;
    }

    return 0;
}