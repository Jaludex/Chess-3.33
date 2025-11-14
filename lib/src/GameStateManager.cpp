#include <GameStateManager.hpp>

GameStateManager::GameStateManager(sf::RenderWindow& _window) : window(&_window)
{

}
GameStateManager::~GameStateManager()
{

}

void GameStateManager::go_back()
{
    states.pop();
}

void GameStateManager::go_to(GameStatePtr new_state)
{
    states.push(new_state);
}

void GameStateManager::init()
{
    if (states.empty())
    {
        states.push(std::make_shared<StateMainMenu>(window));
        states.top()->init();
    }
}   

void GameStateManager::update(float dt)
{
    //Logica para cambiar los states em base a su atributo de cambiar

    states.top()->update(dt);
}

void GameStateManager::render(sf::RenderWindow& window)
{
    states.top()->render(window);
}

void GameStateManager::terminate()
{
    
}