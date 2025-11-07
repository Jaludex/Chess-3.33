#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <IPiece.hpp>
#include <Board.hpp>

class Portal : public IPiece
{
    public:
    Portal(bool team, int startX, int startY);

    virtual ~Portal() = default;
    virtual bool verify_position(Position pos) override;
    virtual void move(Position pos) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual std::vector<Move> set_valid_moves(const std::vector<PiecePtr>& pieces) override;
    virtual bool hurt(PiecePtr attacker) override;

    sf::Color get_color(bool);
    static sf::Color white;
    static sf::Color black;

private:
};
