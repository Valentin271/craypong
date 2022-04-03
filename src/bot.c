#include "bot.h"

Movement bot(Vector2 ballPos, Vector2 botPos)
{
    // If ball is too much on the left
    // or ball is not aligned with player (20px margin)
    if (ballPos.x < GetScreenWidth()/3 || ((ballPos.y > botPos.y + 20) && (ballPos.y < botPos.y + playerSize.y - 20))) {
        return NONE;
    }

    if (ballPos.y < botPos.y + playerSize.y/2) {
        return UP;
    } else if (ballPos.y > botPos.y + playerSize.y/2) {
        return DOWN;
    }

    return NONE;
}