#include "KNTR_Sizing.h"
#include <stdlib.h>

KNTR_Bounds* KNTR_FlexSizesToBounds(
	KNTR_Bounds parent_bounds,
	KNTR_FlexSize* flex_sizes_h,
	KNTR_FlexSize* flex_sizes_v,
	int count
) {
	if (count == 0) 
		return NULL;
	
	KNTR_Bounds* bounds = malloc(count * sizeof(KNTR_Bounds));

	int auto_count = 0;
	double occupied_width = 0;
	double total_width = parent_bounds.w;

	for (int i = 0; i < count; ++i) {
		KNTR_Unit unit = flex_sizes_h[i].unit;
		double value = flex_sizes_h[i].value;
		switch (unit) {
    	case KNTR_UnitPX:
				occupied_width += value;
				break;
			case KNTR_UnitPERCENT:
				occupied_width += (double)parent_bounds.w * value;
				break;
			case KNTR_UnitAUTO:
				auto_count += 1;
				break;
    }
	}

	int auto_width = 0;
	int auto_height = parent_bounds.h;
	if (auto_count) {
		int free_space = (int)(total_width - occupied_width);
		auto_width = free_space / auto_count;
	}

	int current_x = parent_bounds.x;
	for (int i = 0; i < count; ++i) {
		bounds[i].x = current_x;
		bounds[i].y = 0;
		switch (flex_sizes_h[i].unit) {
    	case KNTR_UnitPX:
				bounds[i].w = flex_sizes_h[i].value;
				break;
			case KNTR_UnitPERCENT:
				bounds[i].w = flex_sizes_h[i].value * total_width;
				break;
			case KNTR_UnitAUTO:
				bounds[i].w = (i < count - 1) 
					? auto_width 
					: parent_bounds.w - current_x + parent_bounds.x;
				break;
    }
		current_x += bounds[i].w;
		
		switch (flex_sizes_v[i].unit) {
    	case KNTR_UnitPX:
				bounds[i].h = flex_sizes_v[i].value;
				break;
			case KNTR_UnitPERCENT:
				bounds[i].h = flex_sizes_v[i].value * parent_bounds.h;
				break;
			case KNTR_UnitAUTO:
				bounds[i].h = auto_height;
				break;
    }
	}
	return bounds;
}
