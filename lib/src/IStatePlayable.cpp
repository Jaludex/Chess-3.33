#include <IStatePlayable.hpp>

IStatePlayable::IStatePlayable(sf::RenderWindow* _window) : board(sf::Texture(sf::Vector2u((unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)))), player_turn(true), bot(BoardL(), GameEvaluator())
{
    window = _window;
    actual_phase = PhaseType::Preparing;
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
        if (actual_phase == PhaseType::Fighting) 
        {
            if (board.drop_piece(selected_piece, score))
            {
                this->end_turn();
            }
        }
        else if (actual_phase == PhaseType::Preparing)
        {
            returned_piece();
        }

        bot.set_current_board(board.get_elements());
        selected_piece = nullptr;
    }
    else if (selected_inst)
    {
        if(board.is_touching_mouse(mouse_position))
        {
            auto pos = board.get_square_by_coords(mouse_position);
            auto new_piece = selected_inst->make_piece(pos.x, pos.y);
            if ((new_piece->piece->get_team() && pos.y >= 4) || (!new_piece->piece->get_team() && pos.y <= 1))
            {
                if (!board.get_position(pos.x, pos.y))
                {
                    board.add_piece(new_piece);
                    dropped_inst();
                }
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

void IStatePlayable::end_turn()
{

    auto elements = board.get_elements();
    for (auto element : elements)
    {
        if (element->piece->get_piece_type() == PieceType::Pawn && ((element->piece->get_team() && element->pos.y == 0) || (!element->piece->get_team() && element->pos.y == 5)))
        {
            board.add_piece(std::make_shared<InBoardObject>(element->pos, std::make_shared<Queen>(element->piece->get_team()), element->king));
        }
    }

    bot.initial_game_eval();
    board.update_avaiable_moves();

    //std::cout << score << std::endl;

    //Aqui se implementa el arbitro mejoe
    auto possible_winner = check_winner();
    if (possible_winner != PlayerType::None)
    {
        this->end_fight(possible_winner);
    }

    possible_winner = check_stalemate();
    if (possible_winner != PlayerType::None)
    {
        this->end_fight(possible_winner);
    }

    player_turn = !player_turn;

    round++;
    // std::cout << round << std::endl;
}

PlayerType IStatePlayable::check_winner()
{
    auto elements = board.get_elements();
    BoardObjectPtr P1_King = nullptr;
    BoardObjectPtr P2_King = nullptr;

    for (auto element : elements)
    {
        if (element->king)
        {
            if (element->piece->get_team()) P1_King = element;
            else P2_King = element;
        }
    }

    if (!P1_King) return PlayerType::P2;
    if (!P2_King) return PlayerType::P1;
    return PlayerType::None;
}

//Retorna el player que aun se puede mover, en caso de que uno no pueda
PlayerType IStatePlayable::check_stalemate()
{
    auto elements = board.get_elements();

    // 1. Verificar si hay movimientos legales disponibles (Condición de derrota inmediata)
    if (bot.generate_all_plays(elements, true).empty()) return PlayerType::P2;
    if (bot.generate_all_plays(elements, false).empty()) return PlayerType::P1;

    // Variables de estado (O(1) espacio)
    bool p1_occupies_white = false;
    bool p1_occupies_black = false;
    bool p2_occupies_white = false;
    bool p2_occupies_black = false;

    bool p1_has_non_portal = false;
    bool p2_has_non_portal = false;

    bool has_freemove_piece = false;

    // 2. Iteración única sobre los elementos (O(n) tiempo)
    for (auto element : elements)
    {
        auto type = element->piece->get_piece_type();
        bool team = element->piece->get_team(); // true = P1, false = P2
        
        // A. Detección de piezas de movimiento libre
        // IMPORTANTE: El Peón (Pawn) NO debe estar en esta lista restringida.
        // Si es Peón, Torre, Reina, Rey -> Es movimiento libre.
        if (type != PieceType::Bishop && type != PieceType::Horse && type != PieceType::Trapper && type != PieceType::Portal) 
        {
            has_freemove_piece = true;
            // No hacemos 'break' aquí porque necesitamos seguir validando la condición de "Solo Portales"
        }

        // B. Verificación de "Solo Portales"
        if (type != PieceType::Portal)
        {
            if (team) p1_has_non_portal = true;
            else      p2_has_non_portal = true;
        }

        // C. Mapeo de ocupación de colores
        // No importa qué pieza sea, registramos en qué color está parada.
        int sum = element->pos.x + element->pos.y; 
        
        if (sum % 2 != 0) // Casilla Blanca
        {
            if (team) p1_occupies_white = true;
            else      p2_occupies_white = true;
        }
        else // Casilla Negra
        {
            if (team) p1_occupies_black = true;
            else      p2_occupies_black = true;
        }
    }

    // 3. Condiciones de Derrota por "Solo Portales"
    // Si un jugador tiene piezas pero NINGUNA es distinta a un portal, pierde.
    if (!p1_has_non_portal) return PlayerType::P2;
    if (!p2_has_non_portal) return PlayerType::P1;

    // 4. Análisis de Interacción (Stalemate)
    
    // CASO A: Hay una pieza libre (Peón, Torre, etc.)
    // Si existe un Peón, el juego SIEMPRE continúa, no importa dónde esté.
    if (has_freemove_piece) return PlayerType::None;

    // CASO B: Intersección de Colores
    // ¿Coinciden ambos jugadores en casillas blancas?
    bool meet_on_white = (p1_occupies_white && p2_occupies_white);
    
    // ¿Coinciden ambos jugadores en casillas negras?
    bool meet_on_black = (p1_occupies_black && p2_occupies_black);

    if (meet_on_white || meet_on_black)
    {
        return PlayerType::None; // Hay interacción posible, el juego continúa.
    }

    // CASO C: No hay interacción posible (Stalemate)
    // Ejemplo: P1 solo en negras, P2 solo en blancas.
    return PlayerType::P2; 
}

void IStatePlayable::start_fight()
{
    this->actual_phase = PhaseType::Fighting;
    instantiators.clear();
    board.update_avaiable_moves();
}