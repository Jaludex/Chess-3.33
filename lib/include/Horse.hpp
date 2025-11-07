#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <IPiece.hpp>
#include <Board.hpp>

class Horse : public IPiece
{
    public:
    Horse(bool team, int startX, int startY);

    virtual ~Horse() = default;
    virtual bool verify_position(Position pos) override;
    virtual void move(Position pos) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual std::vector<Move> set_valid_moves(const std::vector<PiecePtr>& pieces) override;
    virtual bool hurt(PiecePtr attacker) override;

    static sf::Color get_color(bool);
    static sf::Color white;
    static sf::Color black;

private:
    const static std::vector<Position> directions;
};
