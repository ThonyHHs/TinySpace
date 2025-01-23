#include "aboutMenu.h"
#include "mainMenu.h"
#include "pauseMenu.h"

AboutMenu::AboutMenu(Game &game) : Menu(game) {
    SetWindowSize(m_window.Width, m_window.Height);
    SetWindowPosition(
        (GetMonitorWidth(GetCurrentMonitor()) - m_window.Width)/2,
        (GetMonitorHeight(GetCurrentMonitor()) - m_window.Height)/2    
    );
}

void AboutMenu::render() const {
    constexpr std::array text = {
        "It is a simple copy of the Asteroids game, but with a new",
        "mechanic: the screen shrinks, and you need to shoot the",
        "borders to keep it at a playable size.",
        "This game was made to help me familiarize myself with",
        "the C++ language.", 
        "It was a great project for me to learn new concepts and", 
        "new ways to design a program.", 
        "Even though I still suck at this, I loved making this project",
        "and finally finishing one.", 
        "The game was made in a total of: I dont know how many hours."
    };

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("ABOUT", 50, 100, 80, WHITE);

    for (size_t i=0; i<text.size(); i++) {
        DrawText(text[i], 50, 250 + i * 30, 20, WHITE);
    }

    DrawText(m_option, GetScreenWidth()/2 - 80, GetScreenHeight()-100, 40, WHITE);
    EndDrawing();
}

void AboutMenu::update() {
    if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(MENU_CONFIRM_SOUND_);
        m_game.setScene<MainMenu>();
    }
}