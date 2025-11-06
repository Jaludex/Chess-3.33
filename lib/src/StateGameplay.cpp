#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow& _window) : board(sf::Texture ({(unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)}))
{
    window = &_window;
}
StateGameplay::~StateGameplay(){}

void StateGameplay::init()
{
    float halfboard_lenght = Board::side_lenght * Board::cell_lenght / 2;
    auto pos = sf::Vector2<float>((float)(window->getSize().x/2 - halfboard_lenght),
                                  (float)(window->getSize().y/2 - halfboard_lenght));
    board.set_sprite_position(pos);

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
            selected->set_sprite_position({(float)mouse_position.x, (float)mouse_position.y});
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
    board.render(window);
}
