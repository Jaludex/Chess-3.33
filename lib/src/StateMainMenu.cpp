#include <StateMainMenu.hpp>

StateMainMenu::StateMainMenu(sf::RenderWindow* _window)
{
    window = _window;
    type = StateType::MainMenu;
    go_to = StateType::None;
}
StateMainMenu::~StateMainMenu() {}

void StateMainMenu::init() 
{
    
}

void StateMainMenu::terminate()
{

}

void StateMainMenu::update(float dt)
{

}

void StateMainMenu::render(sf::RenderWindow& window)
{

}