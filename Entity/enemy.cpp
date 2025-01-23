#include "enemy.h"

Vector2 Enemy::generatePosition() const {
    float offset = 30 * 2;
    int side = GetRandomValue(0, 3);

    switch (side) {
        case 0: // Top
            return {(float)GetRandomValue(0, GetScreenWidth()), -offset};
        case 1: // Right
            return {GetScreenWidth() + offset, (float)GetRandomValue(0, GetScreenHeight())};
        case 2: // Bottom
            return {(float)GetRandomValue(0, GetScreenWidth()), GetScreenHeight() + offset};
        case 3: // Left
            return {-offset, (float)GetRandomValue(0, GetScreenHeight())};
        default:
            return {0.0f, 0.0f}; // Default, shouldn't happen
    }
}

bool Enemy::isOutOfBound() const {
    return {
        position.x > m_bound_radius * 2 || 
        position.y > m_bound_radius * 2 || 
        position.x < -m_bound_radius || 
        position.y < -m_bound_radius
    };
}

Enemy::Enemy() : Entity(generatePosition(), {0}, GetRandomValue(80, 120), 0) {
    m_angle = atan2f((GetScreenHeight()/2) - position.y, (GetScreenWidth()/2) - position.x);
    m_direction = Vector2({cosf(m_angle), sinf(m_angle)});
    m_bound_radius = sqrtf(pow(GetScreenWidth(), 2) + pow(GetScreenHeight(), 2));
    size = GetRandomValue(10, 30);
}

void Enemy::movement() {
    position += m_direction * m_speed * GetFrameTime();
}

void Enemy::render() const {
    DrawCircleLinesV(position, size, WHITE);
}

void Enemy::update() {
    m_bound_radius = sqrtf(pow(GetScreenWidth(), 2) + pow(GetScreenHeight(), 2));
    movement();
}