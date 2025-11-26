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
#include <FileManager.hpp>
#include "../include/json.hpp" 
#include <exception>

using PieceInstantPtr = std::shared_ptr<PieceInstantiator>;
using json = nlohmann::json;

class StateGameplay : public IGameState
{
private:
    sf::Texture background_texture; 
    sf::Sprite background_sprite;

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

    sf::Texture tex_exit;       
    sf::Sprite btn_back_sprite;
    sf::Font font; 
    sf::Text* btn_back = nullptr;
    bool set_up_black_team();
    // Challenges
    
public:
    StateGameplay(sf::RenderWindow* _window);
    ~StateGameplay();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void drag();
    void on_resize() override;
};


