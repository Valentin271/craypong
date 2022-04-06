#include "raylib.h"

#include "game.h"
#include "config.h"

#ifdef PLATFORM_WEB
#include "emscripten.h"
#endif

//--------------------------------------------------
// Shared variables
//--------------------------------------------------
SCREEN screen;
MODE mode;
int framesCounter;

bool showDebug;
int pauseFrames;

// players
Player p1, p2;

// ball
Vector2 ballPosition, ballDirection;
float ballSpeed;

// sounds
Sound playerBeep, wallBeep;

void UpdateDrawFrame()
{
    UpdateFrame();

    BeginDrawing();

    ClearBackground(BLACK);
    DrawFrame();

    EndDrawing();
}

int main()
{
#ifndef DEBUG
    SetTraceLogLevel(LOG_NONE);
#endif

    // Initialization
    //---------------------------------------------------------
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CrayPong");
    InitAudioDevice();
    InitGame();

    SetExitKey(KEY_NULL);

#ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

#endif

    // De-Initialization
    //---------------------------------------------------------
    UnloadGame();
    CloseAudioDevice();
    CloseWindow();
    //----------------------------------------------------------

    return 0;
}