#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <IPiece.hpp>
#include <Board.hpp>

class Tower : public IPiece
{
    public:
    Tower(bool team, int startX, int startY);

    virtual ~Tower() = default;
    virtual bool verify_position(int x, int y) override;
    virtual void move(int x, int y) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;


private:
 
};
