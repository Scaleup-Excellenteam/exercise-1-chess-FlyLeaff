#pragma once
#ifndef MOVECOMPARATOR_H
#define MOVECOMPARATOR_H

#include <utility>

struct MoveComparator {
    bool operator()(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) const {
        return a.first > b.first; // Higher score means higher priority
    }
};

#endif // MOVECOMPARATOR_H
