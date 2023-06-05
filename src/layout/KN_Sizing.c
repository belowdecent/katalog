#include "KN_Sizing.h"
#include <stdlib.h>

KN_Bounds* KN_FlexSizesToBounds(
	KN_Bounds parent_bounds,
	KN_FlexSize* flex_sizes_h,
	KN_FlexSize* flex_sizes_v,
	int count
) {
	if (count == 0) 
		return NULL;
	
	KN_Bounds* bounds = malloc(count * sizeof(KN_Bounds));

	int auto_count = 0;
	double occupied_width = 0;
	double total_width = parent_bounds.w;

	for (int i = 0; i < count; ++i) {
		KN_Unit unit = flex_sizes_h[i].unit;
		double value = flex_sizes_h[i].value;
		switch (unit) {
    	case KN_UnitPX:
				occupied_width += value;
				break;
			case KN_UnitPERCENT:
				occupied_width += (double)parent_bounds.w * value;
				break;
			case KN_UnitAUTO:
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
    	case KN_UnitPX:
				bounds[i].w = flex_sizes_h[i].value;
				break;
			case KN_UnitPERCENT:
				bounds[i].w = flex_sizes_h[i].value * total_width;
				break;
			case KN_UnitAUTO:
				bounds[i].w = (i < count - 1) 
					? auto_width 
					: parent_bounds.w - current_x + parent_bounds.x;
				break;
    }
		current_x += bounds[i].w;
		
		switch (flex_sizes_v[i].unit) {
    	case KN_UnitPX:
				bounds[i].h = flex_sizes_v[i].value;
				break;
			case KN_UnitPERCENT:
				bounds[i].h = flex_sizes_v[i].value * parent_bounds.h;
				break;
			case KN_UnitAUTO:
				bounds[i].h = auto_height;
				break;
    }
	}
	return bounds;
}
