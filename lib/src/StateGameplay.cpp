#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow* _window) : IStatePlayable(_window)
{
    type = StateType::Gameplay;
    go_to = StateType::None;
}

StateGameplay::~StateGameplay() {}

void StateGameplay::init()
{
    //Aqui se intenta cargar una partida anterior que se haya guardado, sino se carga este cacho
    if (inventory.empty())
    {
        for (size_t i = 0; i < 5; i++)
        {
            inventory.push_front(PieceType::Pawn);
        }
    }
    difficulty = 1;
    round = 1;
    score = 0;
    board.add_piece(std::make_shared<InBoardObject>(Position(1, 1), std::make_shared<Queen>(false, SpriteManager::get_type_texture(PieceType::Queen, false))));
    
    
    if (!font.openFromFile("assets/fonts/arial.ttf")) 
    {
         std::cerr << "ERROR: No se pudo cargar fuente en Gameplay" << std::endl;
    }
    btn_back = new sf::Text(font, "<-", 30);
    btn_back->setFillColor(sf::Color::White);
    btn_back->setPosition(sf::Vector2f(20.f, 20.f));
    
    btn_back->setOutlineThickness(2);
    btn_back->setOutlineColor(sf::Color::Black);

    //Como es temporal, por ahora solo tomo todo esto y lo copio para el boton de empezar
    btn_start = new sf::Text(font, "->", 30);
    btn_start->setFillColor(sf::Color::White);
    btn_start->setPosition(static_cast<sf::Vector2f>(window->getSize()) - sf::Vector2f(100, 100));
    btn_start->setOutlineThickness(2);
    btn_start->setOutlineColor(sf::Color::Black);

    adjust_elements();

    bot.set_current_board(board.get_elements());
    bot.initial_game_eval();
}

void StateGameplay::terminate()
{
    //si usamos shared pointers entonces no necesitamos eliminar la pieza creada en init
}

void StateGameplay::update(float dt)
{
    if (actual_phase != PhaseType::Fighting || player_turn)
    {
        drag();
    }
    else
    {
        sf::sleep(sf::seconds(1.f));
        auto bot_play = bot.find_best_play(difficulty);

        if (bot_play.moving_piece)
        {
            Position old_position = bot_play.moving_piece->pos;

            board.move_piece(bot_play.moving_piece, bot_play.destination);
            board.set_piece_sprite(bot_play.moving_piece);

            board.update_bombs(bot_play.moving_piece, old_position);
            this->end_turn();
        }

        player_turn = true;
    }

    sf::Vector2i mousePos = get_relative_mouse_position();

    

    if (btn_back) 
    {
        if (is_mouse_over(*btn_back, mousePos)) btn_back->setFillColor(sf::Color::Yellow);
        else btn_back->setFillColor(sf::Color::White);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (btn_back && is_mouse_over(*btn_back, mousePos))
        {
            this->go_to = StateType::Return; 
            return;
        }
    }

    if (btn_start) 
    {
        if (is_mouse_over(*btn_start, mousePos)) btn_start->setFillColor(sf::Color::Yellow);
        else btn_start->setFillColor(sf::Color::White);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (btn_start && is_mouse_over(*btn_start, mousePos) && board.is_white_king_in_board())
        {
            this->start_fight();

            return;
        }
    }
    board.update(dt);
}


void StateGameplay::render(sf::RenderWindow& window)
{
    board.render(window);
    if (actual_phase == PhaseType::Fighting && selected_piece) board.render_move_highlights(window, selected_piece->piece->get_valid_moves());
    if (actual_phase == PhaseType::Preparing && selected_inst) board.render_instantiator_highlights(window, true);
    board.render_pieces(window);

    for (auto inst : instantiators)
    {
        inst->render(window);
    }

    if (btn_back) window.draw(*btn_back);
    if (btn_start && actual_phase == PhaseType::Preparing) window.draw(*btn_start);
}

void StateGameplay::on_resize() 
{
    adjust_elements();
}

void StateGameplay::adjust_elements()
{
    float halfboard_lenght = Board::side_lenght * Board::cell_lenght / 2;
    auto pos = sf::Vector2<float>((float)(window->getSize().x/2 - halfboard_lenght),
                                  (float)(window->getSize().y/2 - halfboard_lenght));
    board.set_sprite_position(pos);
    board.on_resize();

    if (btn_start) btn_start->setPosition(static_cast<sf::Vector2f>(window->getSize()) - sf::Vector2f(100, 100));

    this->load_instanciators();
}

void StateGameplay::dropped_inst()
{
    if (!selected_inst) return;

    inventory.erase(std::find(inventory.begin(), inventory.end(), selected_inst->get_type()));
    load_instanciators();
}

void StateGameplay::returned_piece()
{
    if (!selected_piece) return;

    inventory.push_front(selected_piece->piece->get_piece_type());
    board.remove_piece(selected_piece);
    
    load_instanciators();
}

void StateGameplay::end_fight(PlayerType winner)
{
    actual_phase = PhaseType::Preparing;

    if (winner == PlayerType::P1)
    {
        auto elements = board.get_elements();
        for (auto element : elements)
        {
            if (element->piece->get_team()) inventory.push_front(element->piece->get_piece_type());
        }
    }
    
    board.clear();
    round++;
    //Aqui le falta escojer un nuevo equipo enemigo (Si la ronda es multiplo de 3 cambia el lider), puede ser con algo como
    //prepare_enemy();
    //O algo asi
    //Tambien, si el calculo de (3^(dificultad+1)) / 2 es igual al numero de ronda actual, sumar 1 a la dificultad.
    //Asi la dificultad que ahora arranca en uno va a subir a un ritmo cada vez mas largo

    this->adjust_elements();
}

void StateGameplay::load_instanciators()
{
    if (actual_phase == PhaseType::Preparing)
    {
        int Ymultiplier = 0;

        bool even_piece = false;

        instantiators.clear();

        for (auto piecetype : inventory)
        {
            instantiators.push_back(std::make_shared<PieceInstantiator>(piecetype, true, sf::Vector2f(xmargin + ((even_piece) ? xoffset : 0), ymargin + (Ymultiplier*yoffset)), SpriteManager::get_type_texture(piecetype, true)));
            
            if (even_piece) Ymultiplier++;
            even_piece = !even_piece;
        }
    }
}