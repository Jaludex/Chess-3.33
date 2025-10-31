#include "Bishop.hpp"

Bishop::Bishop(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Bishop);
    
    current.x = startX;
    current.y = startY;
}

bool Bishop::verify_position(int x, int y)
{
    int dx = std::abs(x - current.x);
    int dy = std::abs(y - current.y);

    return (dx == dy) && (dx > 0);
}

void Bishop::move(int x, int y)
{
    current.x = x;
    current.y = y;

}

void Bishop::update(float dt)
{
    
}

void Bishop::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    //triangle.setRotation(sf::degrees());
    triangle.setScale({1.f,2.f});
    triangle.setPosition(this->sprite.getPosition());
    triangle.setFillColor(sf::Color::Blue);
    window.draw(triangle);
}
