#include "Bishop.hpp"

Bishop::Bishop(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Bishop);
    
    current.x = startX;
    current.y = startY;
}

bool Bishop::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Bishop::move(Position pos)
{
    //Validar si movimiento es valido

    //Si si lo es hace el movimiento
    current.x = pos.x;
    current.y = pos.y;
}

void Bishop::update(float dt)
{
    
}

void Bishop::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Blue);
    window.draw(triangle);
}

std::vector<Move> Bishop::set_valid_moves(const std::vector<PiecePtr>& pieces)
{
    valid_moves.erase(valid_moves.begin(), valid_moves.end());
    const uint8_t lenght = Board::side_lenght;
    const std::vector<Position> directions = {Position(1, -1), Position(1, 1), Position(-1, 1), Position(-1, -1)};

    for (auto direction : directions)
    {
        int delta_x = direction.x;
        int delta_y = direction.y;
        for (size_t k = 1; k <= 2; k++)
        {
            uint8_t tile_x = current.x + (k * delta_x);
            uint8_t tile_y = current.y + (k * delta_y);

            if (tile_x >= lenght || tile_y >= lenght) break;

            Position target_move(tile_x, tile_y);

            bool occupied = false;
            PiecePtr piece_at_cell = nullptr;
            for(auto const& piece : pieces)
            {
                if (piece->get_position() == target_move)
                {
                    piece_at_cell = piece;
                    occupied = true;
                    break;
                }
            }

            if (occupied)
            {
                if (piece_at_cell->get_team() != this->get_team())
                {
                    valid_moves.push_back(Move(target_move, true, piece_at_cell));
                }
                break;
            }
            else
            {
                valid_moves.push_back(Move(target_move, true, piece_at_cell));
            }
        }
        
    }
    return valid_moves;    
}

bool Bishop::hurt(PiecePtr attacker)
{
    return true;
}
