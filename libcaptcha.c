#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gd.h>

#include "libcaptcha.h"

/*
 * Generate a random number in range [0..range].
 */
static int _range_random(int range) {
	if (range) {
		return rand() / (RAND_MAX / range);
	} else {
		return 0;
	}
}

/*
 * Generate a random number in range [-1..1].
 */
static double _norm_random() {
	return rand() / (double)RAND_MAX * 2 - 1;
}

void render(const char *captcha_text, FILE *handle) {
	gdImagePtr captcha_image = NULL;
	int background_color, font_color, font_size, char_step, i;
	int brect[8]; // Bounds rect (set by gdImageStringFT).

	char current_char[2] = { 0 };
	char *font_error = NULL;

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
				font_size, CAPTCHA_CHAR_ANGLE * _norm_random(),
				CAPTCHA_MARGIN_X + (i * char_step), CAPTCHA_HEIGHT - CAPTCHA_MARGIN_Y,
				current_char);
		if (font_error) {
			fprintf(stderr, "Failed to render char '%c': %s\n", *captcha_text, font_error);
		}
	}

	gdImageSetThickness(captcha_image, CAPTCHA_STRIKE_WIDTH);
	for (i = 0; i < CAPTCHA_STRIKE_LINES; ++i) {
		gdImageLine(captcha_image,
				_range_random(CAPTCHA_MARGIN_X),
				_range_random(CAPTCHA_HEIGHT),
				_range_random(CAPTCHA_MARGIN_X) + CAPTCHA_WIDTH - CAPTCHA_MARGIN_X,
				_range_random(CAPTCHA_HEIGHT),
				i % 2 ? background_color : font_color);
	}
	gdImagePng(captcha_image, handle);
	gdImageDestroy(captcha_image);
}
