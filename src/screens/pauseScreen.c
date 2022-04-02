#include "../game.h"

void UpdatePauseScreen()
{
    if (IsKeyPressed(KEY_ESCAPE)) screen = SCREEN_GAME;
}

void DrawPauseScreen()
{
    DrawText("Pause", TextCenterX("Pause", 50), TextCenterY(50), 50, GRAY);
}