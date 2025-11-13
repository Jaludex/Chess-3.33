#include <IPiece.hpp>
#include <Board.hpp>
#include<list>
#include<functional>
#include <limits>
#include <algorithm>

//Linea momentanea en lo que cuadro con jesus los cambios que debe hacer push pa tener ese struct
using InBoardObject = Move;
using BoardL = std::list<std::shared_ptr<InBoardObject>>;
using GmnNodePtr = std::list<std::shared_ptr<GameNode>>;
struct GameNode
{
    BoardL board;
    InBoardObject dad;
    GmnNodePtr possible_plays;
    int result_minimax;
};
class GameTree
{
private:
    std::shared_ptr<GameNode> current_board;
    std::function<int(const BoardL&)> f_heuristica;

    int minimax(std::shared_ptr<GameNode> nodo, int deepness, int alpha, int beta, bool Maximizing);
    std::list<InBoardObject> generate_all_plays(const BoardL& current, bool bot_turn);
    BoardL apply_play(const BoardL& original, const InBoardObject& move);
public:
    GameTree(BoardL, std::function<int(const BoardL&)> heuristica);
    InBoardObject find_best_play(int deepness);
    
};