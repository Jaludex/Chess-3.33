#include <IPiece.hpp>

Position::Position(uint8_t _x, uint8_t _y) : x(_x), y(_y) {}

bool Position::operator==(const Position& right)
{
    return (x == right.x) && (y == right.y);
}


IPiece::IPiece() : IGameObject(sf::Texture(sf::Texture ({(unsigned int)(100),(unsigned int)(100)}))), current(0, 0)
{}

void IPiece::set_piece_type(PieceType type)
{
    this->type = type;
}

void IPiece::set_team(bool team)
{
    this->team = team;
}

bool IPiece::get_team() const
{
    return this->team;
}

PieceType IPiece::get_piece_type() const
{
    return this->type;
}

Position IPiece::get_position() const
{
    return current;
}

std::vector<Move> IPiece::get_valid_moves()
{
    return valid_moves;
}
