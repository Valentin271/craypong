#ifndef CRAYPONG_UTILS_H
#define CRAYPONG_UTILS_H

#include "math.h"

#include "raylib.h"

#include "config.h"
#include "types.h"

extern float ballSpeed;

/**
 * Computes the screen center in X for text with fontsize.
 *
 * @param text Text to center
 * @param fontsize Size of the font
 * @return The X coordinate to center the text
 */
int TextCenterX(const char *text, int fontsize);

/**
 * Computes the screen center in Y for fontsize.
 *
 * @param fontsize Size of the font
 * @return The Y coordinate to center the text
 */
int TextCenterY(int fontsize);

/**
 * Initialize the ball direction with the given angle in radians.
 *
 * @param speed current ball direction
 * @param angle Angle to init the ball direction
 */
void InitBallDirection(Vector2 *dir, float angle);

/**
 * Center the player on Y axis.
 *
 * @param player Player to center
 */
void CenterPlayerY(Player *player);

#endif //CRAYPONG_UTILS_H
