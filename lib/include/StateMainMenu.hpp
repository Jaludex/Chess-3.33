#pragma once

#include <IGameState.hpp>

class StateMainMenu : public IGameState
{
private:
    //Aqui se pueden agregar botones mas elaborados
public:
    StateMainMenu(sf::RenderWindow* _window);
    ~StateMainMenu();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
};