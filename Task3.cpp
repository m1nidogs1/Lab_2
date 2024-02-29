#include <iostream>
#include <omp.h>

double consistent(int n)
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
    return end_time - start_time;
    //printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", end_time - start_time);
}
double parall(int n, int k)
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
    return end_time - start_time;
    //printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, k);
}
void Task3()
{
    int n = 100000000;
    int res = 10000;
    double avg_time = 0;
    printf("========== Задача #3 ==========\n");
    for (int i=0;i<res;i++)
        avg_time += consistent(n);
    avg_time /= res;
    printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", avg_time);
    avg_time = 0;
    for (int i = 0; i < res; i++)
        avg_time += parall(n, 1);
    avg_time /= res;
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", avg_time, 1);
    avg_time = 0;
    for (int i = 0; i < res; i++)
            avg_time += parall(n, 4);
    avg_time /= res;
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", avg_time, 4);
    avg_time = 0;
    for (int i = 0; i < res; i++)
        avg_time += parall(n, 8);
    avg_time /= res;
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", avg_time, 8);
    
}