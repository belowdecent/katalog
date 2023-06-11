#ifndef _FLX_AXIS
#define _FLX_AXIS

#include "KN_Sizing.h"

typedef enum FLX_Align {
	FLX_ALIGN_BEGIN,
	FLX_ALIGN_CENTER,
	FLX_ALIGN_END,
} FLX_Align;

typedef struct FLX_Axis {
	KN_FlexSize* layout;
	FLX_Align align;
	int count;
} FLX_Axis;

void FLX_SetAxis(FLX_Axis* axis, int n, KN_FlexSize const* layout);

#endif