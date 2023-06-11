#include "FLX_Container.h"
#include "KN_Sizing.h"
#include <stdio.h>
#include <stdlib.h>

KN_FlexSize FLX_AUTOSIZE = { KN_UNIT_AUTO, 0 };

FLX_Container FLX_ContainerAuto(
	FLX_Direction direction,
	FLX_Align main_align,
	FLX_Align cross_align		
) {
	FLX_Container container = {0};
	container.direction = direction;
	
	container.main.layout = &FLX_AUTOSIZE;
	container.main.align = main_align;
	container.main.count = 1;

	container.cross.layout = &FLX_AUTOSIZE;
	container.cross.align = cross_align;
	container.cross.count = 1;

	container.repeat_mode = FLX_REPEAT_LAST;
	return container;
}

FLX_Container FLX_ContainerNew(
	FLX_Direction direction,
	KN_FlexSize*  main,
	FLX_Align 	  main_align,
	int 				  main_count,
	KN_FlexSize*  cross,
	FLX_Align     cross_align,
	int           cross_count,
	FLX_Repeat    repeat_mode
) {
	FLX_Container container = {0};
	container.direction  = direction;
	
	container.main.layout = main;
	container.main.align = main_align;
	container.main.count = main_count;

	container.cross.layout = cross;
	container.cross.align = cross_align;
	container.cross.count = cross_count;

	container.repeat_mode = repeat_mode;
	return container;
}

int FLX_FlexSizeToAbsolute(
	KN_FlexSize size, 
	double container_size, 
	int auto_width
) {
	switch (size.unit) {
  	case KN_UNIT_AUTO:
			return auto_width;
		case KN_UNIT_PX:
			return size.value;
		case KN_UNIT_PERCENT:
			return size.value * 0.01 * container_size; 
		default:
			fprintf(stderr, "BAD FLEXSIZE UNIT\n");
			exit(1);
  }
}

#define KN_MIN(a, b) (a < b) ? a : b
#define MAIN_COORD(bound)  (*((c->direction == FLX_ROW) ? &(bound)->x : &(bound)->y))
#define MAIN_SIZE(bound)   (*((c->direction == FLX_ROW) ? &(bound)->w : &(bound)->h))
#define CROSS_COORD(bound) (*((c->direction == FLX_ROW) ? &(bound)->y : &(bound)->x))
#define CROSS_SIZE(bound)  (*((c->direction == FLX_ROW) ? &(bound)->h : &(bound)->w))
KN_Bounds* FLX_FlexSizesToBounds(
	FLX_Container* c,
	KN_Bounds* parent_bounds, 
	int child_count
) {
	KN_Bounds* bounds = malloc(child_count * sizeof(KN_Bounds));

	KN_FlexSize last_main  = c->main.layout[c->main.count - 1];
	KN_FlexSize last_cross = c->cross.layout[c->cross.count - 1];
	
	int auto_count = 0;
	int* auto_indices = malloc(child_count * sizeof(int));
	{ // count auto elements in main axis
		int min_count = KN_MIN(child_count, c->main.count);
		
		for (int i = 0; i < min_count; ++i) {
			if (c->main.layout[i].unit == KN_UNIT_AUTO) {
				auto_indices[auto_count] = i;
				++auto_count;
			}
		}
		
		if (last_main.unit == KN_UNIT_AUTO) {
			while (min_count < child_count) {
				auto_indices[auto_count] = min_count;
				++auto_count;
				++min_count; 
			}
		}
	}

	double free_space = MAIN_SIZE(parent_bounds);
	{ // evaluate free space, set main sizes for non auto elements
		int min_count = KN_MIN(child_count, c->main.count);
		for (int i = 0; i < min_count; ++i) {
			if (c->main.layout[i].unit != KN_UNIT_AUTO) {
				MAIN_SIZE(&bounds[i]) = FLX_FlexSizeToAbsolute(
					c->main.layout[i], 
					MAIN_SIZE(parent_bounds),
					0 
				);
				free_space -= MAIN_SIZE(&bounds[i]);
			}
		}

		if (last_main.unit != KN_UNIT_AUTO) {
			double size = FLX_FlexSizeToAbsolute(last_main, MAIN_SIZE(parent_bounds), 0);
			for (int i = min_count; i < child_count; ++i) {
				MAIN_SIZE(&bounds[i]) = size;
				free_space -= size;
			}
		}
	}
	
	double main_auto_size = (auto_count > 0) ? free_space / auto_count : 0;
	double cross_auto_size = CROSS_SIZE(parent_bounds);

	for (int i = 0; i < auto_count; ++i) {
		MAIN_SIZE(&bounds[auto_indices[i]]) = main_auto_size;
	}
	free(auto_indices);


	MAIN_COORD(&bounds[0]) = MAIN_COORD(parent_bounds);
	if (auto_count == 0) {
		if (c->main.align == FLX_ALIGN_CENTER) {
			MAIN_COORD(&bounds[0]) += free_space / 2;
		} else if (c->main.align == FLX_ALIGN_END) {
    	MAIN_COORD(&bounds[0]) += free_space;
    }
	}
	
	for (int i = 0; i < child_count - 1; ++i) {
		MAIN_COORD(&bounds[i+1]) = MAIN_COORD(&bounds[i]) + MAIN_SIZE(&bounds[i]);
	}

	int min_count = KN_MIN(child_count, c->cross.count);
	for (int i = 0; i < min_count; ++i) {
		CROSS_SIZE(&bounds[i]) = FLX_FlexSizeToAbsolute(
			c->cross.layout[i], 
			CROSS_SIZE(parent_bounds), 
			cross_auto_size
		);
		CROSS_COORD(&bounds[i]) = CROSS_COORD(parent_bounds);
		switch (c->cross.align) {
    	case FLX_ALIGN_BEGIN:
				break;
			case FLX_ALIGN_CENTER:
				CROSS_COORD(&bounds[i]) += (CROSS_SIZE(parent_bounds) - CROSS_SIZE(&bounds[i])) / 2;
				break;
			case FLX_ALIGN_END:
				CROSS_COORD(&bounds[i]) += CROSS_SIZE(parent_bounds) - CROSS_SIZE(&bounds[i]);
				break;
    }
	}
	for (int i = min_count; i < child_count; ++i) {
		CROSS_SIZE(&bounds[i]) = FLX_FlexSizeToAbsolute(
			last_cross,
			CROSS_SIZE(parent_bounds), 
			cross_auto_size
		);
		CROSS_COORD(&bounds[i]) = CROSS_COORD(parent_bounds);
		switch (c->cross.align) {
    	case FLX_ALIGN_BEGIN:
				break;
			case FLX_ALIGN_CENTER:
				CROSS_COORD(&bounds[i]) += (CROSS_SIZE(parent_bounds) - CROSS_SIZE(&bounds[i])) / 2;
				break;
			case FLX_ALIGN_END:
				CROSS_COORD(&bounds[i]) += CROSS_SIZE(parent_bounds) - CROSS_SIZE(&bounds[i]);
				break;
    }
	}

	return bounds;
};
