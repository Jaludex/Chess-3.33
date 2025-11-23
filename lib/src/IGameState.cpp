#include "IGameState.hpp"

sf::Vector2i IGameState::get_relative_mouse_position()
{
    return static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}

