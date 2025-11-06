#include"Queen.hpp"

Queen::Queen(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Queen);
    
    current.x = startX;
    current.y = startY;
}

bool Queen::verify_position(int x, int y)
{
    int dx = std::abs(x - current.x);
    int dy = std::abs(y - current.y);

    return (dx == dy) && (dx > 0);
}

void Queen::move(int x, int y)
{
    current.x = x;
    current.y = y;

}

void Queen::update(float dt)
{
    
}

void Queen::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Yellow);
    window.draw(triangle);
}
