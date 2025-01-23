#include "play.h"
#include "pauseMenu.h"
#include "gameOverMenu.h"

Play::Play(Game &game) : m_game(game), m_current_time(GetTime()), m_end_time(GetTime() + WINDOW_SHRINK_RATE) {
    m_player = std::make_unique<Player>(&m_window);
}

void Play::updateWindowSize() {
    SetWindowSize(m_window.Width, m_window.Height);
    SetWindowPosition(
        (GetMonitorWidth(GetCurrentMonitor()) - m_window.Width)/2,
        (GetMonitorHeight(GetCurrentMonitor()) - m_window.Height)/2    
    );

    if (m_current_time > m_end_time) {
        m_window.Width -= WINDOW_SHRINK_SIZE;
        m_window.Height -= WINDOW_SHRINK_SIZE;
        m_end_time = m_current_time + WINDOW_SHRINK_RATE;
    }

    m_current_time = GetTime();
}

void Play::render() const {
    BeginDrawing();
    ClearBackground(BLACK);

    m_player->render();

    DrawText(TextFormat("SCORE: %d", m_player->score), GetScreenWidth()/2 - 70, 10, 40, WHITE);
    DrawText(TextFormat("%d", GetFPS()), GetScreenWidth() - 60, 20, 20, WHITE);

    EndDrawing();
}

void Play::update() {
    updateWindowSize();
    m_player->update();

    if (IsKeyPressed(KEY_ESCAPE)){
        m_game.running = false;
        m_game.setScene<PauseMenu>();
    }
    if (m_player->game_over) {
        m_game.running = false;
        m_game.setScene<GameOverMenu>();
    }
}