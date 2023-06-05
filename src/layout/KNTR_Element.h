#include "KNTR_Sizing.h"

typedef struct KNTR_Element {
	KNTR_Bounds bounds;

	KNTR_FlexSize* child_layout_v;
	KNTR_FlexSize* child_layout_h;
	struct KNTR_Element* children;
	int count;

} KNTR_Element;

int KNTR_DrawElement(KNTR_Element* element);
KNTR_Element* KNTR_ElementNew(KNTR_FlexSize layout_v[], KNTR_FlexSize layout_h[]);
