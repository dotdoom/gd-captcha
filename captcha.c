#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "libcaptcha.h"

extern uint8_t data[]     asm("_binary_captcha_ttf_start");
extern uint8_t data_end[] asm("_binary_captcha_ttf_end");

int main(int argc, char **argv) {
	FILE *font = NULL;
	char *font_name = NULL;
	const char *captcha_text = argc > 1 ? argv[1] : "beAtLes";

	srand(time(NULL));

	font_name = tmpnam(NULL);
	font = fopen(font_name, "w");
	if (font) {
		if (!fwrite(data, data_end - data, 1, font)) {
			perror("fwrite");
		}

		fclose(font);

		render(captcha_text, stdout, font_name);
		unlink(font_name);

		return 0;
	} else {
		perror("fopen");
	}

	return 1;
}
