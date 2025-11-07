#include "Crook.hpp"

const std::vector<Position> Crook::directions = {Position(0, 2), Position(1, -1), Position(-1, -1)};

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
    //Validar si movimiento es valido

    //Si si lo es hace el movimiento
    current.x = pos.x;
    current.y = pos.y;
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
    triangle.setFillColor(sf::Color::Blue);
    window.draw(triangle);
}

std::vector<Move> Crook::set_valid_moves(const std::vector<PiecePtr>& pieces)
{
    valid_moves.erase(valid_moves.begin(), valid_moves.end());

    Position advance = current + directions[0];
    Position right_diagonal = current + directions[1];
    Position left_diagonal = current + directions[2];

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
    
    if (!front_piece)
    {
        valid_moves.push_back(Move(advance, true, front_piece));
    }

    if (attack_left)
    {
        valid_moves.push_back(Move(left_diagonal, true, attack_left));
    }

    if (attack_right)
    {
        valid_moves.push_back(Move(right_diagonal, true, attack_right));
    }
    return valid_moves;    
}

bool Crook::hurt(PiecePtr attacker)
{
    return true;
}
