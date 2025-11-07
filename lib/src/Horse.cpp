#include"Horse.hpp"

const std::vector<Position> Horse::directions = {Position(0, -2), Position(1, -1), Position(2, 0), Position(1, 1), 
                                                    Position(0, 2), Position(-1, 1), Position(-2, 0), Position(-1, -1)};

Horse::Horse(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Horse);
    
    current.x = startX;
    current.y = startY;
}

bool Horse::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Horse::move(Position pos)
{
   if (is_valid(pos))
    {
        current.x = pos.x;
        current.y = pos.y;
    }


}

void Horse::update(float dt)
{
    
}

void Horse::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(sf::Color::Cyan);
    window.draw(triangle);
}

std::vector<Move> Horse::set_valid_moves(const std::vector<PiecePtr>& pieces) 
{
    valid_moves.clear();
    const uint8_t lenght = Board::side_lenght;

    for (auto direction : directions)
    {
        int new_x = current.x + direction.x;
        int new_y = current.y + direction.y;

        if (new_x < 0 || new_x >= Board::side_lenght || new_y < 0 || new_y >= Board::side_lenght)
        {
            continue;
        }

        Position target_position((int8_t)new_x, (int8_t)new_y);
        PiecePtr target_piece = nullptr;
        for (auto piece : pieces)
        {
            if (piece->get_position() == target_position)
            {
                target_piece = piece;
                break;
            }
        }
        
        if (target_piece)
        {
            if(target_piece->get_team() != team)
            {
                valid_moves.push_back(Move(target_position, true, target_piece));
            }
        }
        else
        {
            valid_moves.push_back(Move(target_position, true, target_piece));
        }
        
    }
    return valid_moves;    
}

bool Horse::hurt(PiecePtr attacker)
{
    return true;
}
