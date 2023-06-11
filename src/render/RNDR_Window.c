#include "RNDR_Window.h"
#include <stdlib.h>

RNDR_Window RNDR_InitWindow(
	Display* dpy,
	int width,
	int height
) {
	RNDR_Window win = {0};
	win.dpy = dpy;
	win.width = width;
	win.height = height;

  Window root;
  root = DefaultRootWindow(win.dpy);

  win.scr = DefaultScreen(win.dpy);
  win.win = XCreateSimpleWindow(
    win.dpy, root, 
    0, 0, 
    width, height, 0,
    BlackPixel(dpy, win.scr), 
    BlackPixel(dpy, win.scr)
  );

  win.quit_code = XKeysymToKeycode(win.dpy, XStringToKeysym("Q"));

  XSelectInput(
    win.dpy, win.win,
    KeyPressMask | StructureNotifyMask | ExposureMask
  );

  XMapWindow(win.dpy, win.win);
	return win;
}