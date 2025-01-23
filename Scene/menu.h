#pragma once

#include "../config.h"
class Game;

class Menu {
    protected:
        WindowSettings m_window;
        Game &m_game;
        const Sound MENU_SELECT_SOUND_ = LoadSound("../Audio/menu_select.wav");
        const Sound MENU_CONFIRM_SOUND_ = LoadSound("../Audio/menu_confirm.wav");

    public:
        Menu(Game &game) : m_game(game) {}
        virtual ~Menu() = default;
        virtual void render() const = 0;
        virtual void update() = 0;
};
