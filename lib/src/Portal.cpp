#include"Portal.hpp"


sf::Color Portal::white = sf::Color(230,230,150,255);
sf::Color Portal::black = sf::Color(150,150,230,255);

sf::Color Portal::get_color(bool _team)
{
return (_team)? Portal::white : Portal::black;
}

Portal::Portal(bool team)
{
    set_team(team);
    set_piece_type(PieceType::Portal);
}

void Portal::update(float dt)
{
    
}

void Portal::render(sf::RenderWindow& window)
{
    auto triangle = sf::CircleShape(45,(size_t)3);
    triangle.setOrigin({45.f,45.f});
    triangle.setScale({1.f,2.f});
    auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
    triangle.setPosition(this->sprite.getPosition() + offset);
    triangle.setFillColor(get_color(team));
    window.draw(triangle);
}

std::vector<BoardObjectPtr> Portal::set_valid_moves(const std::list<BoardObjectPtr>& pieces, Position current) 
{
    valid_moves.erase(valid_moves.begin(), valid_moves.end());
    for (auto object : pieces)
    {
        if (object->piece->get_team() == team && object->piece->get_piece_type() != PieceType::Portal)
        {
            valid_moves.push_back(object);
        }
    }
    
    return valid_moves;    
}

bool Portal::hurt(PiecePtr attacker)
{
    return true;
}

int Portal::get_material_value() const
{
    return 3;
}

int Portal::get_max_mobility() const
{
    return 0;
}
