#include "soundManager.h"

SoundManager::SoundManager(const std::filesystem::path& path) {
    if (!IsAudioDeviceReady()) {
        InitAudioDevice();
    }

    std::string pathStr = path.string();
    m_sound = LoadSound(pathStr.c_str());
}

void SoundManager::play() {
    if (!IsSoundPlaying(m_sound)) {
        PlaySound(m_sound);
    }
}

void SoundManager::stop() {
    if (IsSoundPlaying(m_sound)) {
        StopSound(m_sound);
    }
}

void SoundManager::stopAll() {
    Sounds::Asteroid.stop();
    Sounds::Explode.stop();
    Sounds::Shoot.stop();
    Sounds::Thrust.stop();
    Sounds::MenuNavigate.stop();
    Sounds::MenuSelect.stop();  
}