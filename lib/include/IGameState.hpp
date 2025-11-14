#pragma once
#include <SFML/Graphics.hpp>

enum class StateType
{
    MainMenu,
    Gameplay,
    Options,
    Credits,
    Gameover,
    Shop,
    Stats,
    None
};

class IGameState
{
protected:
    sf::RenderWindow* window;
    //sf::Sprite background;
public:
    StateType type;
    StateType go_to;
    virtual void init() = 0;                // inicializar aspectos del gamestate
    virtual void terminate() = 0;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	virtual void update(float dt) = 0;
	virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2i get_relative_mouse_position();
};

using GameStatePtr = std::shared_ptr<IGameState>;
