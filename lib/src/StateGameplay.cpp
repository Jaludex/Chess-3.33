#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow& _window) : board(sf::Texture ({(unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)})), player_turn(true)
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

    board.add_piece(std::make_shared<Trapper>(true, 1, 5));
    board.add_piece(std::make_shared<Queen>(true, 1, 0));
    board.add_piece(std::make_shared<Trapper>(false, 4, 1));
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
            //Version para moverse dentro de la cuadricula
            /* sf::Vector2f relative_position = sf::Vector2f((float)mouse_position.x, (float)mouse_position.y) - board.get_sprite().getPosition();
            Position position_on_board(relative_position.x / Board::cell_lenght, relative_position.y / Board::cell_lenght);
            auto offset = sf::Vector2f({(float)(position_on_board.x * Board::cell_lenght), (float)(position_on_board.y * Board::cell_lenght)});
            selected->set_sprite_position(board.get_sprite().getPosition() + offset); */

            selected->set_sprite_position({(float)mouse_position.x, (float)mouse_position.y});
        }
        else
        {
            selected = board.clicked_piece(mouse_position);
            if (selected)
            {
                if (selected->get_team() != player_turn) selected = nullptr;                
            } 
        }
    }
    else if (selected)
    {
        if (board.drop_piece(selected)) player_turn = !player_turn;

        selected = nullptr;
    }
}

void StateGameplay::render(sf::RenderWindow& window)
{
    board.render(window);
    if (selected) board.render_highlights(window, selected->get_valid_moves());
    board.render_pieces(window);
}
