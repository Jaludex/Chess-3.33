#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

enum class SoundType
{
    MovePiece,
    Victory,
    Defeat
};

enum class MusicType
{
    MainMenu,
    Battle,
    Versus,
    Practice,
    Tutorial
};

class SoundManager
{
private:
    static std::vector<std::unique_ptr<sf::Sound>> active_sounds;
    static std::map<SoundType, sf::SoundBuffer> sound_buffers;
    static sf::SoundBuffer load_file(std::string route);
    static void clean_finished_sounds();

    static std::map<MusicType, std::string> music_paths;
    static std::unique_ptr<sf::Music> current_music;

    
public:
    static void init();
    static void play(SoundType type);

    static void play_music(MusicType type, bool loop = true);
    static void stop_music();
    static void set_music_volume(float volume);
};

