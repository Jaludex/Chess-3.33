#pragma once
#include <IGameState.hpp>
#include <vector>
#include <string>

/*class StateMainMenu : public IGameState
{
private:
    sf::Font menu_font;
    sf::Text title_text;
    
    struct MenuButton {
        sf::RectangleShape button_shape;
        sf::Text button_text;
        StateType action_type;
    };
    std::vector<MenuButton> menu_buttons;

    void create_button(float x_pos, float y_pos, std::string button_label, StateType action_type_param);

public:
    StateMainMenu(sf::RenderWindow* window_ptr); 
    ~StateMainMenu();

    void init() override;
    void terminate() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window_ref) override;
};*/