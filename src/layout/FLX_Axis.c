#include "FLX_Axis.h"
#include <stdlib.h>

void FLX_SetAxis(FLX_Axis* axis, int n, KN_FlexSize const* layout) {
	axis->layout = malloc(sizeof(KN_FlexSize) * n);
	axis->count = n;
	for (int i = 0; i < n; ++i) {
		axis->layout[i].unit = layout[i].unit;
		axis->layout[i].value = layout[i].value;
	}
}
