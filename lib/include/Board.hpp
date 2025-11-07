#pragma once

#include <SFML/Graphics.hpp>
#include <IPiece.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>


class Board : public IGameObject
{
private:
    //static const sf::Color black{70,50,50,255};
    //static const sf::Color white{220,200,200,255}; 
    std::vector<PiecePtr> elements;

public:

    static const uint8_t side_lenght = 6;
    static const int cell_lenght = 100;

    Board(sf::Texture texture);
    Board(sf::Texture texture, std::vector<PiecePtr> _elements);
    Board(const Board& _board);

    size_t size();
    PiecePtr get_position(short x, short y);
    void remove_by_position(short x, short y);
    PiecePtr clicked_piece(sf::Vector2i mouse_position);
    bool drop_piece(PiecePtr piece);
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void render_highlights(sf::RenderWindow& window, const std::vector<Move>& valid_moves); 
    void render_pieces(sf::RenderWindow& window);
    void add_piece(PiecePtr piece);
    void set_piece_sprite(PiecePtr piece);

};

