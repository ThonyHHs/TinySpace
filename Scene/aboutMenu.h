#pragma once

#include "menu.h"
#include "../game.h"

class AboutMenu : public Menu{
    private:
        const char* m_option = "> Back <";
    public:
        AboutMenu(Game &game);
        void render() const override;
        void update() override;
};
