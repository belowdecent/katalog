#include "cairo.h"
#include "layout/FLX_Axis.h"
#include "layout/FLX_Container.h"
#include "layout/KN_ColorUtils.h"
#include "layout/KN_Sizing.h"
#include "pango/pango-layout.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <pango/pangocairo.h>
#include <cairo/cairo-xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "layout/KN_Element.h"
#include "render/RNDR_Window.h"

#define RADIUS 0
#define N_WORDS 10
#define FONT "Inter 27"

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

KN_Element* my_stuff() {
  KN_Element* window = malloc(sizeof(KN_Element));

	window->bounds.x = 0;
	window->bounds.y = 0;
	window->bounds.w = 256;
	window->bounds.h = 256;
  window->children = calloc(4, sizeof(KN_Element));
	window->count = 4;
  window->padding = KN_PADDING_ALL(KN_UNIT_PX, 5);
  window->color = KN_RGB_HEX(0x4FC3F7);

  window->children[0].color = KN_RGB_HEX(0xF50057);
  window->children[1].color = KN_RGB_HEX(0xD500F9);
  window->children[2].color = KN_RGB_HEX(0x651FFF);
  window->children[3].color = KN_RGB_HEX(0x1A237E);

  window->children[3].children = calloc(3, sizeof(KN_Element));
  window->children[3].count = 3;
  window->children[3].padding = KN_PADDING_BLOCK(KN_UNIT_PERCENT, 5);

  window->container = (FLX_Container){
    .direction = FLX_ROW,
    .repeat_mode = FLX_REPEAT_LAST,
    .main = { .align = FLX_ALIGN_BEGIN },
    .cross = { .align = FLX_ALIGN_END },
  };
  FLX_SetAxis(&window->container.main, 4, (KN_FlexSize[]){
		{KN_UNIT_PX, 128},
		{KN_UNIT_AUTO, 0},
		{KN_UNIT_AUTO, 0},
		{KN_UNIT_PERCENT, 12.5}
  });
  FLX_SetAxis(&window->container.cross, 4, (KN_FlexSize[]){
    {KN_UNIT_PERCENT, 100},
    {KN_UNIT_PERCENT, 50},
    {KN_UNIT_PERCENT, 25},
    {KN_UNIT_PERCENT, 75},
  });

  KN_Element* el = &window->children[3];
  el->container = (FLX_Container){
    .direction = FLX_COLUMN,
    .repeat_mode = FLX_REPEAT_LAST,
    .main = { .align = FLX_ALIGN_CENTER },
    .cross = { .align = FLX_ALIGN_CENTER },
  };
  FLX_SetAxis(&el->container.main, 1, (KN_FlexSize[]){
		{KN_UNIT_AUTO, 0},
  });
  FLX_SetAxis(&el->container.cross, 1, (KN_FlexSize[]){
		{KN_UNIT_PX, 10}
  });

  el->children[0].color = KN_RGB_HEX(0xFF80AB);
  el->children[1].color = KN_RGB_HEX(0xEA80FC);
  el->children[2].color = KN_RGB_HEX(0xB388FF);


  return window;
}

static void win_draw(RNDR_Window* win, KN_Element* my_stuff) {
  printf("Drawing: \n");
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

  KN_DrawElement(my_stuff, cr);
  if (cairo_status(cr)) {
    printf("Something malicious is brewing: %s\n", 
      cairo_status_to_string(cairo_status(cr)));
  }

  cairo_destroy(cr);
  cairo_surface_destroy(surface);
}

static void win_handle_events(RNDR_Window* win, KN_Element* my_stuff) {
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
            win_draw(win, my_stuff);
          }
        }
        break;
    }
  }
}

int main(void) {
  RNDR_Window win = RNDR_InitWindow(XOpenDisplay(0), 512, 512);
  if (win.dpy == NULL) {
    fprintf(stderr, "Failed to open display\n");
    return 1;
  }

  KN_Element* thing = my_stuff();
  win_draw(&win, thing);
  win_handle_events(&win, thing);
  XDestroyWindow(win.dpy, win.win);
  XCloseDisplay(win.dpy);  

  return 0;
}
