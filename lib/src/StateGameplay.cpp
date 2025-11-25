#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow* _window) : IStatePlayable(_window)
{
    type = StateType::Gameplay;
    go_to = StateType::None;
}

StateGameplay::~StateGameplay() {}

void StateGameplay::init()
{
    //Aqui se intenta cargar una partida anterior que se haya guardado, sino se carga esto
    if (inventory.empty())
    {
        for (size_t i = 0; i < 4; i++)
        {
            inventory.push_front(PieceType::Pawn);
        }
    }
    inventory.push_front(PieceType::Queen);
    
    adjust_elements();
    
    if (!font.openFromFile("assets/fonts/arial.ttf")) 
    {
         std::cerr << "ERROR: No se pudo cargar fuente en Gameplay" << std::endl;
    }
    btn_back = new sf::Text(font, "<-", 30);
    btn_back->setFillColor(sf::Color::White);
    btn_back->setPosition(sf::Vector2f(20.f, 20.f));
    
    btn_back->setOutlineThickness(2);
    btn_back->setOutlineColor(sf::Color::Black);

    bot.set_current_board(board.get_elements());
    bot.initial_game_eval();
}

void StateGameplay::terminate()
{
    //si usamos shared pointers entonces no necesitamos eliminar la pieza creada en init
}

void StateGameplay::update(float dt)
{
    if (player_turn)
    {
        drag();
    }
    else
    {
        sf::sleep(sf::seconds(1.f));
        auto bot_play = bot.find_best_play(4);

        if (bot_play.moving_piece)
        {
            Position old_position = bot_play.moving_piece->pos;

            board.move_piece(bot_play.moving_piece, bot_play.destination);
            board.set_piece_sprite(bot_play.moving_piece);

            board.update_bombs(bot_play.moving_piece, old_position);
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
    board.update(dt);
}


void StateGameplay::render(sf::RenderWindow& window)
{
    board.render(window);
    if (actual_phase == PhaseType::Fighting && selected_piece) board.render_highlights(window, selected_piece->piece->get_valid_moves());
    board.render_pieces(window);

    for (auto inst : instantiators)
    {
        inst->render(window);
    }

    if (btn_back) window.draw(*btn_back);
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

void StateGameplay::load_instanciators()
{
    //Aqui aparezco los instanciadores de piezas en tu inventario
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