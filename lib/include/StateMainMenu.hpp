#pragma once
#include <IGameState.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
struct Button
{
    sf::Sprite btn_sprite;
    sf::Text btn_text;
    Button(const sf::Texture& texture, const sf::Font& font)
        : btn_sprite(texture), btn_text(font)
    {
    }
};
class StateMainMenu : public IGameState
{
private:
    sf::Font font;
    sf::Texture button_texture;
    sf::Text* text_title = nullptr;
    
    Button* btn_play = nullptr;
    Button* btn_tutorial = nullptr;
    Button* btn_exit = nullptr;

    void setup_button(Button* button, const std::string& str, float y_pos);

public:
    StateMainMenu(sf::RenderWindow* _window); 
    ~StateMainMenu();

    void init() override;
    void terminate() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void on_resize() override;
};