#pragma once

#include <SpriteManager.hpp>
#include "IGameState.hpp"
#include <Gametree.hpp>
#include <Board.hpp>
#include <memory>
#include <vector>
#include "IPiece.hpp"
#include "Archer.hpp"
#include "Crook.hpp"
#include "Horse.hpp"
#include "Pawn.hpp"
#include "Portal.hpp"
#include "Queen.hpp"
#include "Tower.hpp"
#include "Trapper.hpp"
#include "Bishop.hpp"
#include "PieceInstantiator.hpp"
#include <exception>

using PieceInstantPtr = std::shared_ptr<PieceInstantiator>;

class IStatePlayable : public IGameState
{
protected:
    BoardObjectPtr selected_piece;
    PieceInstantPtr selected_inst;
    Board board;
    sf::Clock elapsed_time;
    long score;
    bool player_turn;
    std::vector<PieceInstantPtr> instantiators;
    GameTree bot; 
    PieceInstantPtr clicked_instantiator(sf::Vector2i mouse_position);
    bool check_winner();
    sf::Font font; 
    sf::Text* btn_back = nullptr;

    float fix_offset(const sf::Sprite& _sprite, char t);
    
public:
    IStatePlayable(sf::RenderWindow* _window);
    ~IStatePlayable();

    void drag();
    
};