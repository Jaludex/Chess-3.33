#include "StateMainMenu.hpp"

StateMainMenu::StateMainMenu(sf::RenderWindow* _window)
    :    text_title(nullptr), btn_play(nullptr), btn_tutorial(nullptr), btn_exit(nullptr)
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
    delete btn_play;
    btn_play = nullptr;
    delete btn_tutorial;
    btn_tutorial = nullptr;
    delete btn_exit;
    btn_exit = nullptr;
}

void StateMainMenu::init()
{
    if (!font.openFromFile("assets/fonts/arial.ttf")) 
    {
        std::cerr << "ERROR: No se pudo cargar la fuente (arial.ttf)" << std::endl;

    }
    

    text_title = new sf::Text(font, "CHESS 3.33", 60);
    btn_play = new sf::Text(font,"JUGAR", 40);
    btn_tutorial = new sf::Text(font,"TUTORIAL", 40);
    btn_exit = new sf::Text(font,"SALIR", 40);

    sf::Vector2u winSize = window->getSize();
    float midX = winSize.x / 2.0f;

    text_title->setFillColor(sf::Color::White);
    text_title->setStyle(sf::Text::Bold);
    
    sf::FloatRect bounds = text_title->getLocalBounds();
    text_title->setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    text_title->setPosition({midX, winSize.y * 0.2f});

    setupText(btn_play, "JUGAR", winSize.y * 0.45f);
    setupText(btn_tutorial, "TUTORIAL", winSize.y * 0.60f);
    setupText(btn_exit, "SALIR", winSize.y * 0.75f);
}

void StateMainMenu::setupText(sf::Text* text, const std::string& str, float yPos)
{
    text->setString(str);
    text->setCharacterSize(40);
    text->setFillColor(sf::Color(200, 200, 200)); 
    
    sf::FloatRect bounds = text->getLocalBounds();
    text->setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
    text->setPosition({(float)window->getSize().x / 2.0f, yPos});
}

void StateMainMenu::update(float dt)
{
    sf::Vector2i mousePos = get_relative_mouse_position();
    
    auto updateButtonColor = [&](sf::Text* btn) {
        if (isMouseOver(*btn, mousePos))
            btn->setFillColor(sf::Color::Yellow);
        else
            btn->setFillColor(sf::Color::White);
    };

    updateButtonColor(btn_play);
    updateButtonColor(btn_tutorial);
    updateButtonColor(btn_exit);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (isMouseOver(*btn_play, mousePos))
        {
            this->go_to = StateType::Gameplay;
        }
        else if (isMouseOver(*btn_tutorial, mousePos))
        {
            this->go_to = StateType::Tutorial;
        }
        else if (isMouseOver(*btn_exit, mousePos))
        {
            window->close(); 
        }
    }
}

bool StateMainMenu::isMouseOver(const sf::Text& text, const sf::Vector2i& mousePos)
{
    sf::FloatRect bounds = text.getGlobalBounds();
    return bounds.contains({(float)mousePos.x, (float)mousePos.y});
}

void StateMainMenu::render(sf::RenderWindow& target)
{
    target.draw(*text_title);
    target.draw(*btn_play);
    target.draw(*btn_tutorial);
    target.draw(*btn_exit);
}