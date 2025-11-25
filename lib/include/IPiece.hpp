#pragma once

#include <SpriteManager.hpp>
#include <cstdint>
#include <IGameObject.hpp>
#include <memory>
#include <list>

struct Position
{
    int8_t x, y;

    Position(int8_t _x, int8_t _y);
    bool operator==(const Position& right);
    Position operator+(Position it);
};

class IPiece;
using PiecePtr = std::shared_ptr<IPiece>;

struct InBoardObject
{
    Position pos;
    PiecePtr piece;
    bool leader;

    InBoardObject(Position _pos, PiecePtr _piece) : pos(_pos), piece(_piece), leader(false) {}
    InBoardObject(Position _pos) : pos(_pos), piece(nullptr), leader(false) {}
    InBoardObject() : pos(Position(0,0)), piece(nullptr), leader(false) {}
};

using BoardObjectPtr = std::shared_ptr<InBoardObject>;

class IPiece : public virtual IGameObject
{
public:
    bool get_team() const;
    std::vector<BoardObjectPtr> get_valid_moves();
    PieceType get_piece_type() const;
    void set_team(bool team);
    void set_piece_type(PieceType type);
    virtual std::vector<BoardObjectPtr> set_valid_moves(const std::list<BoardObjectPtr>& elements, Position current) = 0;
    //Retorna si mata o no a la pieza, pues hay piezas con mas vida
    virtual bool hurt(PiecePtr attacker) = 0;
    bool is_valid(Position pos);
    virtual int get_material_value() const = 0;
    virtual int get_max_mobility() const = 0;
    virtual PiecePtr clone_piece() const = 0;
    IPiece();
    virtual ~IPiece() = default;

protected:
    bool team;
    PieceType type;
    std::vector<BoardObjectPtr> valid_moves;
};
