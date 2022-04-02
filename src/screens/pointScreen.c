#include "../game.h"

void UpdatePointScreen()
{
    if (--pauseFrames <= 0) {
        screen = SCREEN_POINT;
    }
}

void DrawPointScreen()
{

}