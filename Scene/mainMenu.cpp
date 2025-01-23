#include "mainMenu.h"
#include "aboutMenu.h"
#include "helpMenu.h"
#include "play.h"

MainMenu::MainMenu(Game &game) : Menu(game) {
    SetWindowSize(m_window.Width, m_window.Height);
    SetWindowPosition(
        (GetMonitorWidth(GetCurrentMonitor()) - m_window.Width)/2,
        (GetMonitorHeight(GetCurrentMonitor()) - m_window.Height)/2    
    );
}

void MainMenu::render() const {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("EXPANSION", 50, 100, 80, WHITE);
    DrawText("BATTLE", 50, 200, 80, WHITE);

    for (size_t i = 0; i < m_options.size(); i++) {
        const char* option = m_options[i];

        if (m_selected == i) 
            DrawText(TextFormat("> %s <", option),  50, 300 + i*50, 40, WHITE);
        else 
            DrawText(option, 50, 300 + i*50, 40, WHITE);
    }

    DrawText("Made by: ThonyHyperHeadShot", GetScreenWidth()-240, GetScreenHeight() - 25, 15, WHITE);
    EndDrawing();
}

void MainMenu::update() {
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && m_selected > MenuOption::Play) {
        m_selected = static_cast<MenuOption>(static_cast<int>(m_selected) - 1);
        PlaySound(MENU_SELECT_SOUND_);
    }
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && m_selected < MenuOption::Exit) {
        m_selected = static_cast<MenuOption>(static_cast<int>(m_selected) + 1);
        PlaySound(MENU_SELECT_SOUND_);
    }
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
    }

    if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(MENU_CONFIRM_SOUND_);
        switch (m_selected) {
            case MenuOption::Play:
                m_game.play();
                break;
            case MenuOption::Help:
                m_game.setScene<HelpMenu>(false);
                break;
            case MenuOption::About:
                m_game.setScene<AboutMenu>();
                break;
            case MenuOption::Exit:
                CloseWindow();
                break;
        }
    }
}