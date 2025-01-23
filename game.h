#pragma once

#include "config.h"
#include "Entity/player.h"
#include "Scene/menu.h"
#include "Scene/play.h"

class Game {
    private:
        WindowSettings m_window;
        std::shared_ptr<Menu> m_scene;
        std::shared_ptr<Play> m_level;
    private:
        void loop();

    public:
        bool running;
    public:
        Game();
        ~Game();

        template<typename T>
        void setScene(bool sub_menu) {
            m_scene = std::make_shared<T>(*this, sub_menu);
        }
        template<typename T>
        void setScene() {
            m_scene = std::make_shared<T>(*this);
        }
        void play();
        void resume();
        void end();
};