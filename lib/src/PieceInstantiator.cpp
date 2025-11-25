#include "PieceInstantiator.hpp"

PieceInstantiator::PieceInstantiator(PieceType _type, bool _team, sf::Vector2f position, sf::Texture texture) : IGameObject(texture), type{_type}, team{_team}
{
    this->set_sprite_position(position);
    originalposition = position;
}

void PieceInstantiator::update(float dt)
{
    
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
    return make_board_object(type, team, startx, starty);
}

BoardObjectPtr make_board_object(PieceType type, bool team, int startx, int starty)
{
    std::string color = (team)? "white_": "black_";
    switch(type)
    {
        case PieceType::Pawn :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Pawn>(team, SpriteManager::get_piece_texture(color+"pawn")));
        case PieceType::Horse :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Horse>(team, SpriteManager::get_piece_texture(color+"horse")));
        case PieceType::Bishop :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Bishop>(team, SpriteManager::get_piece_texture(color+"bishop")));
        case PieceType::Tower :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Tower>(team, SpriteManager::get_piece_texture(color+"rook")));
        case PieceType::Queen :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Queen>(team, SpriteManager::get_piece_texture(color+"queen")));
        case PieceType::Trapper :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Trapper>(team, SpriteManager::get_piece_texture(color+"trapper")));
        case PieceType::Crook :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Crook>(team, SpriteManager::get_piece_texture(color+"crook")));
        case PieceType::Archer :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Archer>(team, SpriteManager::get_piece_texture(color+"archer")));
        case PieceType::Portal :
            return std::make_shared<InBoardObject>(Position(startx, starty), std::make_shared<Portal>(team, SpriteManager::get_piece_texture(color+"portal")));
        default :
            return nullptr;
    }
}
