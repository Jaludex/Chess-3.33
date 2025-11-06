#include"Horse.hpp"

Horse::Horse(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Horse);
    
    current.x = startX;
    current.y = startY;
}

bool Horse::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Horse::move(Position pos)
{
    current.x = pos.x;
    current.y = pos.y;

}

void Horse::update(float dt)
{
    
}

void Horse::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Magenta);
    window.draw(triangle);
}

std::vector<Move> Horse::get_valid_moves(std::vector<PiecePtr> pieces) 
{

}