#include "PieceInstantiator.hpp"

PieceInstantiator::PieceInstantiator(PieceType _type, bool _team, sf::Vector2f position, sf::Texture texture) : IGameObject(texture), type{_type}, team{_team}
{
    this->set_sprite_position(position);
    originalposition = position;
}

void PieceInstantiator::update(float dt)
{
    
}

PieceType PieceInstantiator::get_type()
{
    return this->type;
}

bool PieceInstantiator::get_team()
{
    return this->team;
}

void PieceInstantiator::render(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void PieceInstantiator::return_to_origin()
{
    this->set_sprite_position(originalposition);
}

BoardObjectPtr PieceInstantiator::make_piece(int startx, int starty)
{
    sf::Texture texture = this->texture;
    switch(type)
    {
        case PieceType::Pawn :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Pawn>(team, texture));
        case PieceType::Horse :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Horse>(team, texture));
        case PieceType::Bishop :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Bishop>(team, texture));
        case PieceType::Tower :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Tower>(team, texture));
        case PieceType::Queen :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Queen>(team, texture));
        case PieceType::Trapper :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Trapper>(team, texture));
        case PieceType::Crook :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Crook>(team, texture));
        case PieceType::Archer :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Archer>(team, texture));
        case PieceType::Portal :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Portal>(team, texture));
        default :
            return nullptr;
    }
}
