#pragma once

#include "menu.h"
#include "../game.h"


class GameOverMenu : public Menu{
    private:
        enum MenuOption {
            Play,
            Main
        };

        std::array<const char*, 2> m_options = {
            "Play Again", 
            "Main Menu"
        };
        MenuOption m_selected = MenuOption::Play;
    public:
        GameOverMenu(Game &game);
        void render() const override;
        void update() override;
};