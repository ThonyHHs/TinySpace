#pragma once

#include <filesystem>

#include "../config.h"

class SoundManager {
    private:
        Sound m_sound;

    public:
        SoundManager(const std::filesystem::path& path);

        void play();
        void stop();

        static void stopAll();
};

namespace Sounds {
    inline SoundManager Asteroid = {"Assets/Audio/asteroid.wav"};
    inline SoundManager Explode = {"Assets/Audio/Explode.wav"};
    inline SoundManager Shoot = {"Assets/Audio/shoot.wav"};
    inline SoundManager Thrust = {"Assets/Audio/thrust.wav"};
    inline SoundManager MenuNavigate = {"Assets/Audio/menu_navigate.wav"};
    inline SoundManager MenuSelect = {"Assets/Audio/menu_select.wav"};
}