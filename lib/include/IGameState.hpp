#pragma once

class IGameState
{
private:
    
public:

    virtual void init() = 0;                // inicializar aspectos del gamestate
    virtual void terminate() = 0;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	virtual void update(float dt) = 0;
	virtual void render() = 0;

};
