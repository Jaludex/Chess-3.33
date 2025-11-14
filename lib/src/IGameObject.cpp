#include <IGameObject.hpp>


IGameObject::IGameObject(sf::Texture texture) : sprite(texture)
{

}

sf::Sprite IGameObject::get_sprite() const
{
    return sprite;
}

void IGameObject::set_sprite_position(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}

bool IGameObject::is_touching_mouse(const sf::Vector2i& mouse_position)
{
    return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_position));
}
