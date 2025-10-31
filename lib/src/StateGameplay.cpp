#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::Texture texture, sf::RenderWindow& _window) : board(texture)
{
    window = &_window;
}
StateGameplay::~StateGameplay(){}

void StateGameplay::init()
{
    board.add_piece(std::make_shared<Bishop>(true, 1, 5));
}

void StateGameplay::terminate()
{
    //si usamos shared pointers entonces no necesitamos eliminar la pieza creada en init
}

void StateGameplay::update(float dt)
{
    drag();
    
    board.update(dt);
}

sf::Vector2i StateGameplay::get_relative_mouse_position()
{
    return sf::Mouse::getPosition(*window);
}

void StateGameplay::drag()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        auto mouse_position = get_relative_mouse_position();
        if (selected)
        {
            selected->set_sprite_position({mouse_position.x, mouse_position.y});
        }
        else
        {
            selected = board.clicked_piece(mouse_position);
        }
    }
    else if (selected)
    {
        board.drop_piece(selected);

        selected = nullptr;
    }
}

void StateGameplay::render(sf::RenderWindow& window)
{
    //board.render(window)
}
