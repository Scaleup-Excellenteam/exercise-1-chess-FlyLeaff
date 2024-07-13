#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <list>
#include <functional>
#include <stdexcept>

template<typename T, typename Comparator = std::less<T>>
class PriorityQueue {
public:
    PriorityQueue();

    void push(const T& value);
    T poll();

    bool isEmpty() const;

private:
    std::list<T> data;
    Comparator comp;

};

template<typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue() {}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& value) {
    auto it = data.begin();
    while (it != data.end() && comp(*it, value)) {
        ++it;
    }
    data.insert(it, value);
    if(data.size()>5)
        data.pop_back();
}

template<typename T, typename Comparator>
T PriorityQueue<T, Comparator>::poll() {
    if (isEmpty()) {
        throw std::out_of_range("PriorityQueue is empty");
    }
    T highestPriority = data.front();
    data.pop_front();
    return highestPriority;
}

template<typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::isEmpty() const {
    return data.empty();
}

#endif // PRIORITYQUEUE_H
