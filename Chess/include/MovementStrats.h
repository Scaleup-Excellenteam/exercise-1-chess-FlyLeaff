
#ifndef MOVEMENT_STRATS_H
#define MOVEMENT_STRATS_H

#include <vector>
#include <utility>

class MovementStrategy
{
public:
    virtual std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const = 0;
    virtual ~MovementStrategy() = default;
};

class HorizontalVerticalMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
};

class DiagonalMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
};

class KingMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
};

class KnightMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
};

class PawnMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
};

#endif // MOVEMENT_STRATS_H
