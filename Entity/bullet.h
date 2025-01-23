#pragma once

#include "entity.h"

class Bullet : public Entity {
    private:
        static constexpr int SPEED_ = 300;
    private:
        Vector2 getDirection(float angle) const;
    public:
        Bullet(Vector2 position, float angle);
        bool isOutOfBound() const;
        void movement() override;
        void render() const override;
        void update() override;
};