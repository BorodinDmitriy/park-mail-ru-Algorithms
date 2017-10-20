/* Бородин Дмитрий, АПО-11 */
/*
Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
Формат входных данных:
На вход подается количество кубиков N.
Формат выходных данных:
Вывести число различных пирамид из N кубиков.

6_1. Высокая пирамида. Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
N ≤ 200.
*/

/*
Решить задачу легко - заводите массив A[N,N], в каждой клетке [K,M] которого будет записано число лесенок из K кубиков, нижний слой которых состоит из M кубиков. Число будет ненулевым, когда M <= K <= M*(M+1)/2. 
Массив заполняется начиная со строчки K=1 по формуле A[K,M]=sum(A[K-M,r],r=1..M-1). Сумма элементов в строчке K=N будет искомым числом.
*/

#include <stdio.h>
#include <stdlib.h>

long** init(int n) 
{
	int count = n + 1;
	long** matr = new long*[count];
	if (!matr) 
	{
		return NULL;
	}
	for (int i = 0; i < count; i++)
	{
		matr[i] = new long[count];
		if (!matr[i]) 
		{
			for (int j = 0; j < i; j++)
			{
				delete[] matr[j];
			}
			delete matr;
			return NULL;
		}
		for (int k = 0; k < count; k++)
		{
			matr[i][k] = 0;
		}
		matr[i][i] = 1;
		matr[i][1] = 1;
	}
	return matr;
}

void print(long** matr, long n)
{
	for (long i = 0; i < n + 1; i++)
	{
		for (long j = 0; j < n + 1; j++)
		{
			printf("%d ", matr[i][j]);
		}
		printf("\n");
	}
}

long solve(long** matr, long n)
{
	for (long i = 3; i <= n; i++)
	{
		for (long j = 2; j < i; j++)
		{
			long sum = 0;
			long index = i - j;
			for (int k = 1; k <= j; k++)
			{
				if (k > index)
				{
					break;
				}
				sum = sum + matr[index][k];
			}
			matr[i][j] = sum;
		}
	}
	long result = 0;
	for (long i = 1; i < n + 1; i++)
	{
		result = result + matr[n][i];
	}
	return result;
}

void free_matr(long** matr, int n)
{
	int count = n + 1;
	for (int i = 0; i < count; i++)
	{
		delete[] matr[i];
	}
	delete[] matr;
}

int main()
{
	long n;
	scanf("%ld", &n);
	long** matr = init(n);
	if (matr) 
	{
		printf("%ld\n", solve(matr, n));
		//print(matr, n);
		free_matr(matr, n);
	}
	return 0;
}