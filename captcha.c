#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <gd.h>

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

/*
 * Generate a random number in range [0..range].
 */
int range_random(int range) {
	if (range) {
		return rand() / (RAND_MAX / range);
	} else {
		return 0;
	}
}

/*
 * Generate a random number in range [-1..1].
 */
double norm_random() {
	return rand() / (double)RAND_MAX * 2 - 1;
}

int main(int argc, char **argv) {
	gdImagePtr captcha_image = NULL;
	int background_color, font_color, font_size, char_step, i;
	int brect[8]; // Bounds rect (set by gdImageStringFT).

	char current_char[2] = { 0 };
	const char *captcha_text = argc > 1 ? argv[1] : "beAtLes";
	char *font_error = 0;

	srand(time(NULL));
	char_step = (CAPTCHA_WIDTH - (CAPTCHA_MARGIN_X * 2)) / strlen(captcha_text);
	font_size = CAPTCHA_HEIGHT - 2 * CAPTCHA_MARGIN_Y;

	captcha_image = gdImageCreate(CAPTCHA_WIDTH, CAPTCHA_HEIGHT);

	// First allocated color (white) is set as a background.
	background_color = gdImageColorAllocate(captcha_image, 255, 255, 255);

	// R, G, B font color (black).
	font_color = gdImageColorAllocate(captcha_image, 0, 0, 0);
	for (i = 0; *captcha_text; ++captcha_text, ++i) {
		current_char[0] = *captcha_text;
		font_error = gdImageStringFT(captcha_image, brect, font_color, CAPTCHA_FONT_LOCATION,
				font_size, CAPTCHA_CHAR_ANGLE * norm_random(),
				CAPTCHA_MARGIN_X + (i * char_step), CAPTCHA_HEIGHT - CAPTCHA_MARGIN_Y,
				current_char);
		if (font_error) {
			fprintf(stderr, "Failed to render char '%c': %s\n", *captcha_text, font_error);
		}
	}

	gdImageSetThickness(captcha_image, CAPTCHA_STRIKE_WIDTH);
	for (i = 0; i < CAPTCHA_STRIKE_LINES; ++i) {
		gdImageLine(captcha_image,
				range_random(CAPTCHA_MARGIN_X),
				range_random(CAPTCHA_HEIGHT),
				range_random(CAPTCHA_MARGIN_X) + CAPTCHA_WIDTH - CAPTCHA_MARGIN_X,
				range_random(CAPTCHA_HEIGHT),
				i % 2 ? background_color : font_color);
	}
	gdImagePng(captcha_image, stdout);
	gdImageDestroy(captcha_image);
	return 0;
}
