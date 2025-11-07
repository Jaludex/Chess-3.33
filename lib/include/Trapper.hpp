#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <IPiece.hpp>
#include <Board.hpp>

class Trapper : public IPiece
{
public:
    Trapper(bool team, int startX, int startY);

    virtual ~Trapper() = default;
    virtual bool verify_position(Position pos) override;
    virtual void move(Position pos) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual std::vector<Move> set_valid_moves(const std::vector<PiecePtr>& pieces) override;
    virtual bool hurt(PiecePtr attacker) override;

private:
    const static std::vector<Position> directions;
    std::shared_ptr<Board> board;
};

class Bomb : public IPiece
{
public:
    Bomb(bool team, int startX, int startY);

    virtual ~Bomb() = default;
    virtual bool verify_position(Position pos) override;
    virtual void move(Position pos) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual std::vector<Move> set_valid_moves(const std::vector<PiecePtr>& pieces) override;
    virtual bool hurt(PiecePtr attacker) override;
};