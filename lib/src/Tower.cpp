#include"Tower.hpp"

const std::vector<Position> Tower::directions = {Position(1, 0), Position(-1, 0), Position(0, 1), Position(0, -1)};
Tower::Tower(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Tower);
    
    current.x = startX;
    current.y = startY;
}

bool Tower::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Tower::move(Position pos)
{
    current.x = pos.x;
    current.y = pos.y;

}

void Tower::update(float dt)
{
    
}

void Tower::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Green);
    window.draw(triangle);
}

std::vector<Move> Tower::get_valid_moves(std::vector<PiecePtr> pieces) 
{
    const uint8_t lenght = Board::side_lenght;

    for (size_t i = 0; i < 4; i++)
    {
        int delta_x = directions[i].x;
        int delta_y = directions[i].y;
        for (size_t k = 0; k < lenght && k <= 3; k++)
        {
            int translation_x = current.x + (k * delta_x);
            int translation_y = current.y + (k * delta_y);

            if (translation_x >= lenght || translation_y >= lenght)
            {
                break;
            }
            
            Position target_move(translation_x,translation_y);
            PiecePtr piece_in_cell = nullptr;

            for(auto piece : pieces)
            {
                if (piece->get_position().x == target_move.x && piece->get_position().y == target_move.y)
                {
                    piece_in_cell = piece;
                    break;
                }
            }

            if (piece_in_cell)
            {
                if (piece_in_cell->get_team() != this->get_team())
                {
                    valid_moves.push_back(Move(target_move, false, false));
                }
                break;
            }
            else
            {
                valid_moves.push_back(Move(target_move, false, false));
            }
        }
        
    }
    return valid_moves;   
}