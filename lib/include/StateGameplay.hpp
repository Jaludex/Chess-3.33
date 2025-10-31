#pragma once

#include <IGameState.hpp>
#include <Board.hpp>

class StateGameplay : IGameState
{
private:

    Board board;
    sf::Clock elapsed_time;
    long score;
    // Challenges
    

public:
    StateGameplay(/* args */);
    ~StateGameplay();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
	void render() override;
};


