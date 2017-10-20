/* Бородин Дмитрий, АПО-11 */
/*
5_2. Дано выражение в инфиксной записи. Вычислить его, используя перевод выражения в постфиксную запись. Выражение не содержит отрицительных чисел.
Количество операций ≤ 100.
Формат входных данных. Строка, состоящая их символов “0123456789-+/()”
Гарантируется, что входное выражение корректно, нет деления на 0, вычислимо в целых числах. Деление целочисленное.
Формат выходных данных. 
Значение выражения.

*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>

#define DEFAULT_CAPACITY 1024

template<typename T>
class myStack
{
private:
	size_t size; // cur_size
	size_t capacity; // capacity
	T* buffer;
public:
	myStack(size_t sz = 1024);
	~myStack();
	void reallocate();
	const size_t getSize() { return size; }
	void push(const T&);
	const T pop();
	const T top();
	void clear();
};

template<typename T>
myStack<T>::myStack(size_t sz)
{
	buffer = new T[sz];
	capacity = sz;
	size = 0;
}

template<typename T>
myStack<T>::~myStack()
{
	delete [] buffer;
}

template<typename T>
void myStack<T>::clear()
{
	T *tmp = new T[DEFAULT_CAPACITY];
	if (tmp)
	{
		delete [] buffer;
		buffer = tmp;
		capacity = DEFAULT_CAPACITY;
		size = 0;
		
	}
}

template<typename T>
void myStack<T>::push(const T& value)
{
	if (size == capacity)
	{
		reallocate();
	}
	
	buffer[size] = value;
	size++;
}

template<typename T>
const T myStack<T>::pop()
{
	T result;
	if (size == 0)
	{
		return -1;
	}
	result = buffer[--size];
	return result;
}

template<typename T>
const T myStack<T>::top()
{
	if (size == 0)
	{
		return -1;
	}
	T result = buffer[size - 1];
	return result;
}

template<typename T>
void myStack<T>::reallocate()
{
	T *tmp = new T[capacity * 2 + 1];
	if (tmp)
	{
		for (int i = 0; i < capacity; i++)
		{
			tmp[i] = buffer[i];
		}
		capacity = capacity * 2 + 1;
		delete [] buffer;
		buffer = tmp;
	}
}


int priority(char c)
{
	switch(c){
        case '|':
            return 0;
            break;
        case '+':
            return 1;
            break;
        case '-':
            return 2;
            break;
        case '*':
            return 3;
            break;
        case '/':
            return 4;
            break;
        case '(':
            return 5;
            break;
        case ')':
            return 6;
            break;
    }
    return -1;
}

// алгоритм Дейкстры обратной польской записи https://habrahabr.ru/post/100869/
void makePolishString(char* input, int* nums, int& n)
{
	int map[6][7] = { {4, 1, 1, 1, 1, 1, 5},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 1, 1, 1, 2},
                    {2, 2, 2, 2, 2, 1, 2},
                    {2, 2, 2, 2, 2, 1, 2},
                    {5, 1, 1, 1, 1, 1, 3} };
    int tmpNum, tmp, length;
    myStack<int> st;
    st.push(0);
    length = strlen(input);
    input[length++] = '|';

    for (int i = 0; i < length; i++)
    {
    	if (input[i] != ' ')
    	{
    		if (isdigit(input[i]))
    		{
    			sscanf(input + i, "%i", &tmpNum);
    			while (isdigit(input[i + 1]))
    				i++;
    			nums[n++] = tmpNum;
    		} else {
    			while (map[st.top()][priority(input[i])] == 2) 
    			{
    				tmp = st.pop();
    				nums[n++] = -tmp;
    			}
    			if (map[st.top()][priority(input[i])] == 1) 
    			{
    				st.push(priority(input[i]));
    			}
    			if (map[st.top()][priority(input[i])] == 3) 
    			{
    				st.pop();
    			}
    		}
    	}
    }
    st.clear();
    return;
}

int calculate(int* nums, int n)
{
	myStack<int> st;
	int b, a, result;

	for (int i = 0; i < n; i++)
	{
		if (nums[i] >= 0)
			st.push(nums[i]);
		else 
		{
			b = st.pop();
			a = st.pop();
			switch(nums[i]){
                case -1:
                    st.push(a + b);
                    break;
                case -2:
                    st.push(a - b);
                    break;
                case -3:
                    st.push(a * b);
                    break;
                case -4:
                    st.push(a / b);
                    break;
            }
		}
	}
	result = st.pop();
	st.clear();
	return result;
}

int main()
{
	char input[DEFAULT_CAPACITY];
	int result;
	int n = 0;
	int nums[DEFAULT_CAPACITY];

	fgets(input, DEFAULT_CAPACITY - 1, stdin);
	makePolishString(input, nums, n);

	result = calculate(nums, n);
	printf("%d\n", result);

	return 0;
}