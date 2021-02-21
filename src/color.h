#pragma once

static const unsigned char DEFAULT_ALPHA = 255;

typedef struct {
	unsigned char r, g, b, a;
} Color;

Color cl_parse(const unsigned char string[]);

unsigned int cl_red(const unsigned int color);

unsigned int cl_green(const unsigned int color);

unsigned int cl_blue(const unsigned int color);

unsigned int cl_alpha(const unsigned int color);
