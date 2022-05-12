#include "../game.h"

void UpdatePauseScreen()
{
    if (
            IsKeyPressed(KEY_ESCAPE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT) ||
            (mode == MODE_2PLAYERS && IsGamepadButtonPressed(1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
            ) {
        screen = SCREEN_GAME;
    }
}

void DrawPauseScreen()
{
    DrawText("Pause", TextCenterX("Pause", 50), TextCenterY(50), 50, GRAY);
}