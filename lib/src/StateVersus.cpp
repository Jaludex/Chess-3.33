#include <StateVersus.hpp>

StateVersus::StateVersus(sf::RenderWindow* _window) : IStatePlayable(_window)
{
    type = StateType::Gameplay;
    go_to = StateType::None;
}

StateVersus::~StateVersus() {}

void StateVersus::init()
{    
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


void StateVersus::render(sf::RenderWindow& window)
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

void StateVersus::on_resize() 
{
    adjust_elements();
}

void StateVersus::adjust_elements()
{
    float halfboard_lenght = Board::side_lenght * Board::cell_lenght / 2;
    auto pos = sf::Vector2<float>((float)(window->getSize().x/2 - halfboard_lenght),
                                  (float)(window->getSize().y/2 - halfboard_lenght));
    board.set_sprite_position(pos);
    board.on_resize();

    if (btn_start) btn_start->setPosition(static_cast<sf::Vector2f>(window->getSize()) - sf::Vector2f(100, 100));

    this->load_instanciators();
}

void StateVersus::dropped_inst()
{
    if (!selected_inst) return;

    load_instanciators();
}

void StateVersus::returned_piece()
{
    if (!selected_piece) return;

    board.remove_piece(selected_piece);
    
    load_instanciators();
}

void StateVersus::end_fight(PlayerType winner)
{
    actual_phase = PhaseType::Preparing;
    
    board.clear();
    round++;

    this->adjust_elements();
}

void StateVersus::load_instanciators()
{
    float width = (float)window->getSize().x;

    instantiators.clear();

    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Pawn, true, sf::Vector2f(xmargin, ymargin)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Horse, true, sf::Vector2f(xmargin, ymargin + yoffset)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Bishop, true, sf::Vector2f(xmargin, ymargin + 2*yoffset)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Tower, true, sf::Vector2f(xmargin, ymargin + 3*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Queen, true, sf::Vector2f(xmargin, ymargin + 4*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Trapper, true, sf::Vector2f(xmargin + xoffset, ymargin + yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Crook, true, sf::Vector2f(xmargin + xoffset, ymargin + 2*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Archer, true, sf::Vector2f(xmargin + xoffset, ymargin + 3*yoffset)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Portal, true, sf::Vector2f(xmargin + xoffset, ymargin + 4*yoffset)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Pawn, false, sf::Vector2f(width - (xmargin + 100), ymargin)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Horse, false, sf::Vector2f(width - (xmargin + 100), ymargin + yoffset)));
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Bishop, false, sf::Vector2f(width - (xmargin + 100), ymargin + 2*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Tower, false, sf::Vector2f(width - (xmargin + 100), ymargin + 3*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Queen, false, sf::Vector2f(width - (xmargin + 100), ymargin + 4*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Trapper, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Crook, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + 2*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Archer, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + 3*yoffset))); 
    instantiators.push_back(std::make_shared<PieceInstantiator>(PieceType::Portal, false, sf::Vector2f(width - (xmargin + 100) - xoffset, ymargin + 4*yoffset))); 
}