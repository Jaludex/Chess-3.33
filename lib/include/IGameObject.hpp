#pragma once
#include <SFML/Graphics.hpp>

class IGameObject
{
protected:
    sf::Sprite sprite;

public:
    IGameObject(sf::Texture texture);
    IGameObject();
    sf::Sprite get_sprite() const;
    void set_sprite_position(const sf::Vector2f& position);
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};


