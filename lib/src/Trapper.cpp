#include "Trapper.hpp"

const std::vector<Position> Trapper::directions = {Position(0, 2), Position(0, -2), Position(-2, 0), Position(2, 0)};

Bomb::white = sf::Color(120,120,20,255);
Bomb::black = sf::Color(20,20,0,255);

Bomb::get_color()
{
return (team)? Bomb::white : Bomb::black;
}

Bomb::Bomb(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Bomb);
    
    current.x = startX;
    current.y = startY;
}
bool Bomb::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Bomb::move(Position pos)
{
    //empty
}

void Bomb::update(float dt)
{
    
}

void Bomb::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(get_color());
    window.draw(triangle);
}

std::vector<Move> Bomb::set_valid_moves(const std::vector<PiecePtr>& pieces) 
{
   valid_moves.erase(valid_moves.begin(),valid_moves.end());
   return valid_moves;    
}

bool Bomb::hurt(PiecePtr attacker)
{
    attacker->hurt(std::make_shared<Bomb>(team,current.x,current.y));
    return true;
}


Trapper::white = sf::Color(170,170,70,255);
Trapper::black = sf::Color(70,70,0,255);

Trapper::get_color()
{
return (team)? Trapper::white : Trapper::black;
}

Trapper::Trapper(bool team, int startX, int startY)
{
    set_team(team);
    set_piece_type(PieceType::Trapper);
    
    current.x = startX;
    current.y = startY;
}

bool Trapper::verify_position(Position pos)
{
    int dx = std::abs(pos.x - current.x);
    int dy = std::abs(pos.y - current.y);

    return (dx == dy) && (dx > 0);
}

void Trapper::move(Position pos)
{
    if(is_valid(pos))
    {
        current.x = pos.x;
        current.y = pos.y;
    }
}

void Trapper::update(float dt)
{
    
}

void Trapper::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(get_color());
    window.draw(triangle);
}

std::vector<Move> Trapper::set_valid_moves(const std::vector<PiecePtr>& pieces)
{
    valid_moves.erase(valid_moves.begin(), valid_moves.end());
    const uint8_t lenght = Board::side_lenght;

    for (auto direction : Trapper::directions)
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

bool Trapper::hurt(PiecePtr attacker)
{
    return true;
}
