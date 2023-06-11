#ifndef _RNDR_WINDOW
#include <X11/Xlib.h>

typedef struct RNDR_Window {
  Display* dpy;
  int scr;
  Window win;
  GC gc;
  int width;
  int height;
  KeyCode quit_code;
} RNDR_Window;

RNDR_Window RNDR_InitWindow(
	Display* dpy,
	int width,
	int height
);

#define _RNDR_WINDOW
#endif
