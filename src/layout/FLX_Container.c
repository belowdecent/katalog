#include "FLX_Container.h"
#include "KN_Sizing.h"
#include <stdio.h>
#include <stdlib.h>

KN_FlexSize FLX_AUTOSIZE = { KN_UnitAUTO, 0 };

FLX_Container FLX_ContainerAuto(
	FLX_Direction direction,
	FLX_Align main_align,
	FLX_Align cross_align		
) {
	FLX_Container container = {0};
	container.direction = direction;
	
	container.main = &FLX_AUTOSIZE;
	container.main_align = main_align;
	container.main_count = 1;

	container.cross = &FLX_AUTOSIZE;
	container.cross_align = cross_align;
	container.cross_count = 1;

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
	
	container.main = main;
	container.main_align = main_align;
	container.main_count = main_count;

	container.cross = cross;
	container.cross_align = cross_align;
	container.cross_count = cross_count;

	container.repeat_mode = repeat_mode;
	return container;
}

int FLX_FlexSizeToAbsolute(KN_FlexSize size, int container_size, int auto_width) {
	switch (size.unit) {
  	case (KN_UnitAUTO):
			return auto_width;
		case (KN_UnitPX):
			return (int)size.value;
		case (KN_UnitPERCENT):
			return (int)(size.value * 0.01 * container_size); 
		default:
			fprintf(stderr, "BAD FLEXSIZE UNIT\n");
			exit(1);
  }
}

#define KN_MIN(a, b) (a < b) ? a : b
KN_Bounds* FLX_FlexSizesToBounds(
	FLX_Container* c, 
	KN_Bounds* parent_bounds, 
	int child_count
) {
	KN_Bounds* bounds = malloc(child_count * sizeof(KN_Bounds));
	int* auto_indices = malloc(child_count * sizeof(int));
	int auto_count = 0;

	// Main Axis START, Cross Axis START, Direction ROW, RepeatMode LAST
	KN_FlexSize last_main  = c->main[c->main_count - 1];
	KN_FlexSize last_cross = c->cross[c->cross_count - 1];

	double free_space = parent_bounds->w;
	int min_count = KN_MIN(child_count, c->main_count);
	
	for (int i = 0; i < min_count; ++i) {
		if (c->main[i].unit == KN_UnitAUTO) {
			auto_indices[auto_count] = i;
			++auto_count; 
		} else {
			bounds[i].w = FLX_FlexSizeToAbsolute(c->main[i], parent_bounds->w, 0);
			free_space -= bounds[i].w;
		}
	}
	
	while (min_count < child_count) {
		if (last_main.unit == KN_UnitAUTO) {
			auto_indices[auto_count] = min_count;
			++auto_count; 
		} else {
			bounds[min_count].w = FLX_FlexSizeToAbsolute(last_main, parent_bounds->w, 0);
			free_space -= bounds[min_count].w;
		}

		++min_count;
	}
	
	double main_auto_size = (auto_count > 0) ? free_space / auto_count : 0;
	int cross_auto_size = parent_bounds->h;

	for (int i = 0; i < auto_count; ++i) {
		bounds[auto_indices[i]].w = main_auto_size;
	}

	bounds[0].x = parent_bounds->x;
	for (int i = 0; i < child_count - 1; ++i) {
		bounds[i + 1].x = bounds[i].x + bounds[i].w;
	}

	min_count = KN_MIN(child_count, c->cross_count);
	for (int i = 0; i < min_count; ++i) {
		bounds[i].h = FLX_FlexSizeToAbsolute(c->cross[i], parent_bounds->h, cross_auto_size);
		bounds[i].y = parent_bounds->y;
	}
	for (int i = min_count; i < child_count; ++i) {
		bounds[i].h = FLX_FlexSizeToAbsolute(last_cross, parent_bounds->h, cross_auto_size);
		bounds[i].y = parent_bounds->y;
	}

	free(auto_indices);
	return bounds;
};
