#pragma once

#include "../Entity/player.h"

class Game;

class Play {
    private:
        static constexpr int   WINDOW_SHRINK_SIZE = 2;
        static constexpr float WINDOW_SHRINK_RATE = 0.1f;

        WindowSettings m_window;
        std::unique_ptr<Player> m_player;
        float m_current_time, m_end_time;
        Game &m_game;  
    public:
        Play(Game &game);
        void updateWindowSize();
        void render() const ;
        void update();
};