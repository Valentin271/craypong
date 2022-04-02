#include "game.h"

void InitGame()
{
    screen = SCREEN_MENU;
    mode = MODE_1PLAYER;
    framesCounter = 1; // NOTE: 1 to avoid modulos being applied right at the start

    showDebug = false;
    pauseFrames = 0;

    // players
    p1 = (Player) {
            {10, GetScreenHeight()/2 - playerSize.y/2},
            0,
            false
    };
    p2 = (Player) {
            {GetScreenWidth() - playerSize.x - 10, GetScreenHeight()/2 - playerSize.y/2},
            0,
            false
    };

    // ball
    ballPosition = (Vector2) {GetScreenWidth()/2, GetScreenWidth()/2};
    ballSpeed = DEFAULT_BALL_SPEED;
    InitBallDirection(&ballDirection, -PI/4 + GetRandomValue(0, 1)*PI/2);

    // sounds
    playerBeep = LoadSound("resources/playerBeep.wav");
    wallBeep = LoadSound("resources/wallBeep.wav");
}

void UpdateFrame()
{
    switch (screen) {
        case SCREEN_MENU:
            UpdateMenuScreen();
            break;
        case SCREEN_GAME:
            UpdateGameScreen();
            break;
        case SCREEN_POINT:
            UpdatePointScreen();
            break;
        case SCREEN_PAUSE:
            UpdatePauseScreen();
            break;
        default:
            break;
    }
}

void DrawFrame()
{
    switch (screen) {
        case SCREEN_MENU:
            DrawMenuScreen();
            break;
        case SCREEN_GAME:
            DrawGameScreen();
            break;
        case SCREEN_POINT:
            DrawGameScreen();
            DrawPointScreen();
            break;
        case SCREEN_PAUSE:
            DrawGameScreen();
            DrawPauseScreen();
            break;
        default:
            break;
    }
}

void UnloadGame()
{
    UnloadSound(playerBeep);
    UnloadSound(wallBeep);
}