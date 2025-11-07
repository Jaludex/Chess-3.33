#include "Crook.hpp"

const std::vector<Position> Crook::directions = {Position(0, 2), Position(1, -1), Position(-1, -1)};

sf::Color Crook::white = sf::Color(150,200,230,225);
sf::Color Crook::black = sf::Color(50,100,130,225);

sf::Color Crook::get_color(bool _team)
{
return (_team)? Crook::white : Crook::black;
}

Crook::Crook(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Crook);
    
    current.x = startX;
    current.y = startY;
}

bool Crook::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Crook::move(Position pos)
{
   if (is_valid(pos))
    {
        current.x = pos.x;
        current.y = pos.y;
    }
}

void Crook::update(float dt)
{
    
}

void Crook::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(get_color(team));
    window.draw(triangle);
}

std::vector<Move> Crook::set_valid_moves(const std::vector<PiecePtr>& pieces)
{
    valid_moves.clear();

    int8_t mirror = (team) ? 1 : -1;

    Position advance(current.x + directions.at(0).x, current.y + (directions.at(0).y * mirror));
    Position right_diagonal(current.x + directions.at(1).x, current.y + (directions.at(1).y * mirror));
    Position left_diagonal(current.x + directions.at(2).x, current.y + (directions.at(2).y * mirror));

    PiecePtr front_piece = nullptr;
    PiecePtr attack_right = nullptr;
    PiecePtr attack_left = nullptr;

    for (auto piece : pieces)
    {
        if(piece->get_position() == advance)
        {
            front_piece = piece;
        }
        else if (piece->get_position() == left_diagonal && piece->get_team() != this->get_team())
        {
            attack_left = piece;
        }
        else if (piece->get_position() == right_diagonal && piece->get_team() != this->get_team())
        {
            attack_right = piece;
        }
    }
    
    if (!front_piece && advance.x <= 5 && advance.y <= 5 && advance.x >= 0 && advance.y >= 0)
    {
        valid_moves.push_back(Move(advance, true, front_piece));
    }

    if (attack_left == nullptr || attack_left->get_team() != this->get_team())
    {
        if (left_diagonal.x <= 5 && left_diagonal.y <= 5 && left_diagonal.x >= 0 && left_diagonal.y >= 0)
        {
            valid_moves.push_back(Move(left_diagonal, true, attack_left));
        }
    }

    if (attack_right == nullptr || attack_right->get_team() != this->get_team())
    {
        if (right_diagonal.x <= 5 && right_diagonal.y <= 5 && right_diagonal.x >= 0 && right_diagonal.y >= 0)
        {
            valid_moves.push_back(Move(right_diagonal, true, attack_right));
        }
    } 
    return valid_moves;    
}

bool Crook::hurt(PiecePtr attacker)
{
    return true;
}
