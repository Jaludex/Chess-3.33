#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1080u, 810u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    sf::Clock clock; 
    sf::Time last_time = clock.getElapsedTime();
    sf::Time delta_time = sf::Time::Zero;
    const sf::Time target_time = sf::seconds(1)/60.f;

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
            //GAMESTATE.update((delta_time/target_time).asSeconds());
            delta_time = sf::Time::Zero;

            window.clear();
            //GAMESTATE.render(window);
            window.display();
        }
        last_time = now;
    }
}





