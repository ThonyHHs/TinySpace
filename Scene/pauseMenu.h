#pragma once

#include "menu.h"
#include "../game.h"


class PauseMenu : public Menu {
    private:
        enum MenuOption {
            Resume,
            Help,
            Main
        };

        std::array<const char*, 3> m_options = {
            "Resume",
            "Help",
            "Main Menu"
        };
        MenuOption m_selected = MenuOption::Resume;

    public:
        PauseMenu(Game& game);
        void render() const override;
        void update() override;
};