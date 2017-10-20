/* Бородин Дмитрий, АПО-11*/
/*
1_5. Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и вычитания (умножением пользоваться нельзя).
n ≤ 1000.
*/

#include <iostream>

using namespace std;
void printSqrs(ostream& out, int n)
{
	unsigned int num = 1;
	unsigned int add = 1;
	while (add <= n) {
		out << num << " ";
		num = num + add + add + 1;
		add++;
	}
}

int main()
{
    int n;
    std::cin >> n;
    printSqrs(cout, n);
    return 0;
}