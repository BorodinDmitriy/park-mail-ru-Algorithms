/* Бородин Дмитрий, АПО-11 */
/**
2_3. 
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k. Найти количество
таких пар индексов (i, j), что A[i] + B[j] = k. Время работы O(n + m).
n, m ≤ 100000.
Указание. Обходите массив B от конца к началу.
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int countIndexPairs(int *arrA, int *arrB, int lenA, int lenB, int k) {
	int lastIndex = 0;
	int result = 0;

	for (int i = lenB - 1; i >= 0; i--){
		int b = arrB[i];

		for (int j = lastIndex; j < lenA; j++) {
			int sum = b + arrA[j];
			if (sum == k){
				result++;
			} else {
				if (sum > k) {
					lastIndex = j;
					break;
				}
			}
		}
	}
	return result;
}

int main()
{
	int lenA = 0;
	int lenB = 0;
	int *arrA = NULL;
	int *arrB = NULL;
	int k = 0;

	if (scanf("%d", &lenA) != 1) {
		return 0;
	}
	assert(lenA > 0);

	arrA = (int *) malloc(lenA * sizeof(int));
	for (int i = 0; i < lenA; i++) {
		if (scanf("%d", arrA + i) != 1) {
			free(arrA);
			return 0;
		}
	}

	if (scanf("%d", &lenB) != 1) {
		return 0;
	}
	assert(lenB > 0);

	arrB = (int *) malloc(lenB * sizeof(int));
	for (int i = 0; i < lenB; i++) {
		if (scanf("%d", arrB + i) != 1) {
			free(arrA);
			free(arrB);
			return 0;
		}
	}

	if (scanf("%d", &k) != 1) {
		free(arrA);
		free(arrB);
		return 0;
	}
	assert(k > 0);

	int result = countIndexPairs(arrA, arrB, lenA, lenB, k);
	printf("%d", result);
	return 0;
}