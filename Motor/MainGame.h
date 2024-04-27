#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

enum class GameState {
    PLAY, EXIT
};

class MainGame {
private:
    Sprite sprite;
    Sprite sprite2;
    Sprite sprite3;
    Sprite sprite4;
    int width;
    int height;
    SDL_Window* window;
    GLS_Program program;
    float time = 0;

public:
    MainGame();
    ~MainGame();
    GameState gameState;
    void run();
    void draw(Sprite& sprite);
    void update(std::chrono::steady_clock::time_point start_time);
    void init();
    void initShaders();
    void processInput();
};
