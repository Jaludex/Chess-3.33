#include <SpriteManager.hpp>

std::map<std::string, sf::Texture> SpriteManager::texture_map;

void SpriteManager::load_texture_piece(std::string type, std::string file)
{
    sf::Texture texture;
    if (!texture.loadFromFile(file))
    {
        throw(std::runtime_error("Texture not found: " + file));
    }
        texture_map[type] = texture;
}
const sf::Texture& SpriteManager::get_piece_texture(std::string type)
{
    return texture_map.at(type);
}

void SpriteManager::init()
{
    std::string route = "assets/";
    SpriteManager::load_texture_piece("white_pawn", route + "WhitePawn.png");
    SpriteManager::load_texture_piece("white_rook", route + "WhiteRook.png");
    SpriteManager::load_texture_piece("white_bishop", route + "WhiteBishop.png");
    SpriteManager::load_texture_piece("white_horse", route + "WhiteHorse.png");
    SpriteManager::load_texture_piece("white_queen", route + "WhiteQueen.png");
    SpriteManager::load_texture_piece("white_portal", route + "WhitePortal.png");
    SpriteManager::load_texture_piece("white_crook", route + "WhiteCrook.png");
    SpriteManager::load_texture_piece("white_archer", route + "WhiteArcher.png");
    SpriteManager::load_texture_piece("white_trapper", route + "WhiteTrapper.png");
    SpriteManager::load_texture_piece("white_trap", route + "WhiteTrap.png");
    SpriteManager::load_texture_piece("black_pawn", route + "BlackPawn.png");
    SpriteManager::load_texture_piece("black_rook", route + "BlackRook.png");
    SpriteManager::load_texture_piece("black_bishop", route + "BlackBishop.png");
    SpriteManager::load_texture_piece("black_horse", route + "BlackHorse.png");
    SpriteManager::load_texture_piece("black_queen", route + "BlackQueen.png");
    SpriteManager::load_texture_piece("black_portal", route + "BlackPortal.png");
    SpriteManager::load_texture_piece("black_crook", route + "BlackCrook.png");
    SpriteManager::load_texture_piece("black_archer", route + "BlackArcher.png");
    SpriteManager::load_texture_piece("black_trapper", route + "BlackTrapper.png");
    SpriteManager::load_texture_piece("black_trap", route + "BlackTrap.png");
    SpriteManager::load_texture_piece("crown", route + "Crown.png");
}
