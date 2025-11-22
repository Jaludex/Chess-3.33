#pragma once
#include <IGameState.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class StateMainMenu : public IGameState
{
private:
    sf::Font font;
    sf::Text* text_title = nullptr;
    
    sf::Text* btn_play = nullptr;
    sf::Text* btn_tutorial = nullptr;
    sf::Text* btn_exit = nullptr;

    void setupText(sf::Text* text, const std::string& str, float yPos);
    
    bool isMouseOver(const sf::Text& text, const sf::Vector2i& mousePos);

public:
    StateMainMenu(sf::RenderWindow* _window); 
    ~StateMainMenu();

    void init() override;
    void terminate() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
};