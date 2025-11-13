#include <Gametree.hpp>

GameTree::GameTree(BoardL beggining, std::function<int(const BoardL&)> f_juego)
{
    this->f_heuristica = f_juego;

    this->current_board = std::make_shared<GameNode>();
    this->current_board->board = beggining;
    //vacio
    //this->current_board->dad = InBoardObject();
    this->current_board->result_minimax = 0;
}
InBoardObject GameTree::find_best_play(int deepness)
{
    int best_value = -(std::numeric_limits<int>::max());
    InBoardObject best_play;
    int alpha = -(std::numeric_limits<int>::max());
    int beta = std::numeric_limits<int>::max();

    std::list<InBoardObject> possible_plays = this->generate_all_plays(current_board->board, true);

    for(const InBoardObject& play : possible_plays)
    {
        BoardL new_state = this->apply_play(current_board->board, play);

        auto play_node = std::make_shared<GameNode>();
        play_node->board = new_state;
        play_node->dad = play;

        current_board->possible_plays.push_front(play_node);

        int eval = this->minimax(play_node, deepness - 1, alpha, beta, false);

        if(eval > best_value)
        {
            best_value = eval;
            best_play = play;
        }
        alpha = std::max(alpha, eval);
    }
    return best_play;
}

int GameTree::minimax(std::shared_ptr<GameNode> node, int deepness, int alpha, int beta, bool Maximizing)
{
    if (deepness == 0 /*||esfindejuego(nodo->board)*/)
    {
        int score = this->f_heuristica(node->board);
        node->result_minimax = score;
        return score;
    }  
}