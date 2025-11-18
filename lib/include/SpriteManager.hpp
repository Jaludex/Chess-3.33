#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class SpriteManager
{
private:
    static std::map<std::string,sf::Texture> texture_map;
public:
    static void load_texture_piece(std::string type, std::string file);
    static const sf::Texture& get_piece_texture(std::string type);
    static void init();

    virtual void abstract() = 0;
};
