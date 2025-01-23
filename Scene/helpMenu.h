#pragma once

#include "menu.h"
#include "../game.h"

class HelpMenu : public Menu{
    private:
        const char* m_option = "> Back <";
        bool m_sub_menu;

    public:
        HelpMenu(Game &game, bool sub_menu);
        void render() const override;
        void update() override;
};