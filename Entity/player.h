#pragma once

#include <algorithm>

#include "entity.h"
#include "bullet.h"
#include "enemy.h"

class Player : public Entity {
    private:
        static constexpr uint8_t MAX_VELOCITY  = 200;
        static constexpr uint8_t TURN_VELOCITY = 4;
        static constexpr uint8_t SCALE         = 40;

        static constexpr float ACELERATION     = 10;
        static constexpr float BULLET_INTERVAL = .3f;
        static constexpr float ENEMY_INTERVAL  = 1.5f;
        static constexpr float FRICTION        = .98f;

        static constexpr std::array<Vector2, 6> SHIP_LINES = {{
            {0.4f, -0.4f},
            {0.2f, -0.2f},
            {-0.2f, -0.2f},
            {-0.4f, -0.4f},
            {0.0f, 0.5f},
            {0.4f, -0.4f}
        }};
        static constexpr std::array<Vector2, 3> THRUST_LINES = {{
            {0.2f, -0.2f},
            {0.0f, -0.5f},
            {-0.2f, -0.2f}
        }};

        Sound m_thrust_sound;
        Sound m_shoot_sound;
        Sound m_asteroid_sound;
        Sound m_explode_sound;

        bool m_thrust_on = false;

        float m_current_time;
        float m_next_bullet_time;
        float m_next_enemy_time;
        
        WindowSettings *m_window = nullptr;
        std::vector<Bullet> m_bullet_list;
        std::vector<Enemy> m_enemy_list;
    private:
        void handleBullets();
        void handleEnemies();
        void handleSound(const Sound &sound, bool pause);
        template<size_t SIZE>
        void drawLines(std::array<Vector2, SIZE> array) const;

    public:
        bool game_over = false;
        uint32_t score = 0;
    public:
        explicit Player(WindowSettings *window);
        
        void checkCollisions();
        void checkInput();
        void movement() override;
        void render() const override;
        void update() override;
};