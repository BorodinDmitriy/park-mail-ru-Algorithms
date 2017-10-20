#include <assert.h>
#include <iostream>

#define BUFFER_SIZE 16
class myDeque {
public:
    myDeque() : head(-1), buffer(NULL), tail(-1), count(0), size(BUFFER_SIZE) {
        buffer = new int[size];
    }

    ~myDeque() {
        if (buffer != NULL)
            delete[] buffer;
    }

    void push_back(int key);

    void push_front(int key);

    void reallocate();

    int pop_back();

    int pop_front();

    bool isEmpty() const { return count == 0; }

private:
    int count;
    int size;

    int tail;
    int head;

    int *buffer;

};

void myDeque::push_back(int key) {
    if (isEmpty()) {
        head = tail = 0;
        buffer[head] = key;
        count = 1;
        return;
    }

    assert(count != 0);
    // Добавляем элемент в конец списка.
    if (size - count < 2) {
        int *oldBuffer = buffer;
        int oldsize = size;

        size *= 2;
        buffer = new int[size];

        //Первым элементом устанавливаем ключ так как мы вызываем push_back
        buffer[0] = key;
        count++;
        for (int i = head, j = 1; j < count; i++, j++)
            if (i < oldsize)
                buffer[j] = oldBuffer[i];
            else {
                i = 0;
                buffer[j] = oldBuffer[i];
            }

        head = 0;
        tail = count - 1;
        delete[] oldBuffer;
        return;
    }

    if (head != 0) {
        buffer[--head] = key;
        count++;
    } else {
        head = size - 1;
        buffer[head] = key;
        count++;
    }
}

void myDeque::push_front(int key) {
    if (isEmpty()) {
        head = tail = 0;
        buffer[tail] = key;
        count = 1;
        return;
    }

    assert(count != 0);
    // Добавляем элемент в конец списка.
    if (size - count < 2) {
        int *oldBuffer = buffer;
        int oldsize = size;

        size *= 2;
        buffer = new int[size];

        for (int i = head, j = 0; j < count; i++, j++)
            if (i < oldsize)
                buffer[j] = oldBuffer[i];
            else {
                i = 0;
                buffer[j] = oldBuffer[i];
            }

        head = 0;
        tail = count - 1;
        delete[] oldBuffer;
    }

    if (tail < size - 1)
        tail++;
    else tail = 0;

    buffer[tail] = key;
    count++;
}

void myDeque::reallocate() {
    int oldsize = size;
    size = count % BUFFER_SIZE + count;
    int *oldBuffer = buffer;

    buffer = new int[size];

    for (int i = head, j = 0; j < count; i++, j++)
        if (i < oldsize)
            buffer[j] = oldBuffer[i];
        else {
            i = 0;
            buffer[j] = oldBuffer[i];
        }

    head = 0;
    tail = count - 1;
    delete[] oldBuffer;
}

int myDeque::pop_back() {
    assert(!isEmpty());

    count--;
    int result = buffer[head];

    if (head < size - 1)
        head++;
    else head = 0;

    return result;
}

int myDeque::pop_front() {
    assert(!isEmpty());

    count--;
    int result = buffer[tail];

    if (tail > 0)
        tail--;
    else tail = size - 1;

    return result;
}

int main() {
    int requestValue = 0;
    int requestsCount = 0;
    std::cin >> requestsCount;

    myDeque deque;
    for (int i = 0; i < requestsCount; ++i) {
        int requestType = 0;
        std::cin >> requestType >> requestValue;
        switch (requestType) {
            case 1:
                deque.push_front(requestValue);
                break;
            case 2:
                if (deque.isEmpty()) {
                    if (requestValue != -1) {
                        std::cout << "NO";
                        return 0;
                    }
                } else {
                    int tmp = deque.pop_front();
                    if (tmp != requestValue) {
                        std::cout << "NO";
                        return 0;
                    }
                }
                break;
            case 3:
                deque.push_back(requestValue);
                break;
            case 4:
                if (deque.isEmpty()) {
                    if (requestValue != -1) {
                        std::cout << "NO";
                        return 0;
                    }
                } else {
                    if (deque.pop_back() != requestValue) {
                        std::cout << "NO";
                        return 0;
                    }
                }
                break;
            default:
                assert(false);
        }
    }
    std::cout << "YES";
    return 0;
}