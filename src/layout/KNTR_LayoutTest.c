#include "KNTR_Element.h"
#include "KNTR_Sizing.h"
#include <stdlib.h>

#define KNTRFLXSIZE sizeof(KNTR_FlexSize)
#define ELSIZE sizeof(KNTR_Element)

int main(void) {
	KNTR_Element window = {
		.bounds = {
			.x = 0,
			.y = 0,
			.h = 256,
			.w = 256
		},
		.child_layout_h = malloc(4 * KNTRFLXSIZE),
		.child_layout_v = malloc(4 * KNTRFLXSIZE),
		.children = malloc(4 * ELSIZE),
		.count = 4
	};

	window.child_layout_h[0].unit = KNTR_UnitPX;
	window.child_layout_h[0].value = 128;
	window.child_layout_h[1].unit = KNTR_UnitAUTO;
	window.child_layout_h[2].unit = KNTR_UnitAUTO;
	window.child_layout_h[3].unit = KNTR_UnitPERCENT;
	window.child_layout_h[3].value = 0.125;
	window.children[3].child_layout_h = malloc(2 * KNTRFLXSIZE);
	window.children[3].child_layout_v = malloc(2 * KNTRFLXSIZE);
	window.children[3].children = malloc(2 * ELSIZE);
	window.children[3].count = 2;

	for (int i = 0; i < 4; ++i) {
		window.child_layout_v[i].unit = KNTR_UnitAUTO;
	}

	for (int i = 0; i < 2; ++i) {
		window.children[3].child_layout_h[i].unit = KNTR_UnitAUTO;
		window.children[3].child_layout_v[i].unit = KNTR_UnitPX;
		window.children[3].child_layout_v[i].value = 64;
	}

	KNTR_DrawElement(&window);

	free(window.children[3].children);
	free(window.children[3].child_layout_h);
	free(window.children[3].child_layout_v);

	free(window.children);
	free(window.child_layout_h);
	free(window.child_layout_v);
}
