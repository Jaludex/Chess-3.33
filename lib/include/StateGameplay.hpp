#pragma once

#include <IStatePlayable.hpp>

class StateGameplay : public IStatePlayable
{
protected:
    std::list<PieceType> inventory;

public:
    StateGameplay(sf::RenderWindow* _window);
    ~StateGameplay();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void on_resize() override;
    void adjust_elements() override;
    void dropped_inst() override;
    void load_instanciators();
};


