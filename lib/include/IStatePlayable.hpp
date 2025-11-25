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

enum class PlayerType
{
    P1,
    P2,
    None
};

enum class PhaseType
{
    Preparing,
    Fighting,
    Shop,
};

class IStatePlayable : public IGameState
{
protected:
    static constexpr float xmargin = Board::cell_lenght / 3;
    static constexpr float ymargin = Board::cell_lenght / 3;
    static constexpr float xoffset = Board::cell_lenght * 1.2f;
    static constexpr float yoffset = Board::cell_lenght * 1.2f;

    BoardObjectPtr selected_piece;
    PieceInstantPtr selected_inst;
    Board board;
    sf::Clock elapsed_time;
    long score;
    bool player_turn;
    std::list<PieceInstantPtr> instantiators;
    GameTree bot; 
    sf::Font font; 
    sf::Text* btn_back = nullptr;
    sf::Text* btn_start = nullptr;
    PhaseType actual_phase;

    float fix_offset(const sf::Sprite& _sprite, char t);
    PieceInstantPtr clicked_instantiator(sf::Vector2i mouse_position);
    PlayerType check_winner();
    void drag();
    void start_fight();

    virtual void adjust_elements() = 0;
    virtual void dropped_inst() = 0;
    virtual void returned_piece() = 0;
    virtual void end_fight() = 0;
    
public:
    IStatePlayable(sf::RenderWindow* _window);
    ~IStatePlayable();

    
    
};