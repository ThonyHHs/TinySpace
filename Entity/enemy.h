#pragma once

#include "entity.h"

class Enemy : public Entity {
    private:
        float m_bound_radius;
    private:
        Vector2 generatePosition() const;
    public:
        float size;
    public:
        Enemy();
        bool isOutOfBound() const;
        void movement() override;
        void render() const override;
        void update() override;
};