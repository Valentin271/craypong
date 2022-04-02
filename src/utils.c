#include "utils.h"

int TextCenterX(const char *text, int fontsize)
{
    return GetScreenWidth()/2 - MeasureText(text, fontsize)/2;
}

int TextCenterY(int fontsize)
{
    return GetScreenHeight()/2 - fontsize/2;
}

void InitBallDirection(Vector2 *speed, float angle)
{
    speed->x = cosf(angle)*ballSpeed;
    speed->y = sinf(angle)*ballSpeed;
}

void CenterPlayerY(Player *player)
{
    player->position.y = GetScreenHeight()/2 - playerSize.y/2;
}