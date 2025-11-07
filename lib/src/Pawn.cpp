#include"Pawn.hpp"

Pawn::Pawn(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Pawn);
    
    current.x = startX;
    current.y = startY;
}

bool Pawn::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Pawn::move(Position pos)
{
    if (is_valid(pos))
    {
        current.x = pos.x;
        current.y = pos.y;
    }


}

void Pawn::update(float dt)
{
    
}

void Pawn::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)12);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Magenta);
    window.draw(triangle);
}

std::vector<Move> Pawn::set_valid_moves(const std::vector<PiecePtr>& pieces) 
{
    valid_moves.erase(valid_moves.begin(), valid_moves.end());
    int8_t mirror = (team) ? -1 : 1;

    Position advance(current.x, current.y + mirror);
    Position left_diagonal(current.x + mirror, current.y + mirror);
    Position right_diagonal(current.x - mirror, current.y + mirror);
    PiecePtr front_piece = nullptr;
    PiecePtr attack_left = nullptr;
    PiecePtr attack_right = nullptr;
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
    
    if (!front_piece && advance.x <= 5, advance.y <= 5)
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

bool Pawn::hurt(PiecePtr attacker)
{
    return true;
}
