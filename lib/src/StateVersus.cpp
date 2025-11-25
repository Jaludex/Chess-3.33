#include <StateVersus.hpp>

StateVersus::StateVersus(sf::RenderWindow* _window) : IStatePlayable(_window)
{
    type = StateType::Versus;
    go_to = StateType::None;
}

StateVersus::~StateVersus() {}

void StateVersus::init()
{
    this->on_resize();
    
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

void StateVersus::terminate()
{
    //si usamos shared pointers entonces no necesitamos eliminar la pieza creada en init
}

void StateVersus::update(float dt)
{
    drag();
    
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


void StateVersus::render(sf::RenderWindow& window)
{
    board.render(window);
    if (selected_piece) board.render_move_highlights(window, selected_piece->piece->get_valid_moves());
    if (selected_inst) board.render_instantiator_highlights(window, selected_inst->get_team());
    board.render_pieces(window);

    for (auto inst : instantiators)
    {
        inst->render(window);
    }

    if (btn_back) window.draw(*btn_back);
}

void StateVersus::on_resize() 
{
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

void StateVersus::adjust_elements()
{

}

void StateVersus::dropped_inst()
{
    //empty
}

void StateVersus::returned_piece()
{

}
