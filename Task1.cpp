#include <iostream>
#include "omp.h"
void Task1_consist(int* a, int n)
{
	double start_time, end_time;
	int sum = 0;
	start_time = omp_get_wtime();
	for (int i = 0; i < n; i++)
		sum += a[i];
	end_time = omp_get_wtime();
	printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", end_time - start_time);

}
void Task1_parallel(int* a, int n, int k)
{
	double start_time, end_time;
	int sum = 0;
	start_time = omp_get_wtime();
#pragma omp parallel reduction (+: sum) num_threads(k)
	{
#pragma omp for 
		for (int i = 0; i < n; i++)
			sum += a[i];
	}

	end_time = omp_get_wtime();
	printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, k);
}
void Task1()
{
	int n = 9999999999;
	printf("========== Задача #1 ==========\n");
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		*(a + i) = rand() % 100 + 1;
	Task1_consist(a, n);
	Task1_parallel(a, n, 1);
	Task1_parallel(a, n, 4);
	Task1_parallel(a, n, 8);
}