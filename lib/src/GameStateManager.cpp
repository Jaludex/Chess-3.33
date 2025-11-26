#include <GameStateManager.hpp>
#include"StateTutorial.hpp"
GameStateManager::GameStateManager(sf::RenderWindow& _window) : window(&_window)
{

}
GameStateManager::~GameStateManager()
{

}

void GameStateManager::go_back()
{    
    states.top()->terminate();
    states.pop();
    this->on_resize();
}

void GameStateManager::go_to(GameStatePtr new_state)
{
    states.push(new_state);
    new_state->init();
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
    if (states.empty()) return;
    StateType next_state = states.top()->go_to;
    
    if (next_state != StateType::None)
    {
        StateType next_state = states.top()->go_to;
        states.top()->go_to = StateType::None;
        switch(next_state)
        {
            case StateType::MainMenu:
                {
                    states.pop();
                    states.push(std::make_shared<StateMainMenu>(this->window));
                    states.top()->init();
                }       
                break;
            case StateType::Gameplay:
                {
                    go_to(std::make_shared<StateGameplay>(this->window));
                }    
                break;
            case StateType::Stats:
            {
                go_to(std::make_shared<StateStats>(this->window)); 
            }
            break;
            case StateType::Tutorial:
                {
                    go_to(std::make_shared<StateTutorial>(this->window)); 
                }
            break;
            case StateType::Return:
                {
                    go_back();
                }
                break;
        
            default:
                break;
        }
    }
    if (!states.empty()) 
    {
        states.top()->update(dt);
    }
}

void GameStateManager::render(sf::RenderWindow& _window)
{
    states.top()->render(_window);
}

void GameStateManager::terminate()
{
    
}

void GameStateManager::on_resize()
{
    states.top()->on_resize();
}
