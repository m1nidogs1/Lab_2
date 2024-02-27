#include <iostream>
#include <omp.h>

void consistent(int n)
{
    double start_time, end_time;
    int* a = new int[n];
    int* b = new int[n];
    int* res = new int[n];
    start_time = omp_get_wtime();

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100 + 1;
        b[i] = rand() % 100 + 1;
    }
    for (int i = 0; i < n; i++)
    {
        res[i] = a[i] + b[i];
        res[i] = a[i] - b[i];
        res[i] = a[i] * b[i];
        res[i] = a[i] / b[i];
    }

    end_time = omp_get_wtime();
    printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", end_time - start_time);
}
void parall(int n, int k)
{
    double start_time, end_time;

    int* a = new int[n];
    int* b = new int[n];
    int* res = new int[n];
    start_time = omp_get_wtime();
#pragma omp parallel num_threads(k)
    {
#pragma omp for 
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % 100 + 1;
            b[i] = rand() % 100 + 1;
        }
#pragma omp for 
        for (int i = 0; i < n; i++)
        {
            res[i] = a[i] + b[i];
            res[i] = a[i] - b[i];
            res[i] = a[i] * b[i];
            res[i] = a[i] / b[i];
        }
    }
    end_time = omp_get_wtime();
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, k);
}
void Task_3()
{
    int n = 100000000;
    printf("========== Задача #3 ==========\n");
    consistent(n);
    parall(n, 1);
    parall(n, 4);
    parall(n, 8);
}