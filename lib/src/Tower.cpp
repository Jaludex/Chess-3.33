#include"Tower.hpp"

Tower::Tower(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Tower);
    
    current.x = startX;
    current.y = startY;
}

bool Tower::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Tower::move(Position pos)
{
    current.x = pos.x;
    current.y = pos.y;

}

void Tower::update(float dt)
{
    
}

void Tower::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Green);
    window.draw(triangle);
}

std::vector<Move> Tower::get_valid_moves(std::vector<PiecePtr> pieces) 
{

}