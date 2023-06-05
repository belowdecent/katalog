#ifndef _FLX_CONTAINER
#define _FLX_CONTAINER

#include "KN_Sizing.h"

typedef enum FLX_Direction {
	FLX_ROW,
	FLX_COLUMN	
} FLX_Direction;

typedef enum FLX_Align {
	FLX_ALIGN_BEGIN,
	FLX_ALIGN_CENTER,
	FLX_ALIGN_END,
} FLX_Align;

typedef enum FLX_Repeat {
	FLX_REPEAT_LAST,
	FLX_REPEAT_CYCLE,
	FLX_REPEAT_NONE
} FLX_Repeat;

typedef struct FLX_Container {
	FLX_Direction direction;
	FLX_Align	main_axis;
	FLX_Align cross_axis;

	FLX_Repeat repeat_mode;

	KN_FlexSize* main_sizes;
	KN_FlexSize* cross_sizes;
	int main_sizes_count;
	int cross_sizes_count;
} FLX_Container;

#endif