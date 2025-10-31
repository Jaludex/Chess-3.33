#pragma once

#include <IPiece.hpp>

#include <vector>
#include <memory>
#include <stdexcept>


class Board : public IGameObject
{
private:

    std::vector<PiecePtr> elements;

public:

    static const uint8_t side_lenght = 6;

    Board(sf::Texture texture);
    Board(sf::Texture texture, std::vector<PiecePtr> _elements);
    Board(const Board& _board);

    size_t size();
    PiecePtr get_position(short x, short y);
    void update(float dt) override;
    void render(sf::RenderWindow window) override;
};

