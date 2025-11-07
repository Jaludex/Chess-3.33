#pragma once

#include <cstdint>
#include <IGameObject.hpp>

struct Position
{
    int8_t x, y;

    Position(int8_t _x, int8_t _y);
    bool operator==(const Position& right);
    Position operator+(Position it);
};

class IPiece;
using PiecePtr = std::shared_ptr<IPiece>;

struct Move
{
    Position relative_positiion;
    bool moves_piece;   //Esto para poder diferenciar los movimientos que atacan pero no mueven directamente la pieza, como las flechas del arquero
    PiecePtr occupant;

    Move(Position _pos, bool _m, PiecePtr _o) : relative_positiion(_pos), moves_piece(_m), occupant(_o) {}
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
    Portal,
    Bomb
};

class IPiece : public IGameObject
{
public:
    bool get_team() const;
    Position get_position() const;
    std::vector<Move> get_valid_moves();
    PieceType get_piece_type() const;
    void set_team(bool team);
    void set_piece_type(PieceType type);
    virtual bool verify_position(Position pos) = 0;
    virtual std::vector<Move> set_valid_moves(const std::vector<PiecePtr>& pieces) = 0;
    virtual void move(Position pos) = 0;
    //Retorna si mata o no a la pieza, pues hay piezas con mas vida
    virtual bool hurt(PiecePtr attacker) = 0;
    bool is_valid(Position pos);
    IPiece();
    virtual ~IPiece() = default;
    void swap(Position pos);

protected:
    Position current;
    bool team;
    PieceType type;
    std::vector<Move> valid_moves;
};
