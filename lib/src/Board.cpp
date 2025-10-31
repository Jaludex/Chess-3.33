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

void update(float dt)
{
    for (auto e : elements)
    {
        e.update(dt)
    }
}

void render(sf::RenderWindow window)
{
    for (auto e : elements)
    {
        e.update(dt)
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


