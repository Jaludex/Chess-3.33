#pragma once

#include <IStatePlayable.hpp>

class StatePractice : public IStatePlayable
{
protected:
    sf::Texture background_texture; 
    sf::Sprite background_sprite;

    void load_instanciators() override;
    void adjust_elements() override;
    void dropped_inst() override;
    void returned_piece() override;
    void end_fight(PlayerType winner) override;

public:
    StatePractice(sf::RenderWindow* _window);
    ~StatePractice();

    void init() override;                // inicializar aspectos del gamestate
    void terminate() override;           // eliminar memoria reservada dinámicamente o cosas que se tengan que manejar al final de ese estado de juego.
	void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void on_resize() override;
    
};


