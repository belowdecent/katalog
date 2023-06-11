#include "FLX_Container.h"
#include "KN_Sizing.h"
#include <pango/pangocairo.h>



typedef struct KN_Padding {
	KN_FlexSize top;
	KN_FlexSize right;
	KN_FlexSize bottom;
	KN_FlexSize left;
} KN_Padding;

#define KN_PADDING_ALL(type, value) 		(KN_Padding) {\
																					{type, value},\
																					{type, value},\
																					{type, value},\
																					{type, value}\
																				}
#define KN_PADDING_INLINE(type, value)  (KN_Padding) {\
																					{0},\
																					{type, value},\
																					{0},\
																					{type, value}\
																				}
#define KN_PADDING_BLOCK(type, value)   (KN_Padding) {\
																					{type, value},\
																					{0},\
																					{type, value},\
																					{0}\
																				}

typedef struct KN_Element {
	KN_Bounds bounds;
	KN_Padding padding;
	FLX_Container container;
	struct KN_Element* children;
	int count;
} KN_Element;

int KN_DrawElement(KN_Element* element, cairo_t* cr);
KN_Element* KN_ElementNew(FLX_Container structure);
