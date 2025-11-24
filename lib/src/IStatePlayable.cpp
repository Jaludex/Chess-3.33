#include <IStatePlayable.hpp>

IStatePlayable::IStatePlayable(sf::RenderWindow* _window) : board(sf::Texture(sf::Vector2u((unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)))), player_turn(true), bot(BoardL(), GameEvaluator())
{
    window = _window;
}

IStatePlayable::~IStatePlayable() { }

void IStatePlayable::drag()
{
    auto mouse_position = this->get_relative_mouse_position();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {        
        if (selected_piece)
        {   
            selected_piece->piece->set_sprite_position({(float)mouse_position.x - fix_offset(selected_piece->piece->get_sprite(), 'x'), (float)mouse_position.y - fix_offset(selected_piece->piece->get_sprite(),'y')});
            selected_inst = nullptr;
        }
        else if (selected_inst)
        {
            selected_inst->set_sprite_position({(float)mouse_position.x - fix_offset(selected_inst->get_sprite(), 'x'), (float)mouse_position.y - fix_offset(selected_inst->get_sprite(), 'y')});
            selected_piece = nullptr;
        }
        else
        {
            selected_piece = board.clicked_piece(mouse_position);

            if (selected_piece)
            {
                if (selected_piece->piece && selected_piece->piece->get_team() != player_turn) selected_piece = nullptr;                
            }
            else
            {
                selected_inst = clicked_instantiator(mouse_position);
            }
        }
    }
    else if (selected_piece)
    {   
        if (board.drop_piece(selected_piece)) 
        {
            player_turn = !player_turn;
            bot.set_current_board(board.get_elements());
            bot.initial_game_eval();
        }

        selected_piece = nullptr;
    }
    else if (selected_inst)
    {
        if(board.is_touching_mouse(mouse_position))
        {
            auto pos = board.get_square_by_coords(mouse_position);
            if (!board.get_position(pos.x, pos.y))
            {
                board.add_piece(selected_inst->make_piece(pos.x, pos.y));
            }
            else
            {
                //Reproducir sonido de error tal vez, notificar que no es valido instanciar asi
            }
                
        }
        
        selected_inst->return_to_origin();
        selected_inst = nullptr;
    }
}

float IStatePlayable::fix_offset(const sf::Sprite& _sprite, char t)
{
    sf::FloatRect boundaries = _sprite.getGlobalBounds();
    if(t == 'x') return boundaries.size.x / 2.0;

    else return boundaries.size.y / 2.0;
}

PieceInstantPtr IStatePlayable::clicked_instantiator(sf::Vector2i mouse_position)
{
    sf::Vector2f pos = static_cast<sf::Vector2f>(mouse_position);
    
    for (auto instantiator : instantiators)
    {
        if (instantiator->get_sprite().getGlobalBounds().contains(pos))
        {
            return instantiator;
        }
    }

    return nullptr;
}