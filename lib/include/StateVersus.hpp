#pragma once

#include <IStatePlayable.hpp>

class StateVersus : public IStatePlayable
{
public:
    StateVersus(sf::RenderWindow* _window);
    ~StateVersus();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void on_resize() override;
};


