#ifndef _KNTR_SIZING
#define _KNTR_SIZING

typedef enum KNTR_Unit {
	KNTR_UnitPX,
	KNTR_UnitPERCENT,
	KNTR_UnitAUTO
} KNTR_Unit;

typedef struct KNTR_FlexSize {
	KNTR_Unit unit;
	double value;
} KNTR_FlexSize;

typedef struct KNTR_Bounds {
	int x;
	int y;
	int w;
	int h;
} KNTR_Bounds;

KNTR_Bounds* KNTR_FlexSizesToBounds(
	KNTR_Bounds parent_bounds,
	KNTR_FlexSize* flex_sizes_h,
	KNTR_FlexSize* flex_sizes_v,
	int count
);

#endif
