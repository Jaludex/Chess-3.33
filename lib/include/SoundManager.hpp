#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>

enum class SoundType
{
    MovePiece,
    Victory,
    Defeat
};

class SoundManager
{
private:
    static std::unique_ptr<sf::Sound> last_sound;
    static std::map<std::string, sf::SoundBuffer> sound_buffers;
    static sf::SoundBuffer load_file(std::string route);
public:
    static void init();
    static void play(SoundType type);
};

