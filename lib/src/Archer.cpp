#include "Archer.hpp"

const std::vector<Position> Archer::directions = {Position(0, -1), Position(1, -2), Position(2, -1), Position(-1, -2), Position(-2, -1)};

sf::Color Archer::white = sf::Color(200,200,250,255);
sf::Color Archer::black = sf::Color(100,100,150,255);

sf::Color Archer::get_color()
{
return (team)? Archer::white : Archer::black;
}

Archer::Archer(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Archer);
    
    current.x = startX;
    current.y = startY;
}

bool Archer::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Archer::move(Position pos)
{
    if (is_valid(pos))
    {
        current.x = pos.x;
        current.y = pos.y;
    }
}

void Archer::update(float dt)
{
    
}

void Archer::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)5);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(get_color());
    window.draw(triangle);
}

std::vector<Move> Archer::set_valid_moves(const std::vector<PiecePtr>& pieces)
{
    valid_moves.clear();

    std::vector<Position> relative_moves;
    int8_t mirror = (team) ? 1 : -1;

    for (size_t i = 0; i < directions.size(); i++)
    {
        relative_moves.push_back(Position(current.x + directions.at(i).x, current.y + (directions.at(i).y * mirror)));
    }

    bool free_front = true;
    for (auto piece : pieces)
    {
        if (relative_moves.at(0) == piece->get_position() &&
            relative_moves.at(0).x < 0 && relative_moves.at(0).x > 5 && 
            relative_moves.at(0).y < 0 && relative_moves.at(0).y > 5) free_front = false;

        for (size_t i = 1; i < 5; i++)
        {
            if (relative_moves.at(i) == piece->get_position() && this->team != piece->get_team()) valid_moves.push_back(Move(relative_moves.at(i), true, piece));
        }
    }

    if (free_front) valid_moves.push_back(Move(relative_moves.at(0), true, nullptr));
    
    return valid_moves;
}

bool Archer::hurt(PiecePtr attacker)
{
    return true;
}
