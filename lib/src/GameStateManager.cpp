#include <GameStateManager.hpp>

GameStateManager::GameStateManager(sf::RenderWindow& _window) : window(&_window)
{

}
GameStateManager::~GameStateManager()
{

}

void GameStateManager::go_back()
{    
    SoundManager::stop_music();
    if (!states.empty())
    {
        auto* playableState = dynamic_cast<IStatePlayable*>(states.top().get());
        if (playableState != nullptr)
        {
            this->last_score = playableState->get_score(); 
            this->last_round = playableState->get_round();
        }
    }
    states.top()->terminate();
    states.pop();
    this->on_resize();
    transition.leave(30);
    SoundManager::play_music(states.top()->music, true);
}

void GameStateManager::go_to(GameStatePtr new_state)
{
    SoundManager::stop_music();
    states.push(new_state);
    new_state->init();
    transition.leave(30);
    SoundManager::play_music(new_state->music, true);
}

void GameStateManager::init()
{
    if (states.empty())
    {
        states.push(std::make_shared<StateMainMenu>(window));
        states.top()->init();
        SoundManager::play_music(MusicType::MainMenu, true);
    }
}   

void GameStateManager::update(float dt)
{
    if (states.empty()) return;
    StateType next_state = states.top()->go_to;
    
    
    if (next_state != StateType::None && transition.is_out())
    {
        transition.enter(30);
    }

    if (next_state != StateType::None && transition.is_staying())
    {
        StateType next_state = states.top()->go_to;
        states.top()->go_to = StateType::None;
        switch(next_state)
        {
            case StateType::MainMenu:
                {
                    SoundManager::stop_music();
                    states.pop();
                    states.push(std::make_shared<StateMainMenu>(this->window));
                    states.top()->init();
                    SoundManager::play_music(states.top()->music, true);
                }       
                break;
            case StateType::Gameplay:
                {
                    go_to(std::make_shared<StateGameplay>(this->window));
                }    
                break;
            case StateType::Stats:
            {
                auto stats_state = std::make_shared<StateStats>(this->window);
                if (this->last_score > 0 || this->last_round > 1)
                {
                    stats_state->set_current_match(this->last_score, this->last_round);
                    this->last_score = 0;
                    this->last_round = 1;
                }

                go_to(stats_state); 
            }
            break;
            break;
            case StateType::Tutorial:
                {
                    go_to(std::make_shared<StateTutorial>(this->window)); 
                }
            break;
            case StateType::Practice:
                {
                    go_to(std::make_shared<StatePractice>(this->window)); 
                }
            break;
            case StateType::Versus:
                {
                    go_to(std::make_shared<StateVersus>(this->window)); 
                }
            break;
            case StateType::Return:
                {
                    go_back();
                    if (this->last_score > 0 || this->last_round > 1)
                    {
                        auto stats_state = std::make_shared<StateStats>(this->window);
                        stats_state->set_current_match(this->last_score, this->last_round);
                        
                        this->last_score = 0;
                        this->last_round = 1;
                        
                        states.push(stats_state);
                        stats_state->init();
                    }
                }
                break;
        
            default:
                break;
        }
    }
    
    if (!states.empty() && transition.is_out()) 
    {
        states.top()->update(dt);
    }

    transition.update(dt);
}

void GameStateManager::render(sf::RenderWindow& _window)
{
    states.top()->render(_window);
    transition.render(_window);
}

void GameStateManager::terminate()
{
    
}

void GameStateManager::on_resize()
{
    states.top()->on_resize();
}
IGameState* GameStateManager::get_current_state()
{
    return &(*states.top());
}