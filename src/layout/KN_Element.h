#include "FLX_Container.h"

typedef struct KN_Element {
	KN_Bounds bounds;
	FLX_Container container;
	struct KN_Element* children;
	int count;
} KN_Element;

int KN_DrawElement(KN_Element* element);
KN_Element* KN_ElementNew(FLX_Container structure);
