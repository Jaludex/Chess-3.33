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
    SpriteManager::load_texture_piece("white_pawn", "assets/WhitePawn.png");
    SpriteManager::load_texture_piece("white_rook", "assets/WhiteRook.png");
    SpriteManager::load_texture_piece("white_bishop", "assets/WhiteBishop.png");
    SpriteManager::load_texture_piece("white_horse", "assets/WhiteHorse.png");
    SpriteManager::load_texture_piece("white_queen", "assets/WhiteQueen.png");
    SpriteManager::load_texture_piece("white_portal", "assets/WhitePortal.png");
    SpriteManager::load_texture_piece("white_crook", "assets/WhiteCrook.png");
    SpriteManager::load_texture_piece("white_archer", "assets/WhiteArcher.png");
    SpriteManager::load_texture_piece("white_trapper", "assets/WhiteTrapper.png");
    SpriteManager::load_texture_piece("white_trap", "assets/WhiteTrap.png");
    SpriteManager::load_texture_piece("black_pawn", "assets/BlackPawn.png");
    SpriteManager::load_texture_piece("black_rook", "assets/BlackRook.png");
    SpriteManager::load_texture_piece("black_bishop", "assets/BlackBishop.png");
    SpriteManager::load_texture_piece("black_horse", "assets/BlackHorse.png");
    SpriteManager::load_texture_piece("black_queen", "assets/BlackQueen.png");
    SpriteManager::load_texture_piece("black_portal", "assets/BlackPortal.png");
    SpriteManager::load_texture_piece("black_crook", "assets/BlackCrook.png");
    SpriteManager::load_texture_piece("black_archer", "assets/BlackArcher.png");
    SpriteManager::load_texture_piece("black_trapper","assets/BlackTrapper.png");
    SpriteManager::load_texture_piece("black_trap", "assets/BlackTrap.png");
}