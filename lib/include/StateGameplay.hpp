#pragma once

#include <IGameState.hpp>
#include <Board.hpp>
#include <memory>

#include <Bishop.hpp>

class StateGameplay : public IGameState
{
private:
    PiecePtr selected;
    Board board;
    sf::Clock elapsed_time;
    long score;
    sf::RenderWindow* window;
    bool player_turn;
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


