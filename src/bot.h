#ifndef CRAYPONG_BOT_H
#define CRAYPONG_BOT_H

#include "raylib.h"
#include "config.h"

typedef enum Movement {
    UP = -1,
    DOWN = 1,
    NONE = 0,
} Movement;

/**
 * Compute the movement the bot should do.
 *
 * @param ballPos Ball position
 * @param botPos Bot position
 * @return The movement that should be done, UP, DOWN or NONE.
 */
Movement bot(Vector2 ballPos, Vector2 botPos);

#endif //CRAYPONG_BOT_H
