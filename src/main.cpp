#include <SFML/Graphics.hpp>
#include <Board.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1080u, 810u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    sf::Clock clock; 
    sf::Time last_time = clock.getElapsedTime();
    sf::Time delta_time = sf::Time::Zero;
    const sf::Time target_time = sf::seconds(1)/60.f;

    const sf::Color Cerulean = sf::Color(130,130,200,255);
    auto t = sf::Texture();
    Board board{t};
    float halfboard_lenght = Board::side_lenght * Board::cell_lenght / 2;
    auto pos = sf::Vector2<float>((float)(window.getSize().x - halfboard_lenght),
                                  (float)(window.getSize().y - halfboard_lenght));
    //board.set_sprite_position(pos);

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

            window.clear(Cerulean);
            //GAMESTATE.render(window);
            board.render(window);
            window.display();
        }
        last_time = now;
    }
}





