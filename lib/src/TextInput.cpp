#include "TextInput.hpp"

// Constructor
InputBox::InputBox(const sf::Font& font, const std::string& prompt)
    : is_active(false), prompt_text(prompt), text_display(font)
{
    text_display.setFont(font);
    text_display.setCharacterSize(30);
    text_display.setFillColor(sf::Color::Yellow);
    text_display.setPosition(sf::Vector2f(100, 100));
    text_display.setString(prompt_text + "_"); 
}

void InputBox::activate() 
{
    is_active = true;
    input_string = "";
    std::cout << "InputBox Activada. Escribiendo..." << std::endl;
}

void InputBox::deactivate() 
{
    is_active = false;
    std::cout << "InputBox Desactivada. Nombre final: " << get_result() << std::endl;
}

void InputBox::handle_event(const sf::Event& event) 
{
    /*if (!is_active) 
    {
        return; 
    }
    if (event.is<sf::Event::TextEntered>())
    {
        auto text_event = event.getIf<sf::Event::TextEntered>();
        unsigned int unicode = text_event->unicode;

        if (unicode < 128)
        {
            char entered_char = static_cast<char>(unicode);
            
            if (entered_char == '\b')
            {
                if (input_string.getSize() > 0)
                    input_string.erase(input_string.getSize() - 1);
            }
            else if (entered_char == '\r' || entered_char == '\n')
            {
                deactivate();
            }
            else
            {
                if (input_string.getSize() < 30) { 
                     input_string += entered_char;
                }
            }
        }
    }
    text_display.setString(prompt_text + input_string + (is_active ? "_" : ""));*/
}

void InputBox::draw(sf::RenderWindow& window) 
{
    if (is_active) {
        window.draw(text_display);
    }
}