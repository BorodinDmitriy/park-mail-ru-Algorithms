/* Бородин Дмитрий, АПО-11 */
/*
7_2. Заявки на переговоры.
В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел — начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число — максимальное число заявок.
*/
#include <stdio.h>
#include <string>
#include <algorithm>

#define DEFAULT_CAPACITY 8


struct request 
{
    int start;
    int finish;
    
    bool operator < (const request &req)
    const
    {
        return ( this -> finish < req.finish);
    }
};


class Room 
{
private:
	long size;
	long capacity;
	request *requests;
public:
	Room();
	~Room();
	long getSize();
	void push(request req);
	void reallocate();
	void mySort();

	const request& operator[](long index)
	{
		return requests[index];
	}
};

Room::Room() : size(0), capacity(DEFAULT_CAPACITY)
{
	requests = new request[DEFAULT_CAPACITY * 2];
}

Room::~Room()
{
	delete [] requests;
}

long Room::getSize()
{
	return size;
}

void Room::push(request req)
{
	if (size == capacity)
	{
		reallocate();
	}
	requests[size++] = req;
}

void Room::reallocate()
{
	capacity = capacity * 2;
	request *tmp = new request[capacity];
	for (long i = 0; i < size; i++)
    {
        tmp[i] = requests[i];
    }
    delete [] requests;
    requests = tmp;
}

void Room::mySort()
{
	std::sort(requests, requests + size);
}

long solution(Room &times)
{
	long result = 1;
	long max = 0;
	times.mySort();

	long size = times.getSize();
	for (long i = 1; i < size; i++)
	{
		if (times[i].start >= times[max].finish)
		{
			result++;
			max = i;
		}
	}
	return result;
}

int main() 
{
	Room times;
	request val;
	while (scanf("%d %d",&(val.start),&(val.finish)) == 2)
	{
		times.push(val);
	}
	/*do {
		cin >> val.start >> val.finish;
		times.push(val);
	}
	while (!cin.eof());*/

	//cout << solution(times);
	printf("%d", solution(times));
	return 0;
}