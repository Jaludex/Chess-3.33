#include <SFML/Graphics.hpp>
#include <StateGameplay.hpp>
#include <Board.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1080u, 810u}), "Chess 3.33 Alpha");
    window.setFramerateLimit(144);
    sf::Clock clock; 
    sf::Time last_time = clock.getElapsedTime();
    sf::Time delta_time = sf::Time::Zero;
    const sf::Time target_time = sf::seconds(1)/60.f;

    const sf::Color Cerulean = sf::Color(130,130,200,255);

    StateGameplay gamestate(window);
    gamestate.init();

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
        if (delta_time >= target_time)
        {
            gamestate.update(delta_time/target_time);
            delta_time = sf::Time::Zero;

            window.clear(Cerulean);
            gamestate.render(window);
            window.display();
        }
        last_time = now;
    }
}





