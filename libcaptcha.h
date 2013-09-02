#ifndef LIBCAPTCHA_H
#define LIBCAPTCHA_H

#include <stdio.h>

// WxH, pixels.
#define CAPTCHA_WIDTH 180
#define CAPTCHA_HEIGHT 60

// Margins to make captcha more readable.
#define CAPTCHA_MARGIN_X (CAPTCHA_WIDTH * 0.05)
#define CAPTCHA_MARGIN_Y (CAPTCHA_HEIGHT * 0.25)

/*
 * The Liberation(tm) version 2.00.0 onward are Licensed under the SIL Open Font License, Version 1.1.
 */
#define CAPTCHA_FONT_LOCATION "./liberation.ttf"

// Will be striked through with X random lines, each X pixels thick.
#define CAPTCHA_STRIKE_WIDTH 2
#define CAPTCHA_STRIKE_LINES 3

// Maximum angle to turn a single char (randomly).
#define CAPTCHA_CHAR_ANGLE (M_PI/8)

int range_random(int range);

double norm_random();

void render(const char *captcha_text, FILE *handle);

#endif