#include "../game.h"


static float bounceAngle, ballRelativeY;


void UpdateGameScreen()
{
    ++framesCounter;

    if (
            IsKeyPressed(KEY_ESCAPE) ||
            IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT) ||
            (mode == MODE_2PLAYERS && IsGamepadButtonPressed(1, GAMEPAD_BUTTON_MIDDLE_RIGHT))
            ) {
        screen = SCREEN_PAUSE;
        return;
    }

    if (IsKeyPressed(KEY_F3)) showDebug = !showDebug;


    // Player movement
    if (
            IsKeyDown(KEY_W) ||
            IsKeyDown(KEY_Z) ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) < -0.2f
            ) {
        p1.position.y -= PLAYER_SPEED;
    }
    if (
            IsKeyDown(KEY_S) ||
            IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
            GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y) > 0.2f
            ) {
        p1.position.y += PLAYER_SPEED;
    }

    switch (mode) {
        case MODE_1PLAYER:
            p2.position.y += PLAYER_SPEED*bot(ballPosition, p2.position);
            break;
        case MODE_2PLAYERS:
            if (
                    IsKeyDown(KEY_UP) ||
                    IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
                    GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y) < -0.2f
                    ) {
                p2.position.y -= PLAYER_SPEED;
            }

            if (
                    IsKeyDown(KEY_DOWN) ||
                    IsGamepadButtonDown(1, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
                    GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y) > 0.2f
                    ) {
                p2.position.y += PLAYER_SPEED;
            }
            break;
        default:
            break;
    }

    // Check out-of-bounds player
    if (p1.position.y < 0) p1.position.y = 0;
    if (p1.position.y + playerSize.y > GetScreenHeight()) p1.position.y = GetScreenHeight() - playerSize.y;
    if (p2.position.y < 0) p2.position.y = 0;
    if (p2.position.y + playerSize.y > GetScreenHeight()) p2.position.y = GetScreenHeight() - playerSize.y;


    // Ball mouvement
    ballPosition.x += ballDirection.x;
    ballPosition.y += ballDirection.y;

    // Ball collisions with player
    p1.colliding = CheckCollisionCircleRec(
            ballPosition, BALLRADIUS,
            (Rectangle) {p1.position.x, p1.position.y, playerSize.x, playerSize.y}
    );
    p2.colliding = CheckCollisionCircleRec(
            ballPosition, BALLRADIUS,
            (Rectangle) {p2.position.x, p2.position.y, playerSize.x, playerSize.y}
    );

    if (p1.colliding) {
        PlaySound(playerBeep);

        ballRelativeY = ballPosition.y - (p1.position.y + playerSize.y/2);
        bounceAngle = ballRelativeY*MAX_BOUNCE_ANGLE/(playerSize.y/2);

        ballDirection.x = cosf(bounceAngle)*ballSpeed;
        ballDirection.y = sinf(bounceAngle)*ballSpeed;

        ballPosition.x = p1.position.x + playerSize.x + BALLRADIUS;
    } else if (p2.colliding) {
        PlaySound(playerBeep);

        ballRelativeY = ballPosition.y - (p2.position.y + playerSize.y/2);
        bounceAngle = ballRelativeY*MAX_BOUNCE_ANGLE/(playerSize.y/2);

        ballDirection.x = -cosf(bounceAngle)*ballSpeed;
        ballDirection.y = sinf(bounceAngle)*ballSpeed;

        ballPosition.x = p2.position.x - BALLRADIUS;
    }


    // Check walls collision for score
    if ((ballPosition.x >= (GetScreenWidth() - BALLRADIUS))) {
        ++p1.score;
        ballPosition = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};

        ballSpeed = DEFAULT_BALL_SPEED;
        InitBallDirection(&ballDirection, 3*PI/4 + GetRandomValue(0, 1)*PI/2);

        screen = SCREEN_POINT;
        pauseFrames = POINT_WAIT_FRAME;
        CenterPlayerY(&p1);
        CenterPlayerY(&p2);
    } else if (ballPosition.x <= BALLRADIUS) {
        ++p2.score;
        ballPosition = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};

        ballSpeed = DEFAULT_BALL_SPEED;
        InitBallDirection(&ballDirection, -PI/4 + GetRandomValue(0, 1)*PI/2);

        screen = SCREEN_POINT;
        pauseFrames = POINT_WAIT_FRAME;
        CenterPlayerY(&p1);
        CenterPlayerY(&p2);
    }

    // Check walls collision for bouncing
    if ((ballPosition.y >= (GetScreenHeight() - BALLRADIUS)) || (ballPosition.y <= BALLRADIUS)) {
        PlaySound(wallBeep);
        ballDirection.y *= -1.0f;
    }

    // Increase speed periodically
    if (framesCounter%SPEED_INCREASE_INTERVAL == 0) {
        ballSpeed += 1.0f;
    }
}

void DrawGameScreen()
{
    // Drawing ball
    DrawCircleV(ballPosition, BALLRADIUS, WHITE);

    // Drawing players
    DrawRectangleV(p1.position, playerSize, WHITE);
    DrawRectangleV(p2.position, playerSize, WHITE);

    // Drawing separation line
    DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), WHITE);

    // Drawing scores
    DrawText(
            TextFormat("%d", p1.score),
            GetScreenWidth()/2 - 20 - MeasureText(TextFormat("%d", p1.score), 60),
            10,
            60,
            WHITE
    );
    DrawText(TextFormat("%d", p2.score), GetScreenWidth()/2 + 20, 10, 60, WHITE);

    // Drawing debug
    if (showDebug) {
        DrawFPS(10, 10);
        DrawText(TextFormat("%.3f ms", GetFrameTime()*1000.0f), 10, 30, 20, RAYWHITE);
    }
}