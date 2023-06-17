#ifndef _KN_COLOR_UTILS
#define _KN_COLOR_UTILS
#include "KN_Color.h"

KN_Color HSLAToRGBA(double h, double s, double l, double a);

#define KN_RGB(r, g, b) (KN_Color){r, g, b, 1}
#define KN_RGBA(r, g, b, a) (KN_Color){r, g, b, a}
#define KN_RGB_HEX(value)\
(KN_Color) {\
	.r = (double)((value >> 16) & 0xFF) / 255.0,\
	.g = (double)((value >> 8)  & 0xFF) / 255.0,\
	.b = (double)((value >> 0)  & 0xFF) / 255.0,\
	.a = 1\
}
#define KN_RGBA_HEX(value)\
(KN_Color) {\
	.r = (double)((value >> 24) & 0xFF) / 255.0,\
	.g = (double)((value >> 16) & 0xFF) / 255.0,\
	.b = (double)((value >> 8)  & 0xFF) / 255.0,\
	.a = (double)((value >> 0)  & 0xFF) / 255.0,\
}
#define KN_HSL(h, s, l) HSLAToRGBA(h, s, l, 1)
#define KN_HSLA(h, s, l, a) HSLAToRGBA(h, s, l, a)

#endif