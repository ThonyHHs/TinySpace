#include "pauseMenu.h"
#include "play.h"
#include "mainMenu.h"
#include "helpMenu.h"

PauseMenu::PauseMenu(Game &game) : Menu(game) {
    SetWindowSize(m_window.Width, m_window.Height);
    SetWindowPosition(
        (GetMonitorWidth(GetCurrentMonitor()) - m_window.Width)/2,
        (GetMonitorHeight(GetCurrentMonitor()) - m_window.Height)/2
    );
}

void PauseMenu::render() const {
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("PAUSE", 50, 100, 80, WHITE);

    for (size_t i = 0; i < m_options.size(); i++) {
        const char* option = m_options[i];

        if (m_selected == i) 
            DrawText(TextFormat("> %s <", option),  50, 300 + i*50, 40, WHITE);
        else 
            DrawText(option, 50, 300 + i*50, 40, WHITE);
    }
    EndDrawing();
}

void PauseMenu::update() {
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && m_selected > MenuOption::Resume) {
        m_selected = static_cast<MenuOption>(static_cast<int>(m_selected) - 1);
        Sounds::MenuNavigate.play();
    }
    if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && m_selected < MenuOption::Main) {
        m_selected = static_cast<MenuOption>(static_cast<int>(m_selected) + 1);
        Sounds::MenuNavigate.play();
    }

    if (IsKeyPressed(KEY_ENTER)) {
        Sounds::MenuSelect.play();
        switch (m_selected) {
            case MenuOption::Resume:
                m_game.resume();
                break;
            case MenuOption::Help:
                m_game.setScene<HelpMenu>(true);
                break;
            case MenuOption::Main:
                m_game.setScene<MainMenu>();
                m_game.running = false;
                break;
        }
    }
}