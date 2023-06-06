#include "KN_Element.h"
#include "FLX_Container.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct KN_ElementStack {
	KN_Element* element;
	struct KN_ElementStack* next;
} KN_ElementStack;



static void render(KN_Bounds bounds, cairo_t* cr, double r, double g, double b){
  cairo_set_source_rgb(cr, r, g, b);
  cairo_rectangle(cr, bounds.x, bounds.y, bounds.w, bounds.h);
  cairo_fill(cr);
	printf("An element is drawn (%i, %i, %i, %i)\n",
		bounds.x, 
		bounds.y,
		bounds.x + bounds.w, 
		bounds.y + bounds.h
	);
}

int KN_DrawElement(KN_Element* el, cairo_t* cr) {
	if (el == NULL) return 1;

	KN_ElementStack* stack = malloc(sizeof(KN_ElementStack));
	stack->element = el;
	stack->next = NULL;

	while (stack != NULL) {
		render(stack->element->bounds, cr, 
			(double)(rand()%90)/100.0,
			(double)(rand()%90)/100.0, 
			(double)(rand()%90)/100.0
		);

		KN_ElementStack* last_node = stack;
		stack = stack->next;
		
		if (last_node->element->count > 0) {
			KN_Bounds* bounds = FLX_FlexSizesToBounds(
				&last_node->element->container, 
				&last_node->element->bounds, 
				last_node->element->count
			);

			for (int i = last_node->element->count-1; i >= 0; --i) {
				KN_ElementStack* new_node = malloc(sizeof(KN_ElementStack));
				last_node->element->children[i].bounds = bounds[i];
				new_node->element = &last_node->element->children[i];
				new_node->next = stack;
				stack = new_node;
			}

			free(bounds);
		}

		free(last_node);
	}
	return 0;
}