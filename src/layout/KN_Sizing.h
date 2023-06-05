#ifndef _KN_SIZING
#define _KN_SIZING

typedef enum KN_Unit {
	KN_UnitPX,
	KN_UnitPERCENT,
	KN_UnitAUTO
} KN_Unit;

typedef struct KN_FlexSize {
	KN_Unit unit;
	double value;
} KN_FlexSize;

typedef struct KN_Bounds {
	int x;
	int y;
	int w;
	int h;
} KN_Bounds;

KN_Bounds* KN_FlexSizesToBounds(
	KN_Bounds parent_bounds,
	KN_FlexSize* flex_sizes_h,
	KN_FlexSize* flex_sizes_v,
	int count
);

#endif
