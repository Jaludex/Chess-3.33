#include "IGameState.hpp"

sf::Vector2i IGameState::get_relative_mouse_position()
{
    return sf::Mouse::getPosition(*window);
}

bool IGameState::is_mouse_over(const sf::Text& text, const sf::Vector2i& mouse_pos)
{
    sf::FloatRect bounds = text.getGlobalBounds();
    return bounds.contains({(float)mouse_pos.x, (float)mouse_pos.y});
}
bool IGameState::is_mouse_over(const sf::Sprite& sprite, const sf::Vector2i& mousePos)
{
    sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return sprite.getGlobalBounds().contains(mouseF);
}
