#pragma once

static const unsigned char DEFAULT_ALPHA = 255;

typedef struct {
	unsigned char r, g, b, a;
} Color;

Color cl_parse(unsigned char string[]);

unsigned int cl_red(unsigned int color);

unsigned int cl_green(unsigned int color);

unsigned int cl_blue(unsigned int color);

unsigned int cl_alpha(unsigned int color);
