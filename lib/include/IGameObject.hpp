#pragma once
#include <SFML/Graphics.hpp>

class IGameObject
{
protected:
    sf::Sprite sprite;

public:
    IGameObject(sf::Texture texture);
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};


