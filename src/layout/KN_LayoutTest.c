#include "KN_Element.h"
#include <stdlib.h>

#define KNTRFLXSIZE sizeof(KN_FlexSize)
#define ELSIZE sizeof(KN_Element)

int main(void) {
	KN_Element window = {
		.bounds = {
			.x = 0,
			.y = 0,
			.h = 256,
			.w = 256
		},
		.children = malloc(4 * ELSIZE),
		.count = 4
	};

	KN_FlexSize sizes1[4] = {
		{KN_UnitPX, 128},
		{KN_UnitAUTO, 0},
		{KN_UnitAUTO, 0},
		{KN_UnitPERCENT, 12.5}
	};
	KN_FlexSize autosize[1] = {
		{KN_UnitAUTO, 0}
	};
	KN_FlexSize v64[1] = {
		{KN_UnitPX, 64}
	};

	window.container = FLX_ContainerNew(
		FLX_ROW, 
		sizes1, 
		FLX_ALIGN_BEGIN, 
		4, 
		autosize, 
		FLX_ALIGN_BEGIN, 
		1, 
		FLX_REPEAT_LAST
	);
	window.children[3].children = malloc(2 * ELSIZE);
	window.children[3].count = 2;
	window.children[3].container = FLX_ContainerNew(
		FLX_ROW, 
		autosize, 
		FLX_ALIGN_BEGIN, 
		1, 
		v64, 
		FLX_ALIGN_BEGIN, 
		1, 
		FLX_REPEAT_LAST
	);

	

	KN_DrawElement(&window);
	free(window.children[3].children);
	free(window.children);
}
