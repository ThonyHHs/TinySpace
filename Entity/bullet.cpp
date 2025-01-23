#include "bullet.h"

Vector2 Bullet::getDirection(float angle) const {
    return Vector2({cosf(angle), sinf(angle)});
}

Bullet::Bullet(Vector2 position, float angle) : 
        Entity(position, getDirection(angle), SPEED_, angle) {}

bool Bullet::isOutOfBound() const {
    return {
        position.x > GetScreenWidth() || 
        position.y > GetScreenHeight() || 
        position.x < 0 || position.y < 0
    };
}

void Bullet::movement() {
    position += m_direction * m_speed * GetFrameTime();
}

void Bullet::render() const {
    DrawLineEx(position, position - m_direction * 10, 4, WHITE);
}

void Bullet::update() {
    movement();
}
