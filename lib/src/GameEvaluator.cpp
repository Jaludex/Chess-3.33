#include <GameEvaluator.hpp>

int GameEvaluator::initial_material_sum_w = 0;

int GameEvaluator::initial_material_sum_b = 0;

void GameEvaluator::initial_eval(BoardL& pieces)
{
    GameEvaluator::initial_material_sum_w = 0;
    GameEvaluator::initial_material_sum_b = 0;

    for(auto p : pieces)
    {
        if(p->piece->get_team())
        {
            GameEvaluator::initial_material_sum_w += p->piece->get_material_value();
        }
        else
        {
            GameEvaluator::initial_material_sum_b += p->piece->get_material_value();
        }
    }
}

int GameEvaluator::eval(BoardL& pieces)
{
    int material_b = 0;
    int material_w = 0;
    int mobility_b = 0;
    int mobility_w = 0;
    int max_mobility_b = 0;
    int max_mobility_w = 0;
    BoardObjectPtr leader_w = nullptr;
    BoardObjectPtr leader_b = nullptr;
    int danger_b = 0;
    int danger_w = 0;

    for (auto p : pieces)
    {
        if (p->piece->get_team())
        {
            material_w += p->piece->get_material_value();
            mobility_w += p->piece->get_valid_moves().size();
            max_mobility_w += p->piece->get_max_mobility();
            danger_b += p->piece->get_material_value() * (p->pos.x + p->pos.y);
            if (p->leader)
            {
                leader_w = p;
            }
        }
        else
        {   
            material_b += p->piece->get_material_value();
            mobility_b += p->piece->get_valid_moves().size();
            max_mobility_b += p->piece->get_max_mobility();
            danger_w += p->piece->get_material_value() * (p->pos.x + p->pos.y);
            if (p->leader)
            {
                leader_b = p;
            }
        }
    }

    if(leader_w)
    {
        danger_w -= (leader_w->pos.x + leader_w->pos.y) * material_b;
    }

    if(leader_b)
    {
        danger_b -= (leader_b->pos.x + leader_b->pos.y) * material_w;
    }

    int material_value = 50 * ((material_b / GameEvaluator::initial_material_sum_b) + 1 - (material_w / GameEvaluator::initial_material_sum_w));

    int mobility_value = 50 * ((mobility_b / max_mobility_b) + 1 - (mobility_w / max_mobility_w));

    return material_value + mobility_value;
}
