#pragma once

#include <IPiece.hpp>

class Bishop : public IPiece
{
public:
    Bishop(bool team, int startX, int startY);

    virtual ~Bishop() = default;
    virtual bool verify_position(int x, int y) override;
    virtual void move(int x, int y) override;


private:
 
};
