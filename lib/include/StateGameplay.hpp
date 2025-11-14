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
#include <map>
#include <exception>
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
    std::map<std::string,sf::Texture> texture_map;
    PieceInstantPtr clicked_instantiator(sf::Vector2i mouse_position);
    // Challenges
    
public:
    StateGameplay(sf::RenderWindow& _window);
    ~StateGameplay();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
    void load_texture_piece(std::string type, std::string file);
    const sf::Texture& get_piece_texture(std::string type);
    sf::Vector2i get_relative_mouse_position();
    void drag();
};


