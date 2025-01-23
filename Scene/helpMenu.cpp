#include "helpMenu.h"
#include "mainMenu.h"
#include "pauseMenu.h"

HelpMenu::HelpMenu(Game &game, bool sub_menu) : Menu(game), m_sub_menu(sub_menu) {
    SetWindowSize(m_window.Width, m_window.Height);
    SetWindowPosition(
        (GetMonitorWidth(GetCurrentMonitor()) - m_window.Width)/2,
        (GetMonitorHeight(GetCurrentMonitor()) - m_window.Height)/2    
    );
}

void HelpMenu::render() const{
    constexpr std::array text = {
        "W/UP_ARROW: Foward",
        "A/LEFT_ARROW: Turn Left",
        "S/DOWN_ARROW: Backwards",
        "D/RIGHT_ARROW: Turn Right",
        "SPACE: Shoot"
    };

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("ABOUT", 50, 100, 80, WHITE);

    for (size_t i=0; i<text.size(); i++) {
        DrawText(text[i], 50, 200 + i * 50, 40, WHITE);
    }

    DrawText(m_option, GetScreenWidth()/2 - 80, GetScreenHeight()-100, 40, WHITE);
    EndDrawing();
}

void HelpMenu::update() {
    if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(MENU_CONFIRM_SOUND_);
        if (m_sub_menu) {
            m_game.setScene<PauseMenu>();
        } else {
            m_game.setScene<MainMenu>();
        }
    } 
}