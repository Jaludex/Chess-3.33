#include <Gametree.hpp>

GameTree::GameTree(BoardL initial_board, GameEvaluator _heuristic)
{
    this->heuristic = _heuristic;
    this->current_board = std::make_shared<GameNode>();
    this->current_board->board = initial_board;
    this->current_board->dad = Play();
    this->current_board->result_minimax = 0;
}

Play GameTree::find_best_play(int deepness)
{
    int best_value = -(std::numeric_limits<int>::max());
    Play best_play;
    int alpha = -(std::numeric_limits<int>::max());
    int beta = std::numeric_limits<int>::max();

    std::list<Play> possible_plays = this->generate_all_plays(current_board->board, false);

    for(const Play& play : possible_plays)
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
    int score = this->heuristic.eval(node->board);
    if ((deepness == 0) || (Maximizing && score <= alpha) || (!Maximizing && score >= beta))
    {
        node->result_minimax = score;
        return score;
    }  
    auto possible_plays = this->generate_all_plays(node->board, !Maximizing);
    
    if (possible_plays.empty()) return score;
    for (const Play& play : possible_plays)
    {
        BoardL new_state = this->apply_play((node->board), play);
        auto child_node = std::make_shared<GameNode>();
        child_node->board = new_state;
        child_node->dad = play;

        node->possible_plays.push_back(child_node);
    }
    
    if(Maximizing)
    {
        int better_value = -(std::numeric_limits<int>::max());

        for(auto& play_node : node->possible_plays)
        {
            int eval = this->minimax(play_node, deepness - 1, alpha, beta, false);

            better_value = std::max(better_value,eval);
            alpha = std::max(alpha, eval);

            if( beta <= alpha) 
            {
                break;
            }
        }
        node->result_minimax = better_value;
        node->possible_plays.clear();
        return better_value;
    }
    else
    {
        int worst_value = std::numeric_limits<int>::max();

        for(auto& play_node : node->possible_plays)
        {

            int eval = this->minimax(play_node, deepness - 1, alpha, beta, true);

            worst_value = std::min(worst_value,eval);
            beta = std::min(beta, eval);

            if( beta <= alpha)
            {
                break;
            }
        }
        node->result_minimax = worst_value;
        node->possible_plays.clear();
        return worst_value;
    }
}

std::list<Play> GameTree::generate_all_plays(const BoardL& current, bool team)
{
    std::list<Play> all_plays;

    for(auto& slot : current)
    {

        if(slot->piece->get_team() == team)
        {
            auto valid_moves = slot->piece->set_valid_moves(current, slot->pos);

            for(auto& move_target : valid_moves)
            {
                BoardObjectPtr captured_slot = nullptr;
                if (move_target->piece)
                {
                    for (auto& targeted : current) 
                    {
                        if (targeted->piece == move_target->piece) 
                        {
                            captured_slot = targeted;
                            break;
                        }
                    }
                }

                Play new_play;
                new_play.moving_piece = slot;
                new_play.destination = move_target->pos;
                new_play.captured_piece = captured_slot; 
                
                all_plays.push_back(new_play);
            }
        }
    }
    return all_plays;
}

BoardL GameTree::apply_play(const BoardL& original, const Play& move)
{
    BoardL new_state;
    std::map<BoardObjectPtr, BoardObjectPtr> original_to_new_map;

    for (auto const& original_slot : original)
    {
        PiecePtr new_piece = original_slot->piece->clone_piece();
        auto new_slot = std::make_shared<InBoardObject>(original_slot->pos, new_piece, original_slot->king);
        new_state.push_back(new_slot);
        original_to_new_map[original_slot] = new_slot;
    }

    BoardObjectPtr new_moving_slot = original_to_new_map[move.moving_piece];
    BoardObjectPtr new_captured_slot = (move.captured_piece) ? original_to_new_map[move.captured_piece] : nullptr;

    if (new_captured_slot)
    {
        if (new_moving_slot->piece->get_piece_type() == PieceType::Portal && new_moving_slot->piece->get_team() == new_captured_slot->piece->get_team())
        {
            new_captured_slot->pos = move.moving_piece->pos;
        }
        else if (new_captured_slot->piece->hurt(new_moving_slot->piece))
        {
            new_state.remove(new_captured_slot);
        }
    }
    if (new_moving_slot)
    {
        new_moving_slot->pos = move.destination;
    }

    if (new_moving_slot->piece->get_piece_type() == PieceType::Trapper)
    {
        auto new_bomb_piece = std::make_shared<Bomb>(new_moving_slot->piece->get_team()); 
        auto new_bomb_slot = std::make_shared<InBoardObject>(move.moving_piece->pos, new_bomb_piece);
        new_state.push_back(new_bomb_slot);
    }
    
    bool team_of_bombs_to_remove = !new_moving_slot->piece->get_team(); 
    new_state.erase(std::remove_if(new_state.begin(), new_state.end(),
        [team_of_bombs_to_remove](BoardObjectPtr element) {
            return element->piece->get_piece_type() == PieceType::Bomb && element->piece->get_team() == team_of_bombs_to_remove;}), new_state.end());


    return new_state;
}

void GameTree::set_current_board(const BoardL& current)
{
    current_board->board = current;
}

void GameTree::initial_game_eval()
{
    heuristic.initial_eval(current_board->board);
}
