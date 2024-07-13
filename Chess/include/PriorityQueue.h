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


#endif // PRIORITYQUEUE_H
