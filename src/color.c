#include <stdio.h>
#include "color.h"

static const unsigned char INVALID_HEX = 16;

unsigned char toDecimal(const unsigned char hexChar) {
	if ('0' <= hexChar && hexChar <= '9') {
		return hexChar - '0';
	}
	if ('A' <= hexChar && hexChar <= 'F') {
		return hexChar - 'A' + ('9' - '0' + 1);
	}
	if ('a' <= hexChar && hexChar <= 'f') {
		return hexChar - 'a' + ('9' - '0' + 1);
	}
	return INVALID_HEX;
}

Color cl_parse_color(const unsigned char string[]) {
	Color color = {0, 0, 0, DEFAULT_ALPHA};
	Color* colorPtr = &color;
	if (string[0] != '#') {
		return color;
	}
	for (unsigned int index = 0; index < 4; index++) {
		unsigned char* address = ((unsigned char*) colorPtr) + index;
		const unsigned char valueLeft = toDecimal(string[index * 2 + 1]) << 4;
		if (valueLeft == INVALID_HEX) {
			break;
		}
		const unsigned char valueRight = toDecimal(string[index * 2 + 2]);
		if (valueRight == INVALID_HEX) {
			break;
		}
		unsigned char value = valueLeft | valueRight;
		*address = value;
	}
	return color;
}

unsigned int cl_get_red(const unsigned int color) {
	const Color colorStruct = *(Color*) &color;
	return colorStruct.r;
}

unsigned int cl_get_green(const unsigned int color) {
	const Color colorStruct = *(Color*) &color;
	return colorStruct.g;
}

unsigned int cl_get_blue(const unsigned int color) {
	Color colorStruct = *(Color*) &color;
	return colorStruct.b;
}

unsigned int cl_get_alpha(const unsigned int color) {
	Color colorStruct = *(Color*) &color;
	return colorStruct.a;
}
