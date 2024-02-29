#include <iostream>
#include <omp.h>

void consistent2(int n)
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
    
    printf("���������������� �������\n����� �� ����� ������� %lf\n===============================\n", end_time - start_time);
}
void parallel(int n, int k)
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
            for (int j = 0; j < n; j++)
            {
                *(*(res + i) + j) = *(*(a + i) + j) + *(*(b + i) + j);
                *(*(res + i) + j) = *(*(a + i) + j) - *(*(b + i) + j);
                *(*(res + i) + j) = *(*(a + i) + j) * *(*(b + i) + j);
                *(*(res + i) + j) = *(*(a + i) + j) / *(*(b + i) + j);
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
    
    printf("������������ �������\n����� �� ����� ������� %lf\n���������� ������� %d\n===============================\n", end_time - start_time, k);
}
void Task4()
{
    int n = 30000;
    printf("========== ������ #4 ==========\n");
    consistent2(n);
    parallel(n, 1);
    parallel(n, 4);
    parallel(n, 8);
}