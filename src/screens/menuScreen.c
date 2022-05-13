#include "../game.h"

Rectangle player1Text = {};

void UpdateMenuScreen()
{
    if (
        IsKeyPressed(KEY_DOWN) ||
        IsKeyPressed(KEY_UP) ||
        IsKeyPressed(KEY_W) ||
        IsKeyPressed(KEY_Z) ||
        IsKeyPressed(KEY_S) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)
        ) {
        mode = mode == MODE_1PLAYER ? MODE_2PLAYERS : MODE_1PLAYER;
    }

    if (
        IsKeyPressed(KEY_ENTER) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
        IsGamepadButtonPressed(1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)
        ) {
        screen = SCREEN_GAME;
    }

    player1Text = (Rectangle) {
        TextCenterX("1 PLAYER", 50),
        GetScreenHeight()/3 - 25,
        MeasureText("1 PLAYER", 50),
        50
    };

#ifdef PLATFORM_WEB
    if (CheckCollisionPointRec(GetTouchPosition(0), player1Text)) {
        screen = SCREEN_GAME;
    }
#endif
}

void DrawMenuScreen()
{
    DrawText(
        "1 PLAYER",
        player1Text.x,
        player1Text.y,
        50,
        mode == MODE_1PLAYER ? WHITE : GRAY
    );
    DrawText(
        "2 PLAYERS",
        TextCenterX("2 PLAYERS", 50),
        2*GetScreenHeight()/3 - 25,
        50,
        mode == MODE_2PLAYERS ? WHITE : GRAY
    );
}