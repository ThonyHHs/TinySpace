#pragma once

#include "menu.h"
#include "../game.h"


class MainMenu : public Menu {
    private:
        enum MenuOption {
            Play,
            Help,
            About,
            Exit
        };

        std::array<const char*, 4> m_options = {
            "Play", 
            "Help", 
            "About", 
            "Exit"
        };
        
        MenuOption m_selected = MenuOption::Play;
    public:
        MainMenu(Game &game);
        void render() const override;
        void update() override;
};