#include <SFML/Window/Event.hpp> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

struct InputBox {
    sf::Font font;
    sf::String input_string;
    sf::Text text_display;
    bool is_active;
    std::string prompt_text;

    InputBox(const sf::Font& font, const std::string& prompt);
    
    void activate();
    void deactivate();
    bool is_active_status() const { return is_active; }

    void handle_event(const sf::Event& event);

    void draw(sf::RenderWindow& window);

    std::string get_result() const { return input_string.toAnsiString(); }
};