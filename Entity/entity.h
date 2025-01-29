#pragma once

#include "../config.h"
#include "../Sound/soundManager.h"

class Entity {
    protected:
        Vector2 m_direction;
        float m_speed = 0.0f;
        float m_angle = 0.0f;
    public:
        Vector2 position;
    public:
        Entity(Vector2 new_position = {0}, Vector2 direction = {0}, float speed = 0.0f, float angle = 0.0f) : position(new_position), m_direction(direction), m_speed(speed), m_angle(angle) {}

        virtual ~Entity() = default;

        virtual void movement() = 0;
        virtual void render() const = 0;
        virtual void update() = 0;
};