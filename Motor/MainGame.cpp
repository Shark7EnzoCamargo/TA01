#include "MainGame.h"
#include "Sprite.h"
#include <chrono>
#include <thread>

MainGame::MainGame()
{
    window = NULL;
    width = 800;
    height = 600;
    gameState = GameState::PLAY;
}

void MainGame::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("TA1_con_fe_xd", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    //se valida si hubo un error
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        //falta validar el estado del glew
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    initShaders();
}

MainGame::~MainGame()
{
}

void MainGame::run() {
    init();
    auto start_time = std::chrono::steady_clock::now();
    update(start_time);
}

void MainGame::initShaders() {
    program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
    program.addAtribute("vertexPoistion");
    program.addAtribute("vertexColor");
    program.linkShader();
}


void MainGame::draw(Sprite& sprite) {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.use();
    GLuint timeLocation = program.getUniformLocation("time");
    glUniform1f(timeLocation, time);
    time += 0.02;
    sprite.draw();
    program.unuse();
    SDL_GL_SwapWindow(window);
}

void MainGame::update(std::chrono::steady_clock::time_point start_time) {
    Sprite sprite;
    sprite.init(-1, -1, 1, 1); 

    // Se dibujará los cuadrados en un intervalo de 5 segundos

    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed_seconds = current_time - start_time;
    float elapsed_time = elapsed_seconds.count();

    while (elapsed_time < 5.0) { 
        draw(sprite);
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); 
        current_time = std::chrono::steady_clock::now();
        elapsed_seconds = current_time - start_time;
        elapsed_time = elapsed_seconds.count();
    }

    Sprite sprite2;
    sprite2.init(0, 0, 1, 1);
    draw(sprite2);

    start_time = std::chrono::steady_clock::now();
    current_time = std::chrono::steady_clock::now();
    elapsed_seconds = current_time - start_time;
    elapsed_time = elapsed_seconds.count();
    while (elapsed_time < 5.0) { 
        draw(sprite2);
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); 
        current_time = std::chrono::steady_clock::now();
        elapsed_seconds = current_time - start_time;
        elapsed_time = elapsed_seconds.count();
    }

    Sprite sprite3;
    sprite3.init(-1, 0, 1, 1);
    draw(sprite3);

    start_time = std::chrono::steady_clock::now();
    current_time = std::chrono::steady_clock::now();
    elapsed_seconds = current_time - start_time;
    elapsed_time = elapsed_seconds.count();
    while (elapsed_time < 5.0) { 
        draw(sprite3);
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); 
        current_time = std::chrono::steady_clock::now();
        elapsed_seconds = current_time - start_time;
        elapsed_time = elapsed_seconds.count();
    }

    Sprite sprite4;
    sprite4.init(0, -1, 1, 1);
    draw(sprite4);
}
