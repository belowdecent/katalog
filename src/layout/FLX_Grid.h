#ifndef _FLX_GRID
#define _FLX_GRID

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
	int repeat_limit;

	KN_FlexSize* sizes_h;
	KN_FlexSize* sizes_v;
	int sizes_h_count;
	int sizes_v_count;
} FLX_Line;

#endif