#include <IGameState.hpp>

sf::Vector2i IGameState::get_relative_mouse_position()
{
    return sf::Mouse::getPosition(*window);
}

