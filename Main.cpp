#include <iostream>
#include <ctime>
#include <omp.h>
#include <algorithm>
#include <iterator>
#include "Task3.h"
#include "Task2.h"
#include "Task4.h"
#include "Task1.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    Task4();
}
