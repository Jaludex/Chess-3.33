/*#include "StateMainMenu.hpp"
#include <iostream>

// Constructor (solo para inicializar puntero y tipo)
StateMainMenu::StateMainMenu(sf::RenderWindow* window_ptr)
{
    window = window_ptr;
    type = StateType::MainMenu;
    go_to = StateType::None;
}

StateMainMenu::~StateMainMenu() {}

void StateMainMenu::init() 
{
    // Carga de fuente
    if (!menu_font.loadFromFile("assets/fonts/arial.ttf")) {
        if (!menu_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "ERROR: No se pudo cargar fuente para el menu" << std::endl;
        }
    }

    sf::Vector2u window_size = window->getSize();
    float center_x = (float)window_size.x / 2.0f;

    // Título
    title_text.setFont(menu_font);
    title_text.setString("CHESS 3.33");
    title_text.setCharacterSize(60);
    title_text.setFillColor(sf::Color::White);
    title_text.setStyle(sf::Text::Bold);
    
    sf::FloatRect title_bounds = title_text.getLocalBounds();
    title_text.setOrigin(title_bounds. + title_bounds.width / 2.0f, title_bounds.top + title_bounds / 2.0f);
    
    title_text.setPosition(sf::Vector2f(center_x, 150.0f)); 

    // Crear Botones
    create_button(center_x, 350.0f, "JUGAR", StateType::Gameplay);
    create_button(center_x, 450.0f, "TUTORIAL", StateType::Tutorial);
    create_button(center_x, 550.0f, "SALIR", StateType::None);
}

void StateMainMenu::create_button(float x_pos, float y_pos, std::string button_label, StateType action_type_param)
{
    MenuButton button_data;
    button_data.action_type = action_type_param;

    // Forma
    button_data.button_shape.setSize(sf::Vector2f(300.0f, 60.0f));
    button_data.button_shape.setOrigin(150.0f, 30.0f);
    button_data.button_shape.setPosition(sf::Vector2f(x_pos, y_pos));
    button_data.button_shape.setFillColor(sf::Color(50, 50, 60));
    button_data.button_shape.setOutlineColor(sf::Color::White);
    button_data.button_shape.setOutlineThickness(2.0f);

    // Texto
    button_data.button_text.setFont(menu_font);
    button_data.button_text.setString(button_label);
    button_data.button_text.setCharacterSize(24);
    button_data.button_text.setFillColor(sf::Color::White);
    
    sf::FloatRect text_bounds = button_data.button_text.getLocalBounds();
    button_data.button_text.setOrigin(text_bounds.left + text_bounds.width/2.0f, text_bounds.top + text_bounds.height/2.0f);
    
    button_data.button_text.setPosition(sf::Vector2f(x_pos, y_pos));

    menu_buttons.push_back(button_data);
}

void StateMainMenu::terminate()
{
    menu_buttons.clear();
}

void StateMainMenu::update(float dt)
{
    sf::Vector2i mouse_pos_i = sf::Mouse::getPosition(*window);
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos_i.x), static_cast<float>(mouse_pos_i.y));
    
    bool clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    for (auto& button_data : menu_buttons)
    {
        if (button_data.button_shape.getGlobalBounds().contains(mouse_pos_f))
        {
            button_data.button_shape.setFillColor(sf::Color(100, 100, 180));
            
            if (clicked)
            {
                if (button_data.action_type == StateType::None) 
                {
                    window->close();
                }
                else 
                {
                    go_to = button_data.action_type; 
                    sf::sleep(sf::milliseconds(150));
                }
            }
        }
        else
        {
            button_data.button_shape.setFillColor(sf::Color(50, 50, 60));
        }
    }
}

void StateMainMenu::render(sf::RenderWindow& window_ref)
{
    window_ref.clear(sf::Color(20, 20, 30));

    window_ref.draw(title_text);

    for (auto& button_data : menu_buttons)
    {
        window_ref.draw(button_data.button_shape);
        window_ref.draw(button_data.button_text);
    }
}
*/