#include <SFML/Graphics.hpp>
#include <StateGameplay.hpp>
#include <StateMainMenu.hpp>
#include <Board.hpp>

using StatePtr = std::shared_ptr<IGameState>;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1080u, 810u}), "Chess 3.33 Alpha");
    window.setFramerateLimit(144);
    sf::Clock clock; 
    sf::Time last_time = clock.getElapsedTime();
    sf::Time delta_time = sf::Time::Zero;
    const sf::Time target_time = sf::seconds(1)/60.f;

    const sf::Color Cerulean = sf::Color(130,130,200,255);

    StatePtr gamestate = std::make_unique<StateMainMenu>();
    gamestate->init();

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        auto now = clock.getElapsedTime();
        delta_time += now - last_time;
        auto dt = delta_time/target_time;
        if (delta_time >= target_time)
        {
            switch (gamestate->update(dt))
            {
            case GameStateSignal::SwitchToGameplay:
                gamestate = std::make_shared<StateGameplay>(window);
                gamestate->init();
                break;
            case GameStateSignal::SwitchToMainMenu:
                gamestate = std::make_shared<StateMainMenu>(window);
                gamestate->init();
                break;

            //Mas casos aca
            
            case GameStateSignal::None:
            default:
                window.clear(Cerulean);
                gamestate->render(window);
                window.display();
                break;
            }

            delta_time = sf::Time::Zero;

            
        }
        last_time = now;
    }
}





