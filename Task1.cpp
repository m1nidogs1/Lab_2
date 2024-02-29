#include <iostream>
#include "omp.h"
double Task1_consist(int* a, int n)
{
	double start_time, end_time;
	int sum = 0;
	start_time = omp_get_wtime();
	for (int i = 0; i < n; i++)
		sum += a[i];
	end_time = omp_get_wtime();
	//printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", end_time - start_time);
	return end_time - start_time;

}
double Task1_parallel(int* a, int n, int k)
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
	//printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", end_time - start_time, k);
	return end_time - start_time;
}
void Task1()
{
	int n = 9999999999;
	printf("========== Задача #1 ==========\n");
	int* a = new int[n];
	for (int i = 0; i < n; i++)
		*(a + i) = rand() % 100 + 1;
	double res = 0;
	for (int i =0;i< 10000;i++)
		res += Task1_consist(a, n);
	res /= 10000;
	printf("Последовательный вариант\nВремя на замер времени %lf\n===============================\n", res);
	res = 0;
	for (int i = 0; i < 10000; i++)
		res += Task1_parallel(a, n, 1);
	res /= 10000;
	printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", res, 1);
	res = 0;
	for (int i = 0; i < 10000; i++)
		res += Task1_parallel(a, n, 4);
	res /= 10000;
	printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", res, 4);
	res = 0;
	for (int i = 0; i < 10000; i++)
		res += Task1_parallel(a, n, 8);
	res /= 10000;
	printf("Параллельный вариант\nВремя на замер времени %lf\nКоличество потоков %d\n===============================\n", res, 8);
}