#include "Gametree.hpp"
#include "Board.hpp" 
#include "Trapper.hpp"
#include <map>
GameTree::GameTree(BoardL beggining, std::function<int(const BoardL&)> f_juego)
{
    this->f_heuristica = f_juego;

    this->current_board = std::make_shared<GameNode>();
    this->current_board->board = beggining;
    this->current_board->dad = Play();
    this->current_board->result_minimax = 0;
}

Play GameTree::find_best_play(int deepness)
{
    int best_value = -(std::numeric_limits<int>::max());
    Play best_play;
    int alpha = -(std::numeric_limits<int>::max());
    int beta = std::numeric_limits<int>::max();

    std::list<Play> possible_plays = this->generate_all_plays(current_board->board, true);

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
    //Nos falta meterle que verifique fin de juego, pa eso necesito al augusto
    if (deepness == 0)
    {
        int score = this->f_heuristica(node->board);
        node->result_minimax = score;
        return score;
    }  

    if(Maximizing)
    {
        int better_value = -(std::numeric_limits<int>::max());
        auto possible_plays = this->generate_all_plays(node->board, false);

        for(const Play& play : possible_plays)
        {
            BoardL new_state = this->apply_play(node->board, play);
            auto play_node = std::make_shared<GameNode>();
            play_node->board = new_state;
            play_node->dad = play;

            node->possible_plays.push_back(play_node);

            int eval = this->minimax(play_node, deepness - 1, alpha, beta, false);

            better_value = std::max(better_value,eval);
            alpha = std::max(alpha, eval);

            if( beta <= alpha) 
            {
                break;
            }
        }
        node->result_minimax = better_value;
        return better_value;
    }
    else
    {
        int worst_value = std::numeric_limits<int>::max();
        auto possible_plays = this->generate_all_plays(node->board, true);

        for(const auto& play : possible_plays)
        {
            BoardL new_state = this->apply_play(node->board, play);
            auto play_node = std::make_shared<GameNode>();
            play_node->board = new_state;
            play_node->dad = play;
             node->possible_plays.push_back(play_node);

            int eval = this->minimax(play_node, deepness - 1, alpha, beta, true);

            worst_value = std::min(worst_value,eval);
            beta = std::min(beta, eval);

            if( beta <= alpha)
            {
                break;
            }
        }
        node->result_minimax = worst_value;
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
                new_play.destino = move_target->pos;
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

    for (auto const& slot_original : original)
    {
        auto nuevo_slot = std::make_shared<InBoardObject>(slot_original->pos, slot_original->piece);
        new_state.push_back(nuevo_slot);
        original_to_new_map[slot_original] = nuevo_slot;
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
        new_moving_slot->pos = move.destino;
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