#include "PriorityQueue.h"

template<typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue() {}

template<typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& value) {
    auto it = data.begin();
    while (it != data.end() && comp(*it, value)) {
        ++it;
    }
    data.insert(it, value);
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
