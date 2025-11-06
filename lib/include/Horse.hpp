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
    virtual bool verify_position(int x, int y) override;
    virtual void move(int x, int y) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;


private:
 
};
