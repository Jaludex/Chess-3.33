#pragma once

#include <IGameState.hpp>
#include <Board.hpp>
#include <memory>

class StateGameplay : IGameState
{
private:
    std::shared_ptr<IPiece> selected;
    Board board;
    sf::Clock elapsed_time;
    long score;
    // Challenges
    
public:
    StateGameplay(sf::Texture texture);
    ~StateGameplay();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
	void render() override;
};


