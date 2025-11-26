#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
// Asegúrate de que la ruta sea correcta según donde pusiste el archivo
#include "../include/json.hpp" 

using json = nlohmann::json;

class Stats
{
public:
    Stats();
    Stats(std::string name, int score, int t_rounds, int lost_pieces);
    ~Stats();

    std::string get_name() const;
    int get_score() const;
    int get_t_rounds() const;
    int get_l_pieces() const;

    static Stats load_by_name(std::string name_to_find, std::string filepath = "stats.json");

    void save_or_update(std::string filepath = "stats.json");

    static std::vector<Stats> load_all(std::string filepath = "stats.json");
    
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Stats, name, score, total_rounds, total_lost_pieces)

private:
    std::string name;
    int score;
    int total_rounds;
    int total_lost_pieces;
};