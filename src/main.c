#include "raylib.h"

#include "game.h"
#include "config.h"


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


int main()
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CrayPong");
    InitAudioDevice();

    SetExitKey(KEY_NULL);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    InitGame();
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        UpdateFrame();

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);
        DrawFrame();

        EndDrawing();
    }

    // De-Initialization
    //---------------------------------------------------------
    UnloadGame();
    CloseAudioDevice();
    CloseWindow();
    //----------------------------------------------------------

    return 0;
}