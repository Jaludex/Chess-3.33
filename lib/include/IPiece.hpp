#pragma once

#include <cstdint>
#include <IGameObject.hpp>

struct Position
{
    uint8_t x, y;
};

enum class PieceType
{
    Pawn ,
    Horse,
    Bishop,
    Tower,
    Queen,
    King,
    Trapper,
    Crook,
    Archer,
    Portal
};

class IPiece : public IGameObject
{
public:
    bool get_team() const;
    Position get_position() const;
    PieceType get_piece_type() const;
    void set_team(bool team);
    void set_piece_type(PieceType type);
    virtual ~IPiece() = default;
    virtual bool verify_position(int x, int y) = 0;
    virtual void move(int x, int y) = 0;

protected:
    Position current;
    bool team;
    PieceType type;
};

using PiecePtr = std::shared_ptr<IPiece>;
