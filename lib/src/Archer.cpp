#include "Archer.hpp"

const std::vector<Position> Archer::directions = {Position(0, -1), Position(1, -2), Position(2, -1), Position(-1, -2), Position(-2, -1)};

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
    triangle.setFillColor(sf::Color::Blue);
    window.draw(triangle);
}

std::vector<Move> Archer::set_valid_moves(const std::vector<PiecePtr>& pieces)
{
    valid_moves.clear();

    Position advance = current + directions[0];
    Position right_diagonal_1 = current + directions[1];
    Position right_diagonal_2 = current + directions[2];
    Position left_diagonal_1 = current + directions[3];
    Position left_diagonal_2 = current + directions[4];

    PiecePtr front_piece = nullptr;
    PiecePtr attack_right_1 = nullptr;
    PiecePtr attack_right_2 = nullptr;
    PiecePtr attack_left_1 = nullptr;
    PiecePtr attack_left_2 = nullptr;

    for (auto piece : pieces)
    {
        if(piece->get_position() == advance)
        {
            front_piece = piece;
        }
        else if (piece->get_position() == left_diagonal_1 && piece->get_team() != this->get_team())
        {
            attack_left_1 = piece;
        }
        else if (piece->get_position() == left_diagonal_2 && piece->get_team() != this->get_team())
        {
            attack_left_2 = piece;
        }
        else if (piece->get_position() == right_diagonal_1 && piece->get_team() != this->get_team())
        {
            attack_right_1 = piece;
        }
        else if (piece->get_position() == right_diagonal_2 && piece->get_team() != this->get_team())
        {
            attack_right_2 = piece;
        }
    }
    
    if (!front_piece && advance.x <= 5 && advance.y <= 5 && advance.x >= 0 && advance.y >= 0)
    {
        valid_moves.push_back(Move(advance, true, front_piece));
    }

    if (attack_left_1)
    {
        valid_moves.push_back(Move(left_diagonal_1, false, attack_left_1));
    }

    if (attack_left_2)
    {
        valid_moves.push_back(Move(left_diagonal_2, false, attack_left_2));
    }

    if (attack_right_1)
    {
        valid_moves.push_back(Move(right_diagonal_1, false, attack_right_1));
    }

    if (attack_right_2)
    {
        valid_moves.push_back(Move(right_diagonal_2, false, attack_right_2));
    }
    return valid_moves;    
}

bool Archer::hurt(PiecePtr attacker)
{
    return true;
}
