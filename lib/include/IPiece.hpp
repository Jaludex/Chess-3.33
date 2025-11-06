#pragma once

#include <cstdint>
#include <IGameObject.hpp>

struct Position
{
    uint8_t x, y;

    Position(uint8_t _x, uint8_t _y) : x(_x), y(_y) {}
};

struct Move
{
    Position relative_positiion;
    bool moves_piece;   //Esto para poder diferenciar los movimientos que atacan pero no mueven directamente la pieza, como las flechas del arquero
    bool jumps;         //Para los movimientos que pasen por encima de otras piezas, como los del caballo

    Move(Position _pos, bool _m, bool _j) : relative_positiion(_pos), moves_piece(_m), jumps(_j) {}
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
    virtual bool verify_position(Position pos) = 0;
    virtual std::vector<Position> get_valid_moves(Board& board) = 0;
    virtual void move(Position pos) = 0;

    IPiece();
    virtual ~IPiece() = default;

protected:
    Position current;
    bool team;
    PieceType type;
};

using PiecePtr = std::shared_ptr<IPiece>;
