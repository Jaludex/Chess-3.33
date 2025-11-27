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
    BoardObjectPtr king_w = nullptr;
    BoardObjectPtr king_b = nullptr;
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
            if (p->king)
            {
                king_w = p;
            }
        }
        else
        {   
            material_b += p->piece->get_material_value();
            mobility_b += p->piece->get_valid_moves().size();
            max_mobility_b += p->piece->get_max_mobility();
            danger_w += p->piece->get_material_value() * (p->pos.x + p->pos.y);
            if (p->king)
            {
                king_b = p;
            }
        }
    }

    if(!king_w)
    {          
        return 800;
    }
    else
    {
        danger_w -= (king_w->pos.x + king_w->pos.y) * material_b;
    }
    
    if(!king_b)
    {
        return 0;
    }
    else
    {
        danger_b -= (king_b->pos.x + king_b->pos.y) * material_w;
    }

    int material_value = 0;
    int mobility_value = 0;

    if (GameEvaluator::initial_material_sum_b != 0 && GameEvaluator::initial_material_sum_w != 0)
    { // 50 + 50 
        material_value = (((30 * material_b) / GameEvaluator::initial_material_sum_b) + (60 * (1 - (material_w / GameEvaluator::initial_material_sum_w)))); 
    }
    if (max_mobility_b != 0 && max_mobility_w != 0)
    { // 50 + 50 
        mobility_value = 50 * ((mobility_b / max_mobility_b) + 1 - (mobility_w / max_mobility_w)); 
    }

    return (material_value * 5) + (mobility_value * 3); //(0% to 100%) * 5 + (0% to 100%) *  3 = (0 to 500) + (0 to 300) = total of 800 max
}
