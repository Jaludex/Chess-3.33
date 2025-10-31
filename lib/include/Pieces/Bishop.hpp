#pragma once

#include <IPiece.hpp>

class Bishop : public IPiece
{
public:
    Bishop(bool team, int startX, int startY);

    virtual ~Bishop() = default;
    virtual bool verify_position(Position position) override;
    virtual void move(Position position) override;
    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;


private:
 
};
