/* Бородин Дмитрий, АПО-11 */
/*
3_2. Дан массив целых чисел А[0..n­1]. Известно, что на интервале [0, m] значения массива строго
возрастают, а на интервале [m, n­1] строго убывают. Найти m за O(log m).
2 ≤ n ≤ 10000.
*/

#include <iostream>

int find(int *arr, int left, int right) {
	if (right - left == 0) {
		return right;
	}

	if (arr[(left + right) / 2] < arr[(left + right) / 2 + 1]) {
		return find(arr, (left + right) / 2 + 1, right);
	} else {
		return find(arr, left, (left + right) / 2);
	}
}

int findNumber(int *arr, int size) {
	if (arr[0] > arr[1]) {
		return 0;
	}
	int left = 1;
	int right = 2;
	while (left <= size) {
		if (right > size)
			right = size;
		if ((arr[right] < arr[right - 1]) && (arr[right] > arr[right + 1])){
			return find(arr, left, right);
		} else {
			left <<= 1;
			right <<= 1;
		}
	}
	return size;
}

int main() {
	int size = 0;
	std::cin >> size;
	int *arr = new int[size];

	for (int i = 0; i < size; ++i) {
		std::cin >> arr[i];
	}
	std::cout << findNumber(arr, size - 1);
	delete[] arr;
	return 0;
}