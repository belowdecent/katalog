#include "KNTR_Element.h"
#include "KNTR_Sizing.h"
#include <stdio.h>
#include <stdlib.h>

void render(KNTR_Bounds bounds){
	printf("An element is drawn (%i, %i, %i, %i)\n",
		bounds.x, 
		bounds.y,
		bounds.x + bounds.w, 
		bounds.y + bounds.h
	);
}

int KNTR_DrawElement(KNTR_Element* el) {
	render(el->bounds);
	if (el->count != 0) {
			KNTR_Bounds* children_bounds = KNTR_FlexSizesToBounds(
			el->bounds, 
			el->child_layout_h, 
			el->child_layout_v,
			el->count 
		);

		for (int i = 0; i < el->count; ++i) {
			el->children[i].bounds = children_bounds[i];
			if (KNTR_DrawElement(&el->children[i])) {
				fprintf(stderr, "Failed!");
				exit(1);
			};
		}
		free(children_bounds);
	}

	return 0;
}