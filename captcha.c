#include <time.h>
#include <stdlib.h>

#include "libcaptcha.h"

int main(int argc, char **argv) {
	const char *captcha_text = argc > 1 ? argv[1] : "beAtLes";

	srand(time(NULL));

	render(captcha_text, stdout);

	return 0;
}
