#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow* _window) :btn_back_sprite(tex_exit), board(sf::Texture(sf::Vector2u((unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)))), player_turn(true), bot(BoardL(), GameEvaluator()),background_sprite(background_texture)
{
    window = _window;
    type = StateType::Gameplay;
    go_to = StateType::None;
}
StateGameplay::~StateGameplay() {}

void StateGameplay::init()
{
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
    this->on_resize();

    //board.add_piece(std::make_shared<InBoardObject>(Position(3, 5), std::make_shared<Queen>(true, SpriteManager::get_piece_texture("white_queen"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(1, 4), std::make_shared<Archer>(true, SpriteManager::get_piece_texture("white_archer"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(5, 5), std::make_shared<Crook>(true, SpriteManager::get_piece_texture("white_crook"))));
    //
    //board.add_piece(std::make_shared<InBoardObject>(Position(0, 1), std::make_shared<Horse>(false, SpriteManager::get_piece_texture("black_horse"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(2, 1), std::make_shared<Queen>(false, SpriteManager::get_piece_texture("black_queen"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(1, 1), std::make_shared<Archer>(false, SpriteManager::get_piece_texture("black_archer"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(1, 0), std::make_shared<Portal>(false, SpriteManager::get_piece_texture("black_portal"))));
    //board.add_piece(std::make_shared<InBoardObject>(Position(5, 1), std::make_shared<Trapper>(false, SpriteManager::get_piece_texture("black_trapper"))));


    bot.set_current_board(board.get_elements());
    bot.initial_game_eval();
}

void StateGameplay::terminate()
{
    //empty
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
    sf::Vector2i mouse_pos = get_relative_mouse_position();

    if (is_mouse_over(btn_back_sprite, mouse_pos)) btn_back_sprite.setColor(sf::Color(200, 200, 200));
    else btn_back_sprite.setColor(sf::Color::White);

    if (is_mouse_over(btn_back_sprite, mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        this->go_to = StateType::MainMenu;
        return;
    }
    board.update(dt);
}
float fix_offset(const sf::Sprite& _sprite, char t)
{
    sf::FloatRect boundaries = _sprite.getGlobalBounds();
    if(t == 'x') return boundaries.size.x / 2.0;

    else return boundaries.size.y / 2.0;
}
void StateGameplay::drag()
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

void StateGameplay::render(sf::RenderWindow& window)
{
    window.draw(background_sprite);
    board.render(window);
    if (selected_piece) board.render_highlights(window, selected_piece->piece->get_valid_moves());
    board.render_pieces(window);

    for (auto inst : instantiators)
    {
        inst->render(window);
    }

    window.draw(btn_back_sprite);
}

PieceInstantPtr StateGameplay::clicked_instantiator(sf::Vector2i mouse_position)
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

void StateGameplay::on_resize() 
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
    board.on_resize();

    float xmargin = Board::cell_lenght / 3;
    float ymargin = Board::cell_lenght / 3;
    float xoffset = Board::cell_lenght * 1.2f;
    float yoffset = Board::cell_lenght * 1.2f;
    float width = (float)window->getSize().x;


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

    //Esto deberia cambiarse cuando solo aparezcan los instanciadores de las piezas que tienes, pero por ahora resuelve
    instantiators.clear();

    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Pawn, true, sf::Vector2f(xmargin, ymargin), SpriteManager::get_piece_texture("white_pawn")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Horse, true, sf::Vector2f(xmargin, ymargin + yoffset), SpriteManager::get_piece_texture("white_horse")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Bishop, true, sf::Vector2f(xmargin, ymargin + 2*yoffset), SpriteManager::get_piece_texture("white_bishop")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Tower, true, sf::Vector2f(xmargin, ymargin + 3*yoffset), SpriteManager::get_piece_texture("white_rook"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Queen, true, sf::Vector2f(xmargin, ymargin + 4*yoffset), SpriteManager::get_piece_texture("white_queen"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Trapper, true, sf::Vector2f(xmargin + xoffset, ymargin + yoffset), SpriteManager::get_piece_texture("white_trapper"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Crook, true, sf::Vector2f(xmargin + xoffset, ymargin + 2*yoffset), SpriteManager::get_piece_texture("white_crook"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Archer, true, sf::Vector2f(xmargin + xoffset, ymargin + 3*yoffset), SpriteManager::get_piece_texture("white_archer")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Portal, true, sf::Vector2f(xmargin + xoffset, ymargin + 4*yoffset), SpriteManager::get_piece_texture("white_portal")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Pawn, false, sf::Vector2f(width - (xmargin + 100), ymargin), SpriteManager::get_piece_texture("black_pawn")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Horse, false, sf::Vector2f(width - (xmargin + 100), ymargin + yoffset), SpriteManager::get_piece_texture("black_horse")));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Bishop, false, sf::Vector2f(width - (xmargin + 100), ymargin + 2*yoffset), SpriteManager::get_piece_texture("black_bishop"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Tower, false, sf::Vector2f(width - (xmargin + 100), ymargin + 3*yoffset), SpriteManager::get_piece_texture("black_rook"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Queen, false, sf::Vector2f(width - (xmargin + 100), ymargin + 4*yoffset), SpriteManager::get_piece_texture("black_queen"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Trapper, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + yoffset), SpriteManager::get_piece_texture("black_trapper"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Crook, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + 2*yoffset), SpriteManager::get_piece_texture("black_crook"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Archer, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + 3*yoffset), SpriteManager::get_piece_texture("black_archer"))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Portal, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + 4*yoffset), SpriteManager::get_piece_texture("black_portal"))); 
}
