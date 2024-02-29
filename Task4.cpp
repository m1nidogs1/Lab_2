#include <iostream>
#include <omp.h>

double consistent2(int n)
{
    double start_time, end_time;
    int** a = new int*[n];
    int** b = new int*[n];
    int** res = new int*[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        b[i] = new int[n];
        res[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
        for (int j=0;j<n;j++)
        {
            *(*(a+i)+j) = rand() % 100 + 1;
            *(*(b + i) + j) = rand() % 100 + 1;
        }
    start_time = omp_get_wtime();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
        *(*(res+i)+j) = *(*(a + i) + j) + *(*(b + i) + j);
        *(*(res + i) + j) = *(*(a + i) + j) - *(*(b + i) + j);
        *(*(res + i) + j) = *(*(a + i) + j) * *(*(b + i) + j);
        *(*(res + i) + j) = *(*(a + i) + j) / *(*(b + i) + j);
        }
    end_time = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        delete a[i];
        delete b[i];
        delete res[i];
    }
    delete a;
    delete b;
    delete res;
    return end_time - start_time;
    //printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", end_time - start_time);
}
double parallel(int n, int k)
{
    double start_time, end_time;
    int** a = new int* [n];
    int** b = new int* [n];
    int** res = new int* [n];


        for (int i = 0; i < n; i++)
        {
            a[i] = new int[n];
            b[i] = new int[n];
            res[i] = new int[n];
        }
        
        for (int i = 0; i < n; i++)

            for (int j = 0; j < n; j++)
            {
                *(*(a + i) + j) = rand() % 100 + 1;
                *(*(b + i) + j) = rand() % 100 + 1;
            }
        start_time = omp_get_wtime();
#pragma omp parallel num_threads(k)
        {
#pragma omp for
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    *(*(res + i) + j) = *(*(a + i) + j) + *(*(b + i) + j);
                    *(*(res + i) + j) = *(*(a + i) + j) - *(*(b + i) + j);
                    *(*(res + i) + j) = *(*(a + i) + j) * *(*(b + i) + j);
                    *(*(res + i) + j) = *(*(a + i) + j) / *(*(b + i) + j);
                }
            }
        }
    end_time = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        delete a[i];
        delete b[i];
        delete res[i];
    }
    
    delete a;
    delete b;
    delete res;
    return end_time - start_time;
    
    //printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, k);
}
void Task4()
{
    int n = 30000;
    printf("========== Задача #4 ==========\n");
    int res = 1;
    double avg_time = 0;
    for (int i = 0; i < res; i++)
        avg_time += consistent2(n);
    avg_time /= res;
    printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", avg_time);
    avg_time = 0;
    for (int i = 0; i < res; i++)
        avg_time += parallel(n, 1);
    avg_time /= res;
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", avg_time, 1);
    avg_time = 0;
    for (int i = 0; i < res; i++)
        avg_time += parallel(n, 4);
    avg_time /= res;
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", avg_time, 4);
    avg_time = 0;
    for (int i = 0; i < res; i++)
        avg_time += parallel(n, 8);
    avg_time /= res;
    printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", avg_time, 8);
}