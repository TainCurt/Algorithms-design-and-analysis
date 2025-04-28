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
int benchmark()
{
    Timer timer;
    int size_to_sort[] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int percent[] = {0, 250, 500, 750, 950, 990, 997};
    for (int i = 0; i < sizeof(size_to_sort) / sizeof(size_to_sort[0]); i++)
    {
        unique_ptr<Data<int>> quicksort = create_and_fill<int, QuickSortData<int>>(size_to_sort[i], "1mData.txt");
        unique_ptr<Data<int>> mergesort = create_and_fill<int, MergeSortData<int>>(size_to_sort[i], "1mData.txt");
        unique_ptr<Data<int>> introsort = create_and_fill<int, IntroSortData<int>>(size_to_sort[i], "1mData.txt");

        vector<unique_ptr<Data<int>>> test_quicksort = prepare_copies(quicksort, 100);
        vector<unique_ptr<Data<int>>> test_mergesort = prepare_copies(mergesort, 100);
        vector<unique_ptr<Data<int>>> test_introsort = prepare_copies(introsort, 100);
        for (int j = 0; j < sizeof(percent) / sizeof(percent[0]); j++)
        {
            float sorted_percent = static_cast<float>(percent[j]) / 1000.0f;
            if (percent[j] == 0)
            {
                for (int k = 0; k < 100; k++)
                {
                    timer.start();
                    test_quicksort[k]->sort();
                    timer.stop();
                }
                cout << "Quicksort " << size_to_sort[i] << " elementow. Posortowane 0%. Czas: " << timer.result() << endl;
                timer.reset();

                for (int k = 0; k < 100; k++)
                {
                    timer.start();
                    test_mergesort[k]->sort();
                    timer.stop();
                }
                cout << "Mergesort " << size_to_sort[i] << " elementow. Posortowane 0%. Czas: " << timer.result() << endl;
                timer.reset();

                for (int k = 0; k < 100; k++)
                {
                    timer.start();
                    test_introsort[k]->sort();
                    timer.stop();
                }
                cout << "Introsort " << size_to_sort[i] << " elementow. Posortowane 0%. Czas: " << timer.result() << endl;
                timer.reset();
                cout << endl;
            }
            else
            {
                for (int k = 0; k < 100; k++)
                {
                    test_quicksort[k]->sort_p(percent[j]);
                    timer.start();
                    test_quicksort[k]->sort();
                    timer.stop();
                }
                cout << "Quicksort " << size_to_sort[i] << " elementow. Posortowane " << sorted_percent * 100 << "%. Czas: " << timer.result() << endl;
                timer.reset();

                for (int k = 0; k < 100; k++)
                {
                    test_mergesort[k]->sort_p(percent[j]);
                    timer.start();
                    test_mergesort[k]->sort();
                    timer.stop();
                }

                cout << "Mergesort " << size_to_sort[i] << " elementow. Posortowane " << sorted_percent * 100 << "%. Czas: " << timer.result() << endl;
                timer.reset();

                for (int k = 0; k < 100; k++)
                {
                    test_introsort[k]->sort_p(percent[j]);
                    timer.start();
                    test_introsort[k]->sort();
                    timer.stop();
                }
                cout << "Introsort " << size_to_sort[i] << " elementow. Posortowane " << sorted_percent * 100 << "%. Czas: " << timer.result() << endl;
                timer.reset();
                cout << endl;
            }
        }
    }
}