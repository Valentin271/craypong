#include "raylib.h"

#include "config.h"
#include "bot.h"


typedef struct Player {
    Vector2 position;
    unsigned short score;
    bool colliding;
} Player;


int main()
{
    // Initialization
    //---------------------------------------------------------
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CrayPong");
    InitAudioDevice();

    SetExitKey(KEY_NULL);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    bool debugMenu = false;

    Player p1 = {
            {playerSize.x, GetScreenHeight()/2 - playerSize.y/2},
            0,
            false
    };
    Player p2 = {
            {GetScreenWidth() - playerSize.x*2, GetScreenHeight()/2 - playerSize.y/2},
            0,
            false
    };

    Vector2 ballPosition = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    Vector2 ballSpeed = {5.0f, 5.0f};

    const Sound bip = LoadSound("resources/bip.wav");
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Reset
        //-----------------------------------------------------
        p1.colliding = false;
        p2.colliding = false;
        //-----------------------------------------------------

        // Update
        //-----------------------------------------------------

        // PLayer mouvement
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_Z)) p1.position.y -= PLAYER_SPEED;
        if (IsKeyDown(KEY_S)) p1.position.y += PLAYER_SPEED;
        // TODO: Choose between AI and 2P
//        if (IsKeyDown(KEY_UP)) p2.position.y -= PLAYER_SPEED;
//        if (IsKeyDown(KEY_DOWN)) p2.position.y += PLAYER_SPEED;

        p2.position.y += PLAYER_SPEED*bot(ballPosition, p2.position);

        if (p1.position.y < 0) p1.position.y = 0;
        if (p1.position.y + playerSize.y > GetScreenHeight()) p1.position.y = GetScreenHeight() - playerSize.y;
        if (p2.position.y < 0) p2.position.y = 0;
        if (p2.position.y + playerSize.y > GetScreenHeight()) p2.position.y = GetScreenHeight() - playerSize.y;

        // Collisions
        p1.colliding = CheckCollisionCircleRec(
                ballPosition, BALLRADIUS,
                (Rectangle) {p1.position.x, p1.position.y, playerSize.x, playerSize.y}
        );
        p2.colliding = CheckCollisionCircleRec(
                ballPosition, BALLRADIUS,
                (Rectangle) {p2.position.x, p2.position.y, playerSize.x, playerSize.y}
        );

        if (p1.colliding || p2.colliding) {
            PlaySound(bip);
            ballSpeed.x *= -1.0f;
        }

        // Ball mouvement
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // Check walls collision for bouncing
        if ((ballPosition.x >= (GetScreenWidth() - BALLRADIUS))) {
            ++p1.score;
            ballPosition = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
            ballSpeed.x *= -1.0f;
        } else if (ballPosition.x <= BALLRADIUS) {
            ++p2.score;
            ballPosition = (Vector2) {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
            ballSpeed.x *= -1.0f;
        }

        if ((ballPosition.y >= (GetScreenHeight() - BALLRADIUS)) || (ballPosition.y <= BALLRADIUS))ballSpeed.y *= -1.0f;

        if (IsKeyPressed(KEY_F3)) debugMenu = !debugMenu;
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

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
        if (debugMenu) {
            DrawFPS(10, 10);
            DrawText(TextFormat("%.3f ms", GetFrameTime()*1000.0f), 10, 30, 20, RAYWHITE);
        }

        EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}