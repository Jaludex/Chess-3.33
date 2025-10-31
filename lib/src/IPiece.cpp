#include <IPiece.hpp>

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
