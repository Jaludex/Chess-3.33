#include <StateGameplay.hpp>

StateGameplay::StateGameplay(sf::RenderWindow& _window) : board(sf::Texture ({(unsigned int)(Board::side_lenght * Board::cell_lenght),
                                                                              (unsigned int)(Board::side_lenght * Board::cell_lenght)})), player_turn(true), bot(BoardL(), GameEvaluator())
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

    float xmargin = Board::cell_lenght / 3;
    float ymargin = Board::cell_lenght / 3;
    float xoffset = Board::cell_lenght * 1.2f;
    float yoffset = Board::cell_lenght * 1.2f;
    float width = (float)window->getSize().x;
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Pawn, true, sf::Vector2f(xmargin, ymargin)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Horse, true, sf::Vector2f(xmargin, ymargin + yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Bishop, true, sf::Vector2f(xmargin, ymargin + 2*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Tower, true, sf::Vector2f(xmargin, ymargin + 3*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Queen, true, sf::Vector2f(xmargin, ymargin + 4*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Trapper, true, sf::Vector2f(xmargin + xoffset, ymargin + yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Crook, true, sf::Vector2f(xmargin + xoffset, ymargin + 2*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Archer, true, sf::Vector2f(xmargin + xoffset, ymargin + 3*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Portal, true, sf::Vector2f(xmargin + xoffset, ymargin + 4*yoffset)));

    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Pawn, false, sf::Vector2f(width - xmargin, ymargin)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Horse, false, sf::Vector2f(width - xmargin, ymargin + yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Bishop, false, sf::Vector2f(width - xmargin, ymargin + 2*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Tower, false, sf::Vector2f(width - xmargin, ymargin + 3*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Queen, false, sf::Vector2f(width - xmargin, ymargin + 4*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Trapper, false, sf::Vector2f(width - xmargin - xoffset, ymargin + yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Crook, false, sf::Vector2f(width - xmargin - xoffset, ymargin + 2*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Archer, false, sf::Vector2f(width - xmargin - xoffset, ymargin + 3*yoffset)));
    //instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Portal, false, sf::Vector2f(width - xmargin - xoffset, ymargin + 4*yoffset)));

    load_texture_piece("white_pawn", "bin/assets/WhitePawn.png");
    load_texture_piece("white_rook", "bin/assets/WhiteRook.png");
    load_texture_piece("white_bishop", "bin/assets/WhiteBishop.png");
    load_texture_piece("white_horse", "bin/assets/WhiteHorse.png");
    load_texture_piece("white_queen", "bin/assets/WhiteQueen.png");
    load_texture_piece("white_portal", "bin/assets/WhitePortal.png");
    load_texture_piece("white_crook", "bin/assets/WhiteCrook.png");
    load_texture_piece("white_archer", "bin/assets/WhiteArcher.png");
    load_texture_piece("white_trapper", "bin/assets/WhiteTrapper.png");
    load_texture_piece("white_trap", "bin/assets/WhiteTrap.png");
    board.add_piece(std::make_shared<InBoardObject>(Position(0,0), std::make_shared<Tower>(true,get_piece_texture("white_rook"))));
    load_texture_piece("black_pawn", "bin/assets/BlackPawn.png");
    load_texture_piece("black_rook", "bin/assets/BlackRook.png");
    load_texture_piece("black_bishop", "bin/assets/BlackBishop.png");
    load_texture_piece("black_horse", "bin/assets/BlackHorse.png");
    load_texture_piece("black_queen", "bin/assets/BlackQueen.png");
    load_texture_piece("black_portal", "bin/assets/BlackPortal.png");
    load_texture_piece("black_crook", "bin/assets/BlackCrook.png");
    load_texture_piece("black_archer", "bin/assets/BlackArcher.png");
    load_texture_piece("black_trapper","bin/assets/BlackTrapper.png");
    load_texture_piece("black_trap", "bin/assets/BlackTrap.png");

    bot.set_current_board(board.get_elements());
    bot.initial_game_eval();
}

void StateGameplay::load_texture_piece(std::string type, std::string file)
{
    sf::Texture texture;
    if (!texture.loadFromFile(file))
    {
        throw(std::runtime_error("Texture not found: " + file));
    }
        texture_map[type] = texture;
}
const sf::Texture& StateGameplay::get_piece_texture(std::string type)
{
    return texture_map.at(type);
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
        auto bot_play = bot.find_best_play(2);

        Position old_position = bot_play.moving_piece->pos;

        board.move_piece(bot_play.moving_piece, bot_play.destination);
        board.set_piece_sprite(bot_play.moving_piece);

        board.update_bombs(bot_play.moving_piece, old_position);

        player_turn = true;
    }
    
    
    
    board.update(dt);
}

sf::Vector2i StateGameplay::get_relative_mouse_position()
{
    return sf::Mouse::getPosition(*window);
}

bool check_winner()
{

}

void StateGameplay::drag()
{
    auto mouse_position = get_relative_mouse_position();
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {        
        if (selected_piece)
        {   
            selected_piece->piece->set_sprite_position({(float)mouse_position.x, (float)mouse_position.y});
            selected_inst = nullptr;
        }
        else if (selected_inst)
        {
            selected_inst->set_sprite_position({(float)mouse_position.x, (float)mouse_position.y});
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
            board.add_piece(selected_inst->make_piece(pos.x, pos.y));
        }
        
        selected_inst->return_to_origin();
        selected_inst = nullptr;
    }
}

void StateGameplay::render(sf::RenderWindow& window)
{
    board.render(window);
    if (selected_piece) board.render_highlights(window, selected_piece->piece->get_valid_moves());
    board.render_pieces(window);

    for (auto inst : instantiators)
    {
        inst->render(window);
    }
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
