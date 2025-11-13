#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <IPiece.hpp>
#include <Board.hpp>

class Archer : public IPiece
{
public:
    Archer(bool team);

    virtual ~Archer() = default;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual std::vector<BoardObjectPtr> set_valid_moves(const std::list<BoardObjectPtr>& elements, Position current) override;
    virtual bool hurt(PiecePtr attacker) override;

    static sf::Color get_color(bool);
    static sf::Color white;
    static sf::Color black;

private:
    const static std::vector<Position> directions;
};
