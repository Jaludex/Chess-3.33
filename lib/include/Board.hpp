#pragma once

#include <SFML/Graphics.hpp>
#include <IPiece.hpp>
#include <algorithm>
#include <stdexcept>
#include "Trapper.hpp"

class Board : public IGameObject
{
private:
    //static const sf::Color black{70,50,50,255};
    //static const sf::Color white{220,200,200,255}; 
    std::list<BoardObjectPtr> elements;

public:

    static const uint8_t side_lenght = 6;
    static const u_int cell_lenght = 100;

    Board(sf::Texture texture);
    Board(sf::Texture texture, std::list<BoardObjectPtr> _elements);
    Board(const Board& _board);

    size_t size();
    BoardObjectPtr get_position(short x, short y);
    void remove_by_position(short x, short y);
    BoardObjectPtr clicked_piece(sf::Vector2i mouse_position);
    Position get_square_by_coords(sf::Vector2i mouse_position);
    bool drop_piece(BoardObjectPtr element);
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void render_highlights(sf::RenderWindow& window, const std::vector<BoardObjectPtr>& valid_moves); 
    void render_pieces(sf::RenderWindow& window);
    void add_piece(BoardObjectPtr piece);
    void set_piece_sprite(BoardObjectPtr element);

};

