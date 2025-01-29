#pragma once

#include "../config.h"
#include "../Sound/soundManager.h"

class Game;

class Menu {
    protected:
        WindowSettings m_window;
        Game &m_game;
        
    public:
        Menu(Game &game) : m_game(game) {}
        virtual ~Menu() = default;
        virtual void render() const = 0;
        virtual void update() = 0;
};
