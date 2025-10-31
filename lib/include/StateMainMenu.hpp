#pragma once

#include <IGameState.hpp>

class StateMainMenu : public IGameState
{
private:
    

public:
    StateMainMenu(/* args */);
    ~StateMainMenu();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
	void render() override;
};

StateMainMenu::StateMainMenu(/* args */)
{
}

StateMainMenu::~StateMainMenu()
{
}
