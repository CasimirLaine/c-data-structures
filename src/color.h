#pragma once

static const unsigned char DEFAULT_ALPHA = 255;

typedef struct {
	unsigned char r, g, b, a;
} Color;

Color cl_parse_color(unsigned char string[]);

unsigned int cl_get_red(unsigned int color);

unsigned int cl_get_green(unsigned int color);

unsigned int cl_get_blue(unsigned int color);

unsigned int cl_get_alpha(unsigned int color);
