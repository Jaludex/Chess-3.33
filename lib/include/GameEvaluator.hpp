#include <Board.hpp>

class GameEvaluator
{
    private:
    static int initial_material_sum_w;
    static int initial_material_sum_b;

    public:
    static void initial_eval(BoardL&);
    static int eval(BoardL&);
};
