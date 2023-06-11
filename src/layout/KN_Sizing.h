#ifndef _KN_SIZING
#define _KN_SIZING

typedef enum KN_Unit {
	KN_UNIT_PX = 0,
	KN_UNIT_PERCENT = 1,
	KN_UNIT_AUTO = 2
} KN_Unit;

typedef struct KN_FlexSize {
	KN_Unit unit;
	double value;
} KN_FlexSize;

typedef struct KN_Bounds {
	double x;
	double y;
	double w;
	double h;
} KN_Bounds;

#endif
