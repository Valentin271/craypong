#ifndef CRAYPONG_TYPES_H
#define CRAYPONG_TYPES_H

#include "stdbool.h"

#include "raylib.h"


//--------------------------------------------------
// Types definitions
//--------------------------------------------------
typedef struct Player {
    Vector2 position;
    unsigned short score;
    bool colliding;
} Player;

typedef enum SCREEN {
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_PAUSE,
    SCREEN_POINT
} SCREEN;

typedef enum MODE {
    MODE_1PLAYER,
    MODE_2PLAYERS
} MODE;

#endif //CRAYPONG_TYPES_H
