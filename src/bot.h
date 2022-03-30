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
Movement bot(Vector2 ballPos, Vector2 botPos)
{
    // If ball is too much on the left
    // or ball is not aligned with player (20px margin)
    if (ballPos.x < GetScreenWidth()/3 || (ballPos.y > botPos.y + 20) && (ballPos.y < botPos.y + playerSize.y - 20)) {
        return NONE;
    }

    if (ballPos.y < botPos.y + playerSize.y/2) {
        return UP;
    } else if (ballPos.y > botPos.y + playerSize.y/2) {
        return DOWN;
    }

    return NONE;
}

#endif //CRAYPONG_BOT_H
