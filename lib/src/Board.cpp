#include <Board.hpp>

Board::Board(sf::Texture texture) : IGameObject(texture)
{
    sprite.setScale(sf::Vector2f(1.0,1.0));
}

Board::Board(sf::Texture texture, std::list<BoardObjectPtr> _elements) : IGameObject(texture), elements(_elements)
{
    sprite.setScale(sf::Vector2f(1.0,1.0));
}

Board::Board(const Board& _board) : IGameObject(_board.sprite.getTexture()), elements(_board.elements)
{
    sprite.setScale(sf::Vector2f(1.0,1.0));
}

void Board::update(float dt)
{
    for (auto element : elements)
    {
        element->piece->set_valid_moves(elements, element->pos);
        element->piece->update(dt);
    }
}

void Board::render(sf::RenderWindow& window)
{
    sf::RectangleShape cell({(float)(Board::cell_lenght),(float)(Board::cell_lenght)});
    auto origin = this->sprite.getPosition();
    
    for(int i = 0; i < Board::side_lenght * Board::side_lenght; i++)
    {
        cell.setFillColor( ((i + i/Board::side_lenght) % 2 == 0) ? sf::Color::White : sf::Color::Black);        
        auto pos = sf::Vector2<float>({(float)(i % Board::side_lenght * Board::cell_lenght),(float)(i / Board::side_lenght * Board::cell_lenght)});
        cell.setPosition(origin + pos);
        window.draw(cell);
    }
}

void Board::render_highlights(sf::RenderWindow& window, const std::vector<BoardObjectPtr>& valid_moves)
{
    sf::RectangleShape cell({(float)(Board::cell_lenght),(float)(Board::cell_lenght)});
    auto origin = this->sprite.getPosition();

    for (auto move : valid_moves)
    {
        cell.setFillColor( (move->piece) ? sf::Color::Red : sf::Color::Cyan );
        auto pos = sf::Vector2<float>({(float)(move->pos.x * Board::cell_lenght), (float)(move->pos.y * Board::cell_lenght)});
        cell.setPosition(origin + pos);
        window.draw(cell);
    }

}

void Board::render_pieces(sf::RenderWindow& window)
{
    for (auto element : elements)
    {
        element->piece->render(window);
    }
}

size_t Board::size()
{
    return elements.size();
}

BoardL Board::get_elements()
{
    return elements;
}

BoardObjectPtr Board::get_position(short x, short y)
{
    if ((x >= Board::side_lenght) || (y >= Board::side_lenght)) throw std::invalid_argument("Coordinate outside of board");

    for (auto element : elements)
    {
        if (element->pos.x == x && element->pos.y == y) return element;
    }
    
    return nullptr;
}

BoardObjectPtr Board::clicked_piece(sf::Vector2i mouse_position)
{
    if (this->is_touching_mouse(mouse_position))
    {
        for (auto element : elements)
        {
            if (element->piece->is_touching_mouse(mouse_position))
            {
                return element;
            }   
        }
    }

    return nullptr;
}

void Board::set_piece_sprite(BoardObjectPtr element)
{
    auto objetive_position = element->pos;
    auto board_position = sprite.getPosition();
    auto offset = sf::Vector2f({(float)(objetive_position.x * Board::cell_lenght), (float)(objetive_position.y * Board::cell_lenght)});
    element->piece->set_sprite_position(board_position + offset);
}

Position Board::get_square_by_coords(sf::Vector2i mouse_position)
{
    sf::Vector2f relative_position = static_cast<sf::Vector2f>(mouse_position) - sprite.getPosition();
    return Position(relative_position.x / Board::cell_lenght, relative_position.y / Board::cell_lenght);
}

//Retorna si la pieza se movio en el tablero
bool Board::drop_piece(BoardObjectPtr element)
{
    bool it_moves = false;
    auto old_pos = element->pos;
    if (sprite.getGlobalBounds().contains(element->piece->get_sprite().getPosition()))
    {
        Position position_on_board = get_square_by_coords(static_cast<sf::Vector2i>(element->piece->get_sprite().getPosition()));
        it_moves = this->move_piece(element, position_on_board);
    }

    if (it_moves) update_bombs(element, old_pos);
    
    set_piece_sprite(element);
    return it_moves;
}

void Board::add_piece(BoardObjectPtr piece)
{
    elements.push_front(piece);
    set_piece_sprite(piece);
}

bool Board::move_piece(BoardObjectPtr element, Position destination)
{
    bool it_moves = false;
    auto valid_moves = element->piece->get_valid_moves();
    for (auto move : valid_moves)
    {
        if (move->pos == destination)
        {
            it_moves = true;
            if (move->piece)
            {
                if (element->piece->get_piece_type() == PieceType::Portal && element->piece->get_team() == move->piece->get_team())
                {                    
                    move->pos = element->pos;
                    set_piece_sprite(move);
                }
                else if (move->piece->hurt(element->piece))
                {
                    auto it = std::find(elements.begin(), elements.end(), (move->piece->get_piece_type() == PieceType::Bomb) ? element : move);
                    if (it != elements.end())
                    {
                        elements.erase(it);
                    }
                }
            }
            element->pos = destination;
            break;
        }
    }

    return it_moves;
}

void Board::update_bombs(BoardObjectPtr moved_piece, Position old_position)
{
    if (moved_piece->piece->get_piece_type() == PieceType::Trapper)
        {
            add_piece(std::make_shared<InBoardObject>(old_position, std::make_shared<Bomb>(moved_piece->piece->get_team(), (moved_piece->piece->get_team()) ? SpriteManager::get_piece_texture("white_trap") : SpriteManager::get_piece_texture("black_trap"))));
        }
        
        bool team_of_bombs_to_remove = !moved_piece->piece->get_team(); 
        elements.erase(std::remove_if(elements.begin(), elements.end(),
            [team_of_bombs_to_remove](BoardObjectPtr element) {
                return element->piece->get_piece_type() == PieceType::Bomb && element->piece->get_team() == team_of_bombs_to_remove;}), elements.end());
}

void Board::on_resize()
{
    for (auto piece : elements)
    {
        set_piece_sprite(piece);
    }
}

