#pragma once

#include <IPiece.hpp>
#include <list>
#include <functional>
#include <limits>
#include <algorithm>
#include <memory>


using BoardObjectPtr = std::shared_ptr<InBoardObject>;
using BoardL = std::list<BoardObjectPtr>;


struct Jugada
{
    BoardObjectPtr moving_piece; 
    Position destino;             
    BoardObjectPtr captured_piece; 

    Jugada() : moving_piece(nullptr), destino(0, 0), captured_piece(nullptr) {}
};

struct GameNode
{
    BoardL board;
    Jugada dad; 
    std::list<std::shared_ptr<GameNode>> possible_plays;
    int result_minimax;
};

class GameTree
{
private:
    std::shared_ptr<GameNode> current_board;

    std::function<int(const BoardL&)> f_heuristica;

    int minimax(std::shared_ptr<GameNode> nodo, int deepness, int alpha, int beta, bool Maximizing);
    
    std::list<Jugada> generate_all_plays(const BoardL& current, bool bot_turn);
    
    BoardL apply_play(const BoardL& original, const Jugada& move);

public:
    GameTree(BoardL, std::function<int(const BoardL&)> heuristica);
    
    Jugada find_best_play(int deepness);
};