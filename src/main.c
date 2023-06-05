#include "cairo.h"
#include "pango/pango-layout.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <pango/pangocairo.h>
#include <cairo/cairo-xlib.h>
#include <stdio.h>

#define RADIUS 0
#define N_WORDS 10
#define FONT "Inter 27"

typedef struct {
  Display* dpy;
  int scr;
  Window win;
  GC gc;
  int width;
  int height;
  KeyCode quit_code;
} KNTR_Window;

static void draw_text(cairo_t* cr) {
  PangoLayout* layout;
  PangoFontDescription* desc;
  int i;
  /* Center coordinates on the middle of the region we are drawing */
  cairo_translate(cr, RADIUS, RADIUS);
  /* Create a PangoLayout, set the font and text */
  layout = pango_cairo_create_layout(cr);

  pango_layout_set_text(layout, "Text", -1);
  desc = pango_font_description_from_string(FONT);
  pango_layout_set_font_description(layout, desc);
  pango_font_description_free(desc);
  /* Gradient from red at angle == 60 to blue at angle == 240 */
  cairo_set_source_rgb(cr, 0.5, 0, 0.5);

  pango_cairo_show_layout(cr, layout);
  cairo_translate(cr, 50, 50);
  pango_layout_set_text(layout, "Gay", -1);
  pango_cairo_show_layout(cr, layout);


  /* free the layout object */
  g_object_unref(layout);
}

static void KNTR_WindowInit(KNTR_Window* win) {
  Window root;

  win->width = 512;
  win->height = 512;

  root = DefaultRootWindow(win->dpy);
  win->scr = DefaultScreen(win->dpy);
  win->win = XCreateSimpleWindow(
    win->dpy, root, 
    0, 0, 
    win->width, win->height, 0,
    BlackPixel(win->dpy, win->scr), 
    BlackPixel(win->dpy, win->scr)
  );

  win->quit_code = XKeysymToKeycode(win->dpy, XStringToKeysym("Q"));

  XSetWindowAttributes set_attr;
  set_attr.override_redirect = True;
  XChangeWindowAttributes(win->dpy, win->win, CWOverrideRedirect, &set_attr);

  XSelectInput(
    win->dpy, win->win,
    KeyPressMask | StructureNotifyMask | ExposureMask
  );

  XMapWindow(win->dpy, win->win);
  XGrabKeyboard(win->dpy, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
}

static void KNTR_WindowDestroy(KNTR_Window* win) {
  XDestroyWindow(win->dpy, win->win);
}

static void win_draw(KNTR_Window* win) {
  cairo_surface_t* surface;
  cairo_t* cr;

  Visual* visual = DefaultVisual(win->dpy, DefaultScreen(win->dpy));
  XClearWindow(win->dpy, win->win);

  surface = cairo_xlib_surface_create(
    win->dpy, 
    win->win, 
    visual, 
    win->width, win->height
  );
  cr = cairo_create(surface);

  cairo_set_source_rgb(cr, 1, 1, 1);

  cairo_save(cr);

  draw_text(cr);
  cairo_set_source_rgb(cr, 1, 0, 1);
  cairo_rectangle(cr, 20, 20, 150, 150);
  cairo_fill(cr);

  if (cairo_status(cr)) {
    printf("Something malicious is brewing: %s\n", 
      cairo_status_to_string(cairo_status(cr)));
  }

  cairo_destroy(cr);
  cairo_surface_destroy(surface);

}

static void win_handle_events(KNTR_Window* win) {
  XEvent xev;

  while (1) {
    XNextEvent(win->dpy, &xev);

    switch (xev.type) {
      case KeyPress: 
        {
          XKeyEvent* kev = &xev.xkey;
          if (kev->keycode == win->quit_code) {
            return;
          }
        }
        break;
      case ConfigureNotify:
        {
          XConfigureEvent* cev = &xev.xconfigure;

          win->width = cev->width;
          win->height = cev->height;
        }
        break;
      case Expose:
        {
          XExposeEvent* eev = &xev.xexpose;
          if (eev->count == 0) {
            win_draw(win);
          }
        }
        break;
    }
  }
}

int main(void) {
  KNTR_Window win;
  win.dpy = XOpenDisplay(0);

  if (win.dpy == NULL) {
    fprintf(stderr, "Failed to open display\n");
    return 1;
  }

  KNTR_WindowInit(&win);
  win_draw(&win);
  win_handle_events(&win);
  KNTR_WindowDestroy(&win);

  XCloseDisplay(win.dpy);  

  return 0;
}
