#pragma once

#include "IPiece.hpp"
#include <SFML/Graphics.hpp>

class Bishop : public IPiece
{
public:
    Bishop(bool team, int startX, int startY, const sf::Texture& texture);

    virtual ~Bishop() = default;
    virtual bool verify_position(int x, int y) override;
    virtual void move(int x, int y) override;
    virtual void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_sprite;
};
