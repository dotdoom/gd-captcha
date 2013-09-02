
#include "libcaptcha.h"

int main(int argc, char **argv) {
	char current_char[2] = { 0 };
	const char *captcha_text = argc > 1 ? argv[1] : "beAtLes";
	char *font_error = 0;
	
	render(captcha_text, stdout);
	
	return 0;
}
