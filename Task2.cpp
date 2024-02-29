#include <iostream>
#include <ctime>
#include <omp.h>
#include <algorithm>
#include <iterator>
void Qsort_constent(int a[], int L, int R)
{
    int i = L, j = R, w, x;
    x = a[(L + R) / 2];
    do
    {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i <= j)
        {
            w = a[i]; a[i] = a[j]; a[j] = w;
            i++; j--;
        }
    } while (i < j);
    if (L < j) Qsort_constent(a, L, j);
    if (i < R) Qsort_constent(a, i, R);
}
void Qsort_parallel(int a[], int L, int R, int k)
{
    int i = L, j = R, w, x;
    x = a[(L + R) / 2];
    do
    {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i <= j)
        {
            w = a[i]; a[i] = a[j]; a[j] = w;
            i++; j--;
        }
    } while (i < j);
    {
#pragma omp task shared(a)
        {
            if (L < j) Qsort_parallel(a, L, j, k);
        }
#pragma omp task shared(a)
        {
            if (i < R) Qsort_parallel(a, i, R, k);
        }
    }
#pragma omp taskwait
}
void Task2()
{
    int n = 100000000;
    int* a1 = new int[n];

    printf("========== Задача #2 ==========\n");
    int* a2 = new int[n];
    int* a3 = new int[n];
    int* a4 = new int[n];
    for (int i = 0; i < n; i++)
    {
        a1[i] = rand() % 100 + 1;
    }
    std::copy_n(a1, n, a2);
    std::copy_n(a1, n, a3);
    std::copy_n(a1, n, a4);
    double start_time, end_time;
    start_time = omp_get_wtime();
    Qsort_constent(a2, 0, n - 1);
    end_time = omp_get_wtime();
    printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", end_time - start_time);
    
#pragma omp parallel shared(a1) num_threads(1)
    {
#pragma omp single nowait
        {
            start_time = omp_get_wtime();
            Qsort_parallel(a1, 0, n - 1, 1);
            end_time = omp_get_wtime();
        }
    }
   
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, 1);

#pragma omp parallel shared(a3) num_threads(4)
    {
#pragma omp single nowait
        {
            start_time = omp_get_wtime();
            Qsort_parallel(a3, 0, n - 1, 1);
            end_time = omp_get_wtime();
        }
    }

    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, 4);
  
#pragma omp parallel shared(a4) num_threads(8)
    {
#pragma omp single nowait
        {
            start_time = omp_get_wtime();
            Qsort_parallel(a4, 0, n - 1, 1);
            end_time = omp_get_wtime();
        }
    }
    end_time = omp_get_wtime();
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, 8);

}