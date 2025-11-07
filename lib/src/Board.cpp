#include <Board.hpp>

#include <iostream>
Board::Board(sf::Texture texture) : IGameObject(texture)
{
    //empty
}

Board::Board(sf::Texture texture, std::vector<PiecePtr> _elements) : IGameObject(texture), elements(_elements)
{
    //empty
}

Board::Board(const Board& _board) : IGameObject(_board.sprite.getTexture()), elements(_board.elements)
{
    //empty
}

void Board::update(float dt)
{
    for (auto element : elements)
    {
        element->set_valid_moves(elements);
        element->update(dt);
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

void Board::render_highlights(sf::RenderWindow& window, const std::vector<Move>& valid_moves)
{
    sf::RectangleShape cell({(float)(Board::cell_lenght),(float)(Board::cell_lenght)});
    auto origin = this->sprite.getPosition();

    for (auto move : valid_moves)
    {
        cell.setFillColor( (move.occupant) ? sf::Color::Red : sf::Color::Cyan );
        auto pos = sf::Vector2<float>({(float)(move.relative_positiion.x * Board::cell_lenght), (float)(move.relative_positiion.y * Board::cell_lenght)});
        cell.setPosition(origin + pos);
        window.draw(cell);
    }

}

void Board::render_pieces(sf::RenderWindow& window)
{
    for (auto element : elements)
    {
        element->render(window);
    }
}

size_t Board::size()
{
    return elements.size();
}

PiecePtr Board::get_position(short x, short y)
{
    if ((x >= Board::side_lenght) || (y >= Board::side_lenght)) throw std::invalid_argument("Coordinate outside of board");

    for (auto element : elements)
    {
        auto position = element->get_position();
        if (position.x == x && position.y == y) return element;
    }
    
    return nullptr;
}

PiecePtr Board::clicked_piece(sf::Vector2i mouse_position)
{
    sf::Vector2f pos((float)(mouse_position.x), (float)(mouse_position.y));
    if (sprite.getGlobalBounds().contains(pos))
    {
        for (auto piece : elements)
        {
            if (piece->get_sprite().getGlobalBounds().contains(pos))
            {
                return piece;
            }
            
        }
    }

    return nullptr;
}

void Board::set_piece_sprite(PiecePtr piece)
{
    auto objetive_position = piece->get_position();
    auto board_position = sprite.getPosition();
    auto offset = sf::Vector2f({(float)(objetive_position.x * Board::cell_lenght), (float)(objetive_position.y * Board::cell_lenght)});
    piece->set_sprite_position(board_position + offset);
}

//Retorna si la pieza se movio en el tablero
bool Board::drop_piece(PiecePtr piece)
{
    bool it_moves = false;
    if (sprite.getGlobalBounds().contains(piece->get_sprite().getPosition()))
    {
        sf::Vector2f relative_position = piece->get_sprite().getPosition() - sprite.getPosition();
        Position position_on_board(relative_position.x / Board::cell_lenght, relative_position.y / Board::cell_lenght);
        auto valid_moves = piece->get_valid_moves();

        for (auto move : valid_moves)
        {
            if (move.relative_positiion == position_on_board)
            {
                if (move.occupant)
                {
                    if (move.occupant->hurt(piece))
                    {
                        it_moves = move.moves_piece;
                        auto it = std::find(elements.begin(), elements.end(), move.occupant);
                        if (it != elements.end())
                        {
                            elements.erase(it);
                        }
                    }
                }
                else it_moves = true;

                break;
            }
        }

        if (it_moves) piece->move(position_on_board);
    }

    set_piece_sprite(piece);

    return it_moves;
}

void Board::add_piece(PiecePtr piece)
{
    elements.push_back(piece);
    set_piece_sprite(piece);
}

