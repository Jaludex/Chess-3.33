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

    float xmargin = Board::cell_lenght;
    float ymargin = Board::cell_lenght * 2;
    float xoffset = Board::cell_lenght * 1.2f;
    float yoffset = Board::cell_lenght * 1.2f;
    float width = (float)window->getSize().x;
    
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Pawn, true, sf::Vector2f(x_margin, ymargin)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Horse, true, sf::Vector2f(x_margin, ymargin + yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Bishop, true, sf::Vector2f(x_margin, ymargin + 2*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Tower, true, sf::Vector2f(x_margin, ymargin + 3*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Queen, true, sf::Vector2f(x_margin, ymargin + 4*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Trapper, true, sf::Vector2f(x_margin + xoffset, ymargin + yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Crook, true, sf::Vector2f(x_margin + xoffset, ymargin + 2*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Archer, true, sf::Vector2f(x_margin + xoffset, ymargin + 3*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Portal, true, sf::Vector2f(x_margin + xoffset, ymargin + 4*yoffset)));

    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Pawn, false, sf::Vector2f(width - x_margin, ymargin)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Horse, false, sf::Vector2f(width - x_margin, ymargin + yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Bishop, false, sf::Vector2f(width - x_margin, ymargin + 2*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Tower, false, sf::Vector2f(width - x_margin, ymargin + 3*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Queen, false, sf::Vector2f(width - x_margin, ymargin + 4*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Trapper, false, sf::Vector2f(width - x_margin - xoffset, ymargin + yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Crook, false, sf::Vector2f(width - x_margin - xoffset, ymargin + 2*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Archer, false, sf::Vector2f(width - x_margin - xoffset, ymargin + 3*yoffset)));
    instantiators.add(std::make_shared<PieceInstantiator>(PieceType::Portal, false, sf::Vector2f(width - x_margin - xoffset, ymargin + 4*yoffset)));

    board.add_piece(std::make_shared<Crook>(true, 1, 5));
    board.add_piece(std::make_shared<Queen>(true, 1, 0));
    board.add_piece(std::make_shared<Trapper>(false, 4, 2));
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
                auto piece = 
                if (piece->get_team() != player_turn) selected = nullptr;                
            }

            selected = clicked_instantiator(mouse_position);
        }
    }
    else if (selected)
    {
        PiecePtr piece = std::dynamic_pointer_cast<IPiece>(selected);
        
        if(PiecePtr)
        {
            if (board.drop_piece(selected))      
               player_turn = !player_turn;
        }

        std::shared_ptr<PieceInstantiator> instantiator = std::dynamic_pointer_cast<PieceInstantiator>(selected);
        
        if(instantiator)
        {
            if(instantiator)//here we have to check if mouse is inside board
                board.add_piece(instantiator->make_piece(/*TODO FILL HERE WITH COORDS*/)));
            
            Instantiator->return_to_origin();
        }
        
        selected = nullptr;
    }
}

void StateGameplay::render(sf::RenderWindow& window)
{
    board.render(window);
    if (selected) board.render_highlights(window, selected->get_valid_moves());
    board.render_pieces(window);
}

std::shared_ptr<PieceInstantiator> StateGameplay::clicked_instantiator(sf::Vector2i mouse_position)
{
    sf::Vector2f pos((float)(mouse_position.x), (float)(mouse_position.y));
    
    for (instantiator : instantiators)
    {
        if (instantiator->get_sprite().getGlobalBounds().contains(pos))
        {
            return instantiator;
        }
    }

    return nullptr;
}
