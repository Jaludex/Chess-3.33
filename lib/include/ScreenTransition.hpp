#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum TransitionPhase
{
    Out,
    Enter,
    Stay,
    Leave
};

class ScreenTransition
{
    private:
    float elapsed_frames;
    float target_frames;
    TransitionPhase phase;
    public:
    ScreenTransition();
    bool is_transitioning();
    bool is_staying();
    bool is_out();
    void enter(float);
    void leave(float);
    void update(float dt);
    void render(sf::RenderWindow& window);
};
