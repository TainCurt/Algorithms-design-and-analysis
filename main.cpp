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
    unique_ptr<Data<float>> base = create_and_fill<float, IntroSortData<float>>(20, 0, 100);
    base->show();
    cout << endl;
    base->sort();
    base->show();
}
