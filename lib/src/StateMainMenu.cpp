#include "StateMainMenu.hpp"

StateMainMenu::StateMainMenu(sf::RenderWindow* _window)
    :  background_sprite(background_tex),text_title(nullptr), btn_play(nullptr), btn_tutorial(nullptr), btn_exit(nullptr)
{
    window = _window;
    type = StateType::MainMenu;
    go_to = StateType::None;
}

StateMainMenu::~StateMainMenu()
{
    terminate();
}

void StateMainMenu::terminate()
{

    delete text_title;
    text_title = nullptr;

    delete btn_stats;
    btn_stats = nullptr;

    delete btn_play;
    btn_play = nullptr;

    delete btn_tutorial;
    btn_tutorial = nullptr;

    delete btn_exit;
    btn_exit = nullptr;
}

void StateMainMenu::init()
{
    std::cout<<"8 ";
    if (!font.openFromFile("assets/fonts/arial.ttf")) 
    {
        std::cerr << "ERROR: No se pudo cargar la fuente (arial.ttf)" << std::endl;

    }
    if(!background_tex.loadFromFile("assets/background_menu.png"))
    text_title = new sf::Text(font, "CHESS 3.33", 60);
    if (!button_texture.loadFromFile("assets/button.png")) 
    {
        sf::Image img;
        img.resize(sf::Vector2u(200, 50), sf::Color::White);
        
        if (!button_texture.loadFromImage(img))
        {
             std::cerr << "FATAL: No se pudo crear textura de respaldo." << std::endl;
        }
        std::cerr << "WARNING: assets/button.png no encontrado, usando textura blanca." << std::endl;
    }
    button_texture.setSmooth(true); 

    text_title = new sf::Text(font, "CHESS 3.33", 60);
    btn_stats = new Button(button_texture, font);
    btn_play = new Button(button_texture, font);
    btn_tutorial = new Button(button_texture, font);
    btn_exit = new Button(button_texture, font);

    text_title->setFillColor(sf::Color::White);
    text_title->setStyle(sf::Text::Bold);
    
    on_resize();
}

void StateMainMenu::on_resize()
{
    sf::Vector2u win_size = window->getSize();
    float midX = win_size.x / 2.0f;

    sf::FloatRect bounds = text_title->getLocalBounds();
    text_title->setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    text_title->setPosition({midX, win_size.y * 0.2f});

    setup_button(btn_play,     "JUGAR",    win_size.y * 0.40f);
    setup_button(btn_stats,    "PUNTAJES", win_size.y * 0.55f);
    setup_button(btn_tutorial, "TUTORIAL", win_size.y * 0.70f);
    setup_button(btn_exit,     "SALIR",    win_size.y * 0.85f);
}
void StateMainMenu::setup_button(Button* button, const std::string& str, float y_pos)
{
    sf::Vector2u win_size = window->getSize();

    unsigned int char_size = static_cast<unsigned int>(win_size.y * 0.036f);
    
    if (char_size < 20) char_size = 20; 

    button->btn_text.setFont(font);
    button->btn_text.setString(str);
    button->btn_text.setCharacterSize(char_size);
    button->btn_text.setFillColor(sf::Color::White); 
    
    sf::FloatRect text_bounds = button->btn_text.getLocalBounds();
    button->btn_text.setOrigin({
        text_bounds.position.x + text_bounds.size.x / 2.0f, 
        text_bounds.position.y + text_bounds.size.y / 2.0f 
    });

    button->btn_sprite.setTexture(button_texture);
    sf::FloatRect sprite_local_bounds = button->btn_sprite.getLocalBounds();

    float target_width = static_cast<float>(win_size.x) * 0.15f;
    float target_height = static_cast<float>(win_size.y) * 0.10f;

    if (target_width < 180.0f) target_width = 180.0f;
    if (target_height < 60.0f) target_height = 60.0f;

    float scale_x = target_width / sprite_local_bounds.size.x;
    float scale_y = target_height / sprite_local_bounds.size.y;

    button->btn_sprite.setScale(sf::Vector2f(scale_x, scale_y)); 

    button->btn_sprite.setOrigin({
        sprite_local_bounds.size.x / 2.0f, 
        sprite_local_bounds.size.y / 2.0f
    });
    float mid_x = (float)win_size.x / 2.0f;    
    
    button->btn_sprite.setPosition({mid_x, y_pos});
    float vertical_correction = - (target_height * 0.05f); 
    button->btn_text.setPosition({mid_x, y_pos + vertical_correction});
}

void StateMainMenu::update(float dt)
{
    sf::Vector2i mouse_pos = get_relative_mouse_position();
    
   auto update_button_color = [&](Button* btn) {
        if (is_mouse_over(btn->btn_sprite, mouse_pos))
            btn->btn_sprite.setColor(sf::Color(200, 200, 200)); 
        else
            btn->btn_sprite.setColor(sf::Color::White);
    };

    update_button_color(btn_stats);
    update_button_color(btn_play);
    update_button_color(btn_tutorial);
    update_button_color(btn_exit);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (is_mouse_over(btn_play->btn_sprite, mouse_pos))
        {
            this->go_to = StateType::Gameplay;
        }
        else if (is_mouse_over(btn_stats->btn_sprite, mouse_pos))
        {
            this->go_to = StateType::Stats;
        }
        else if (is_mouse_over(btn_tutorial->btn_sprite, mouse_pos))
        {
            this->go_to = StateType::Tutorial;
        }
        else if (is_mouse_over(btn_exit->btn_sprite, mouse_pos))
        {
            window->close(); 
        }
    }
}

void StateMainMenu::render(sf::RenderWindow& target)
{
    
    target.draw(*text_title);
    target.draw(btn_play->btn_sprite);
    target.draw(btn_play->btn_text); 

    target.draw(btn_stats->btn_sprite);
    target.draw(btn_stats->btn_text);

    target.draw(btn_tutorial->btn_sprite);
    target.draw(btn_tutorial->btn_text);

    target.draw(btn_exit->btn_sprite);
    target.draw(btn_exit->btn_text);
}