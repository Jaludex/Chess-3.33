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

//Ahora este metodo debe hacer el highlight de las casillas a las que se peude mover la pieza
PiecePtr Board::clicked_piece(sf::Vector2i mouse_position)
{
    if (sprite.getGlobalBounds().contains({mouse_position.x, mouse_position.y}))
    {
        for (auto piece : elements)
        {
            if (piece->get_sprite().getGlobalBounds().contains({mouse_position.x, mouse_position.y}))
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

//Este metodo debe eliminar el hightlight a posiciones validas, la logica de si el movimiento es valido o no se ha de manejar desde piece.move()
void Board::drop_piece(PiecePtr piece)
{
    if (sprite.getGlobalBounds().contains(piece->get_sprite().getPosition()))
    {
        sf::Vector2f relative_position = piece->get_sprite().getPosition() - sprite.getPosition();
        
        piece->move(Position(relative_position.x / Board::cell_lenght, relative_position.y / Board::cell_lenght));
        
    }

    set_piece_sprite(piece);
}

void Board::add_piece(PiecePtr piece)
{
    elements.push_back(piece);
    set_piece_sprite(piece);
}

