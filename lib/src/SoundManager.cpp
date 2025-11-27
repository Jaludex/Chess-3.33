#include "SoundManager.hpp"

std::map<std::string, sf::SoundBuffer> SoundManager::sound_buffers;
std::unique_ptr<sf::Sound> SoundManager::last_sound;

void SoundManager::init()
{
    last_sound = nullptr;
    std::string route = "assets/sounds/";
    sound_buffers["victory"] = load_file(route + "victory.ogg");
    sound_buffers["defeat"] = load_file(route + "defeat.ogg");
    sound_buffers["move_piece"] = load_file(route + "move_piece.ogg");
}

sf::SoundBuffer SoundManager::load_file(std::string route)
{
    sf::SoundBuffer new_buffer;
    if (!new_buffer.loadFromFile(route))
    {
        std::cerr << "Error loading file: " << route << std::endl;
    }
    return new_buffer;
}

void SoundManager::play(SoundType type)
{
    switch (type)
    {
    case SoundType::Victory:
        last_sound = std::make_unique<sf::Sound>(sound_buffers.at("victory"));
        break;
    case SoundType::Defeat:
        last_sound = std::make_unique<sf::Sound>(sound_buffers.at("defeat"));
        break;
    case SoundType::MovePiece:
    default:
        last_sound = std::make_unique<sf::Sound>(sound_buffers.at("move_piece"));
        break;
    }
    std::cout << "Play" << std::endl;
    last_sound->play();
}