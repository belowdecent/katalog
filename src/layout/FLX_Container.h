#ifndef _FLX_CONTAINER
#define _FLX_CONTAINER

#include "FLX_Axis.h"

typedef enum FLX_Direction {
	FLX_ROW,
	FLX_COLUMN	
} FLX_Direction;

typedef enum FLX_Repeat {
	FLX_REPEAT_LAST,
	FLX_REPEAT_CYCLE,
	FLX_REPEAT_NONE
} FLX_Repeat;

typedef struct FLX_Container {
	FLX_Direction direction;
	FLX_Repeat repeat_mode;

	FLX_Axis main;
	FLX_Axis cross;
} FLX_Container;

FLX_Container FLX_ContainerAuto(
	FLX_Direction direction,
	FLX_Align main_align,
	FLX_Align cross_align		
);

FLX_Container FLX_ContainerNew(
	FLX_Direction direction,
	KN_FlexSize*  main,
	FLX_Align 	  main_align,
	int 				  main_count,
	KN_FlexSize*  cross,
	FLX_Align     cross_align,
	int           cross_count,
	FLX_Repeat    repeat_mode
);

int FLX_FlexSizeToAbsolute(
	KN_FlexSize size, 
	double container_size, 
	int auto_width
);

KN_Bounds* FLX_FlexSizesToBounds(
	FLX_Container* c, 
	KN_Bounds* parent_bounds, 
	int child_count
);

#endif