
#ifndef MOVEMENT_STRATS_H
#define MOVEMENT_STRATS_H

#include <vector>
#include <utility>
#include <memory>

class MovementStrategy
{
public:
    virtual std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const = 0;
    virtual ~MovementStrategy() = default;
    virtual std::unique_ptr<MovementStrategy> clone() const = 0;
};

class HorizontalVerticalMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
    virtual std::unique_ptr<MovementStrategy> clone() const override;
};

class DiagonalMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
    virtual std::unique_ptr<MovementStrategy> clone() const override;
};

class KingMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
    virtual std::unique_ptr<MovementStrategy> clone() const override;
};

class KnightMovement : public MovementStrategy
{
public:
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;
    virtual std::unique_ptr<MovementStrategy> clone() const override;
};

class PawnMovement : public MovementStrategy
{
public:
    explicit PawnMovement(bool isWhite) : isWhite(isWhite) {}
    std::vector<std::pair<int, int>> getValidMoves(int srcRow, int srcCol) const override;

    virtual std::unique_ptr<MovementStrategy> clone() const override;
private:
    bool isWhite;
};

#endif // MOVEMENT_STRATS_H
