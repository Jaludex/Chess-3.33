#include"PieceInstantiator.hpp"

PieceInstantiator::PieceInstantiator(PieceType _type, bool _team, sf::Vector2f position) : type{_type}, team{_team}
{
    this->set_sprite_position(position);
    originalposition = position;
}

void PieceInstantiator::update(float dt)
{
    
}

void PieceInstantiator::render(sf::RenderWindow& window)
{
    switch(type)
    {
        case PieceType::Pawn :
            {
            auto triangle = sf::CircleShape(45,(size_t)12);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Pawn::get_color(team));
            window.draw(triangle);
            }
            break;
            
        case PieceType::Horse :
            {
            auto triangle = sf::CircleShape(45,(size_t)3);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(sprite.getPosition() + offset);
            triangle.setFillColor(Horse::get_color(team));
            window.draw(triangle);
            }
            break;

        case PieceType::Bishop :
            {            
            auto triangle = sf::CircleShape(45,(size_t)3);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Bishop::get_color(team));
            window.draw(triangle);
            }
            break;

        case PieceType::Tower :
            {            
            auto triangle = sf::CircleShape(45,(size_t)7);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Tower::get_color(team));
            window.draw(triangle);
            }
            break;

        case PieceType::Queen :
            {
            auto triangle = sf::CircleShape(45,(size_t)3);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Queen::get_color(team));
            window.draw(triangle);
            }
            break;

        case PieceType::Trapper :
            {
            auto triangle = sf::CircleShape(45,(size_t)3);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Trapper::get_color(team));
            window.draw(triangle);
            }
            break;

        case PieceType::Crook :
            {
            auto triangle = sf::CircleShape(45,(size_t)3);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Crook::get_color(team));
            window.draw(triangle);
            }
            break;

        case PieceType::Archer :
            {
            auto triangle = sf::CircleShape(45,(size_t)5);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Archer::get_color(team));
            window.draw(triangle);
            }
            break;
        
        case PieceType::Portal :
            {
            auto triangle = sf::CircleShape(45,(size_t)3);
            triangle.setOrigin({45.f,45.f});
            triangle.setScale({1.f,2.f});
            auto offset = sf::Vector2f({(float)(Board::cell_lenght/2), (float)(Board::cell_lenght/2)});
            triangle.setPosition(this->sprite.getPosition() + offset);
            triangle.setFillColor(Portal::get_color(team));
            window.draw(triangle);
            }            
            break;

    }
}

void PieceInstantiator::return_to_origin()
{
    this->set_sprite_position(originalposition);
}

PiecePtr PieceInstantiator::make_piece(int startx, int starty)
{
    switch(type)
    {
        case PieceType::Pawn :
            return std::make_shared<Pawn>(team, startx, starty);
        case PieceType::Horse :
            return std::make_shared<Horse>(team, startx, starty);
        case PieceType::Bishop :
            return std::make_shared<Bishop>(team, startx, starty);
        case PieceType::Tower :
            return std::make_shared<Tower>(team, startx, starty);
        case PieceType::Queen :
            return std::make_shared<Queen>(team, startx, starty);
        case PieceType::Trapper :
            return std::make_shared<Trapper>(team, startx, starty);
        case PieceType::Crook :
            return std::make_shared<Crook>(team, startx, starty);
        case PieceType::Archer :
            return std::make_shared<Archer>(team, startx, starty);
        case PieceType::Portal :
            return std::make_shared<Portal>(team, startx, starty);
        default :
            return nullptr;
    }
}
