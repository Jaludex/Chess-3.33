#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow* _window) :btn_back_sprite(tex_exit), board(sf::Texture(sf::Vector2u((unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)))), player_turn(true), bot(BoardL(), GameEvaluator()),background_sprite(background_texture), 
                                                                              IStatePlayable(_window)
{
    type = StateType::Gameplay;
    go_to = StateType::None;
}

StateGameplay::~StateGameplay() {}

void StateGameplay::init()
{
    srand(time(0));
    
        if(!background_texture.loadFromFile("assets/game_background.png"))
    {
        std::cerr << "ERROR: No se pudo cargar fondo en Gameplay" << std::endl;
    }
    auto size = background_texture.getSize();
    background_sprite.setTexture(background_texture);
    background_sprite.setTextureRect({{0, 0}, {static_cast<int>(size.x), static_cast<int>(size.y)}});

    if (!tex_exit.loadFromFile("assets/back_button.png")) // Usa la ruta de tu imagen de botón
    {
        std::cerr << "Error cargando textura de boton de regreso en Gameplay" << std::endl;
    }
    tex_exit.setSmooth(true);
    btn_back_sprite.setTexture(tex_exit, true);
    this->set_up_black_team();

    //board.add_piece(std::make_shared<InBoardObject>(Position(3, 5), std::make_shared<Queen>(true, SpriteManager::get_piece_texture("white_queen"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(1, 4), std::make_shared<Archer>(true, SpriteManager::get_piece_texture("white_archer"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(5, 5), std::make_shared<Crook>(true, SpriteManager::get_piece_texture("white_crook"))));
    //
    //board.add_piece(std::make_shared<InBoardObject>(Position(0, 1), std::make_shared<Horse>(false, SpriteManager::get_piece_texture("black_horse"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(2, 1), std::make_shared<Queen>(false, SpriteManager::get_piece_texture("black_queen"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(1, 1), std::make_shared<Archer>(false, SpriteManager::get_piece_texture("black_archer"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(1, 0), std::make_shared<Portal>(false, SpriteManager::get_piece_texture("black_portal"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(5, 1), std::make_shared<Trapper>(false, SpriteManager::get_piece_texture("black_trapper"))));

    //Aqui se intenta cargar una partida anterior que se haya guardado, sino se carga este cacho
    if (inventory.empty())
    {
        for (size_t i = 0; i < 5; i++)
        {
            inventory.push_front(PieceType::Pawn);
        }
        inventory.push_front(PieceType::Bishop);
    }
    difficulty = 2;
    round = 1;
    score = 0;
    board.add_piece(std::make_shared<InBoardObject>(Position(1, 1), std::make_shared<Bishop>(false)));
    
    
    if (!font.openFromFile("assets/fonts/arial.ttf")) 
    {
         std::cerr << "ERROR: No se pudo cargar fuente en Gameplay" << std::endl;
    }
  
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
    //empty
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
            Position old_position(bot_play.moving_piece->pos);

            board.move_piece(bot_play.moving_piece, bot_play.destination);
            board.set_piece_sprite(bot_play.moving_piece);

            board.update_bombs(bot_play.moving_piece, old_position);
            this->end_turn();
        }

        player_turn = true;
    }
    sf::Vector2i mouse_pos = get_relative_mouse_position();

    if (is_mouse_over(btn_back_sprite, mouse_pos)) btn_back_sprite.setColor(sf::Color(200, 200, 200));
    else btn_back_sprite.setColor(sf::Color::White);

    if (is_mouse_over(btn_back_sprite, mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        this->go_to = StateType::MainMenu;
        return;
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
    window.draw(background_sprite);
    board.render(window);
    if (actual_phase == PhaseType::Fighting && selected_piece) board.render_move_highlights(window, selected_piece->piece->get_valid_moves());
    if (actual_phase == PhaseType::Preparing && selected_inst) board.render_instantiator_highlights(window, true);
    board.render_pieces(window);

    for (auto inst : instantiators)
    {
        inst->render(window);
    }

    window.draw(btn_back_sprite);
    if (btn_start && actual_phase == PhaseType::Preparing) window.draw(*btn_start);
}

void StateGameplay::on_resize() 
{
    adjust_elements();
}

void StateGameplay::adjust_elements()
{
    sf::Vector2u win_size = window->getSize();
    sf::Vector2u original_size = background_texture.getSize();
    float scale_x = (float)win_size.x / original_size.x;
    float scale_y = (float)win_size.y / original_size.y;

    background_sprite.setScale(sf::Vector2f(scale_x, scale_y));
    background_sprite.setOrigin(sf::Vector2f(0.0f, 0.0f)); 
    background_sprite.setPosition(sf::Vector2f(0.0f, 0.0f));

    float halfboard_lenght = Board::side_lenght * Board::cell_lenght / 2;
    auto pos = sf::Vector2<float>((float)(window->getSize().x/2 - halfboard_lenght),
                                  (float)(window->getSize().y/2 - halfboard_lenght));
    board.set_sprite_position(pos);


    sf::Vector2u winSizeU = window->getSize();
    sf::Vector2f winSize((float)winSizeU.x, (float)winSizeU.y);

    float target_btn_height = winSize.y * 0.08f;
    
    sf::Vector2u btn_texture_size = tex_exit.getSize();
    if (btn_texture_size.y > 0) 
    {
        float scale = target_btn_height / btn_texture_size.y;
        btn_back_sprite.setScale(sf::Vector2f(scale, scale));
    }

    float margin = 20.0f;
    sf::FloatRect bounds = btn_back_sprite.getLocalBounds(); 
    btn_back_sprite.setOrigin(sf::Vector2f(bounds.size.x / 2.0f, bounds.size.y / 2.0f));
    
    float pos_x = margin + bounds.size.x * btn_back_sprite.getScale().x / 2.0f;
    float pos_y = margin + bounds.size.y * btn_back_sprite.getScale().y / 2.0f;

    btn_back_sprite.setPosition(sf::Vector2f(pos_x, pos_y));
  
    this->load_instantiators();
    
}

bool StateGameplay::set_up_black_team()
{
    int type = rand() % 9;

    FileManager presets("kingpresets.json");
    
    std::string _s;
    if(!presets.read_line(_s))
        return false;
    json index_values = json::parse(_s);

    std::string piece_name;
    switch(type)
    {
        case (int)PieceType::Pawn: piece_name = "Pawn"; break;
        case (int)PieceType::Horse: piece_name = "Horse"; break;
        case (int)PieceType::Bishop: piece_name = "Bishop"; break;
        case (int)PieceType::Tower: piece_name = "Rook"; break;
        case (int)PieceType::Queen: piece_name = "Queen"; break;
        case (int)PieceType::Trapper: piece_name = "Trapper"; break;
        case (int)PieceType::Crook: piece_name = "Crook"; break;
        case (int)PieceType::Archer: piece_name = "Archer"; break;
        case (int)PieceType::Portal: piece_name = "Portal"; break;
    }

    int chosen_preset_index = (int)index_values.at(piece_name + "Start") + (rand() % (int)index_values.at(piece_name + "Amount"));
    
    std::string piece_array_string;
    if(!presets.goto_line(chosen_preset_index) || !presets.read_line(piece_array_string))
        return false;

    json pieces = json::parse(piece_array_string);

    for (auto p : pieces)
    {
        auto type = p.at("piece");
        int column = p.at("x");
        int row = p.at("y");

        board.add_piece(make_board_object(type, false, column, row));
    }

    return true;
}
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
            instantiators.push_back(std::make_shared<PieceInstantiator>(piecetype, true, sf::Vector2f(xmargin + ((even_piece) ? xoffset : 0), ymargin + (Ymultiplier*yoffset))));
            
            if (even_piece) Ymultiplier++;
            even_piece = !even_piece;
        }
    }
}
