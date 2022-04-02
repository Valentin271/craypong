#ifndef CRAYPONG_CONFIG_H
#define CRAYPONG_CONFIG_H

#include "math.h"

#include "raylib.h"

// Window

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 450

// Game

#define POINT_WAIT_FRAME 50
#define SPEED_INCREASE_INTERVAL 1800  // 60fps * 30s = 1800 frames

// Ball
#define BALLRADIUS 10.0f
#define DEFAULT_BALL_SPEED 5.0f;
#define MAX_BOUNCE_ANGLE (PI/3)  // in radians, 60 degrees

// Player

#define PLAYER_SPEED 5.0f

static const Vector2 playerSize = {10.0f, 70.0f};


#endif //CRAYPONG_CONFIG_H
