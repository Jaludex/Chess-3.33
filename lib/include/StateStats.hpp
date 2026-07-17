#pragma once
#include "IGameState.hpp"
#include "Stats.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class StateStats : public IGameState
{
private:
    sf::Font font;
    sf::Text* title_text;
    sf::Text* back_btn_text; 

    std::vector<Stats> loaded_stats;

    float scroll_y;       
    float total_height;   
    float row_height;     

    void draw_row(sf::RenderWindow& window, const Stats& stat, int index, float y_pos);
    std::string player_name;
    Stats current_match_stats;
    bool is_entering_name = false; 
public:
    StateStats(sf::RenderWindow* _window);
    ~StateStats();

    void init() override;
    void terminate() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    void on_resize() override;
    void add_char(char c) 
    {
        if (player_name.size() < 12) 
        {
            player_name += c;
        }
    }
    void remove_last_char() 
    {
        if (!player_name.empty()) 
        {
             player_name.pop_back();
        }
    }
    void set_current_match(int final_score, int final_rounds) 
    {
        current_match_stats = Stats("", final_score, final_rounds);
        player_name = "";
        is_entering_name = true;
    }
    void save_current_player();
};