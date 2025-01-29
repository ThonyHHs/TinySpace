#include "game.h"
#include "Scene/mainMenu.h"


Game::Game() {
    InitWindow(m_window.Width, m_window.Height, m_window.Title);
    
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(m_window.Fps);
    SetExitKey(0);

    setScene<MainMenu>();
    running = false;

    while (!WindowShouldClose()) {
        loop();
    }

    CloseAudioDevice();
    CloseWindow();
}

Game::~Game() {
    m_level.reset();
    m_scene.reset();
}

void Game::loop() {
    if (m_scene) {
        m_scene->render();
        m_scene->update();
    }
    else if (running && m_level) {
        m_level->update();
        m_level->render();
    }
}

void Game::play() {
    m_scene = nullptr;
    running = true;
    m_level = std::make_shared<Play>(*this);
}

void Game::resume() {
    m_scene = nullptr;
    running = true;
}

void Game::end() {
    running = false;
    m_level = nullptr;
}