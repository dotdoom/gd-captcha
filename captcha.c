#include <gd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int rand_v(int range) {
	return rand() / (RAND_MAX / range);
}

#define VERA "/usr/local/lib/X11/fonts/bitstream-vera/Vera.ttf"

int main(int argc, char **argv) {
  gdImagePtr im;
  int black;
  int white;
  int i, err;
  int bb[8];
  char *s = argv[1];
  char s_c[2] = { 0 };
  srand(time(NULL));
  im = gdImageCreate(180, 60);
  /* Background color (first allocated) */
  white = gdImageColorAllocate(im, 255, 255, 255);
  black = gdImageColorAllocate(im, 0, 0, 0);
  gdImageSetThickness(im, 2);
  for (i = 0; i < strlen(s); ++i) {
	  s_c[0] = s[i];
	  gdImageStringFT(im, bb, black, VERA, 32., M_PI / 8 * ((double)rand() / (RAND_MAX / 2) - 1), 10 + i * 23, 40, s_c);
  }
  for (i = 0; i < 3; ++i) {
	  gdImageLine(im, rand_v(20) + 5,
			  rand_v(50) + 5,
			  rand_v(20) + 155,
			  rand_v(50) + 5,
			  i ? white : black);
  }
  gdImagePng(im, stdout);
  gdImageDestroy(im);
  return 0;
}
