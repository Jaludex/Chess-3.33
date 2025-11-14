#pragma once

#include <GameEvaluator.hpp>
#include <Board.hpp>
#include <list>
#include <functional>
#include <limits>
#include <algorithm>
#include <memory>
#include "Gametree.hpp"
#include "Board.hpp" 
#include "Trapper.hpp"
#include <map>


struct Play
{
    BoardObjectPtr moving_piece; 
    Position destino;             
    BoardObjectPtr captured_piece; 

    Play() : moving_piece(nullptr), destino(0, 0), captured_piece(nullptr) {}
};

struct GameNode
{
    BoardL board;
    Play dad; 
    std::list<std::shared_ptr<GameNode>> possible_plays;
    int result_minimax;
};

class GameTree
{
private:
    std::shared_ptr<GameNode> current_board;
    
    GameEvaluator heuristica;

    int minimax(std::shared_ptr<GameNode> nodo, int deepness, int alpha, int beta, bool Maximizing);
    
    std::list<Play> generate_all_plays(const BoardL& current, bool bot_turn);
    
    BoardL apply_play(const BoardL& original, const Play& move);

public:
    GameTree(BoardL beggining, GameEvaluator heuristica);
    
    Play find_best_play(int deepness);
};
