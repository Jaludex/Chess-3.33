#include <Board.hpp>

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
    for (auto e : elements)
    {
        e.update(dt);
    }
}

void Board::render(sf::RenderWindow& window)
{
    sf::RectangleShape cell({(float)(Board::cell_lenght),(float)(Board::cell_lenght)});
    auto origin = this->sprite.getPosition();
    
    for(int i = 0; i < Board::side_lenght * Board::side_lenght; i++)
    {
        cell.setFillColor( (i % 2 == 0) ? Board::white : Board::black);
        cell.setPosition({(float)(i % Board::side_lenght * Board::Cell_Lenght),(float)(i / Board::side_lenght * Board::Cell_Lenght)});
        window.draw(cell);
    }

    for (auto e : elements)
    {
        e.render(window);
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

void Board::add_piece(PiecePtr piece)
{
    elements.push_back(piece);
}

