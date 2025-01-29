#include "player.h"
#include "../Scene/mainMenu.h"

Player::Player(WindowSettings *window) : 
    Entity(Vector2{window->Width, window->Height} / 2, {0}, 0, 0),
    m_current_time(GetTime()),
    m_next_bullet_time(GetTime() + BULLET_INTERVAL),
    m_next_enemy_time(GetTime() + ENEMY_INTERVAL) {
    m_window = window;
}

void Player::handleBullets() {
    for (auto& bullet : m_bullet_list) {
        bullet.update();
    }

    for (size_t i=0; i < m_bullet_list.size(); i++) {
        Bullet &bullet = m_bullet_list[i];
        if (bullet.isOutOfBound()) {
            if ((bullet.position.x < 0 || bullet.position.x > m_window->Width) && 
                GetScreenWidth() < GetMonitorWidth(GetCurrentMonitor())) {
                m_window->Width += 30;
            }
            if ((bullet.position.y < 0 || bullet.position.y > m_window->Height) &&
                GetScreenHeight() < GetMonitorHeight(GetCurrentMonitor())) {
                m_window->Height += 30;
            }
            
            m_bullet_list.erase(m_bullet_list.begin() + i);
        }
    }
}

void Player::handleEnemies() {
    if (m_current_time > m_next_enemy_time) {
        m_enemy_list.push_back(Enemy());
        m_next_enemy_time = m_current_time + ENEMY_INTERVAL;
    }

    for (size_t i=0; i < m_enemy_list.size(); i++) {
        Enemy *enemy = &m_enemy_list[i];

        if (enemy->isOutOfBound()) {
            m_enemy_list.erase(m_enemy_list.begin() + i);
        }
        
        enemy->update();
    }
}

template<size_t SIZE>
void Player::drawLines(std::array<Vector2, SIZE> array) const {
    for (size_t i=0; i < array.size()-1; i++) {
        Vector2 pos = array[i];
        Vector2 pos2 = array[i + 1];
        DrawLineEx(
            {position.x + Vector2Rotate(pos, m_angle - 1.5f).x * SCALE, position.y + Vector2Rotate(pos, m_angle - 1.5f).y * SCALE},
            {position.x + Vector2Rotate(pos2, m_angle - 1.5f).x * SCALE, position.y + Vector2Rotate(pos2, m_angle - 1.5f).y * SCALE}, 
            2, 
            WHITE
        );
    }
}

void Player::checkCollisions() {
    for (size_t i=0; i < m_enemy_list.size(); i++) {
        Enemy *enemy = &m_enemy_list[i];
        for (size_t j=0; j < m_bullet_list.size(); j++) {
            Bullet *bullet = &m_bullet_list[j];
            if (CheckCollisionPointCircle(bullet->position, enemy->position, enemy->size)) {
                Sounds::Asteroid.play();
                m_enemy_list.erase(m_enemy_list.begin() + i);
                m_bullet_list.erase(m_bullet_list.begin() + j);
                score++;
            }
        }

        for (size_t k=0; k < SHIP_LINES.size(); k++) {
            Vector2 point = {
                position.x + Vector2Rotate(SHIP_LINES[k], m_angle - 1.5f).x * SCALE, 
                position.y + Vector2Rotate(SHIP_LINES[k], m_angle - 1.5f).y * SCALE
            };
            if (CheckCollisionPointCircle(point, enemy->position, enemy->size)) {
                Sounds::Explode.play();
                game_over = true;
            }
        }

        if (GetScreenWidth() < 200 || GetScreenHeight() < 200)
            game_over = true;
    }
}

void Player::checkInput() {
    int direction = (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) - (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN));
    if (direction) {
        m_direction = Vector2{cosf(m_angle), sinf(m_angle)} * direction;
        m_speed += ACELERATION;
        m_thrust = true;
        Sounds::Thrust.play();
    } else {
        m_thrust = false;
        Sounds::Thrust.stop();
    }
    
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        m_angle -= TURN_VELOCITY * GetFrameTime();
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        m_angle += TURN_VELOCITY * GetFrameTime();
    

    if (IsKeyPressed(KEY_SPACE) && m_current_time > m_next_bullet_time) {
        Sounds::Shoot.play();
        m_bullet_list.push_back(
            Bullet(
                {
                    position.x + Vector2Rotate(SHIP_LINES[4], m_angle - 1.5f).x * SCALE, 
                    position.y + Vector2Rotate(SHIP_LINES[4], m_angle - 1.5f).y * SCALE
                },
                m_angle
            )
        );
        m_next_bullet_time = m_current_time + BULLET_INTERVAL;
    }
}

void Player::movement() {
    if (m_speed > MAX_VELOCITY) m_speed = MAX_VELOCITY;  
    m_speed *= FRICTION;
    position += m_direction * m_speed * GetFrameTime();

    position.x = fmod(position.x + GetScreenWidth(), GetScreenWidth());
    position.y = fmod(position.y + GetScreenHeight(), GetScreenHeight());
}

void Player::render() const {
    drawLines(SHIP_LINES);

    if (m_thrust) {
        drawLines(THRUST_LINES);
    }

    for (auto &bullet : m_bullet_list) {
        bullet.render();
    }
    for (auto &enemy : m_enemy_list) {
        enemy.render();
    }
}

void Player::update() {
    m_current_time = GetTime();
    handleBullets();
    handleEnemies();
    checkCollisions();
    checkInput();
    movement();
}