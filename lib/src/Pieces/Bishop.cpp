#include "Bishop.hpp"

const float TILE_SIZE = 64.f; 

Bishop::Bishop(bool team, int startX, int startY, const sf::Texture& texture)
{
    set_team(team);
    set_piece_type(PieceType::Bishop);
    
    current.x = startX;
    current.y = startY;

    m_sprite.setTexture(texture);
    
    if (team) 
    {
        m_sprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    } 
    else 
    {
        m_sprite.setTextureRect(sf::IntRect(64, 0, TILE_SIZE, TILE_SIZE));
    }
    m_sprite.setPosition(current.x * TILE_SIZE, current.y * TILE_SIZE);
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

    m_sprite.setPosition(current.x * TILE_SIZE, current.y * TILE_SIZE);
}

