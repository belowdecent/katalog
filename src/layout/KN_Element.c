#include "KN_Element.h"
#include "FLX_Container.h"
#include <stdio.h>
#include <stdlib.h>

void render(KN_Bounds bounds){
	printf("An element is drawn (%i, %i, %i, %i)\n",
		bounds.x, 
		bounds.y,
		bounds.x + bounds.w, 
		bounds.y + bounds.h
	);
}

int KN_DrawElement(KN_Element* el) {
	render(el->bounds);

	if (el->count > 0) {
		KN_Bounds* bounds = FLX_FlexSizesToBounds(&el->container, &el->bounds, el->count);

		for (int i = 0; i < el->count; ++i) {
			el->children[i].bounds = bounds[i];
			if (KN_DrawElement(&el->children[i])) {
				fprintf(stderr, "Failed!");
				exit(1);
			};
		}
		free(bounds);
	}

	return 0;
}