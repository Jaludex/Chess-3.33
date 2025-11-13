#pragma once

#include <IGameState.hpp>
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

using PieceInstantPtr = std::shared_ptr<PieceInstantiator>;

class StateGameplay : IGameState
{
private:
    BoardObjectPtr selected_piece;
    PieceInstantPtr selected_inst;
    Board board;
    sf::Clock elapsed_time;
    long score;
    sf::RenderWindow* window;
    bool player_turn;
    std::vector<PieceInstantPtr> instantiators;

    PieceInstantPtr clicked_instantiator(sf::Vector2i mouse_position);
    // Challenges
    
public:
    StateGameplay(sf::RenderWindow& _window);
    ~StateGameplay();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;

    sf::Vector2i get_relative_mouse_position();
    void drag();
};


