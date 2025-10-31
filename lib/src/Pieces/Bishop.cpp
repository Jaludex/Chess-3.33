#include "Bishop.hpp"

const float TILE_SIZE = 64.f; 

Bishop::Bishop(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Bishop);
    
    current.x = startX;
    current.y = startY;
}

bool Bishop::verify_position(int x, int y)
{
    int dx = std::abs(x - current.x);
    int dy = std::abs(y - current.y);

    return (dx == dy) && (dx > 0);
}

void Bishop::move(int x, int y)
{
    current.x = x;
    current.y = y;

}

void Bishop::update(float dt)
{
    
}

void Bishop::render(sf::RenderWindow& window)
{
    //board.render(window)
}
