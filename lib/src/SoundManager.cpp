#include "SoundManager.hpp"

std::map<SoundType, sf::SoundBuffer> SoundManager::sound_buffers;
std::vector<std::unique_ptr<sf::Sound>> SoundManager::active_sounds;

std::map<MusicType, std::string> SoundManager::music_paths;
std::unique_ptr<sf::Music> SoundManager::current_music = nullptr;

void SoundManager::init()
{
    std::string route = "assets/sounds/";
    sound_buffers[SoundType::Victory] = load_file(route + "victory.ogg");
    sound_buffers[SoundType::Defeat] = load_file(route + "defeat.ogg");
    sound_buffers[SoundType::MovePiece] = load_file(route + "move_piece.ogg");

    std::string music_route = "assets/music/";
    music_paths[MusicType::MainMenu] = music_route + "main_menu.ogg";
    music_paths[MusicType::Practice] = music_route + "practice.ogg";
    music_paths[MusicType::Tutorial] = music_route + "tutorial.ogg";
    music_paths[MusicType::Battle] = music_route + "battle.ogg";
    music_paths[MusicType::Versus] = music_route + "versus.ogg";

    set_music_volume(50.f);
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
    clean_finished_sounds();
    auto sound = std::make_unique<sf::Sound>(sound_buffers.at(type));
    sound->setVolume(100);
    sound->play();
    
    active_sounds.push_back(std::move(sound));
}

void SoundManager::clean_finished_sounds()
{
    active_sounds.erase(
        std::remove_if(active_sounds.begin(), active_sounds.end(),
            [](const std::unique_ptr<sf::Sound>& sound) {
                return sound->getStatus() == sf::SoundSource::Status::Stopped;
            }),
        active_sounds.end()
    );
}

void SoundManager::play_music(MusicType type, bool loop)
{
    stop_music();

    if (music_paths.find(type) == music_paths.end())
    {
        std::cerr << "Error: El MusicType solicitado no esta registrado en music_paths." << std::endl;
        return; 
    }

    current_music = std::make_unique<sf::Music>();

    std::string path = music_paths.at(type);
    if (!current_music->openFromFile(path))
    {
        std::cerr << "Error al abrir el archivo de musica: " << path << std::endl;
        current_music.reset();
        return;
    }

    current_music->setLooping(loop);
    current_music->play();
}

void SoundManager::stop_music()
{
    if (current_music)
    {
        current_music->stop();
        current_music.reset();
    }
}

void SoundManager::set_music_volume(float volume)
{
    if (current_music)
    {
        current_music->setVolume(std::clamp(volume, 0.0f, 100.0f));
    }
}