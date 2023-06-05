#include "FLX_Container.h"
#include "KN_Sizing.h"
#include <stdlib.h>

KN_FlexSize FLX_AUTOSIZE = { KN_UnitAUTO, 0 };

FLX_Container* FLX_ContainerAuto(
	FLX_Direction direction,
	FLX_Align main_axis,
	FLX_Align cross_axis		
) {
	FLX_Container* container = malloc(sizeof(FLX_Container));
	container->direction = direction;
	container->main_axis = main_axis;
	container->cross_axis = cross_axis;
	
	container->main_sizes = &FLX_AUTOSIZE;
	container->main_sizes_count = 1;

	container->cross_sizes = &FLX_AUTOSIZE;
	container->cross_sizes_count = 1;

	container->repeat_mode = FLX_REPEAT_LAST;
	return container;
}

FLX_Container* FLX_ContainerNew(
	FLX_Direction direction,
	FLX_Align main_axis,
	FLX_Align cross_axis,
	KN_FlexSize* main_sizes,
	int main_sizes_count,
	KN_FlexSize* cross_sizes,
	int cross_sizes_count,
	FLX_Repeat repeat_mode
) {
	FLX_Container* container = malloc(sizeof(FLX_Container));
	container->direction  = direction;
	container->main_axis  = main_axis;
	container->cross_axis = cross_axis;
	
	container->main_sizes = main_sizes;
	container->main_sizes_count = main_sizes_count;

	container->cross_sizes = cross_sizes;
	container->cross_sizes_count = cross_sizes_count;

	container->repeat_mode = repeat_mode;
	return container;
}

void FLX_ContainerFree(
	FLX_Container* container, 
	int free_main_sizes, 
	int free_cross_sizes) 
{
	if (free_main_sizes) 
		free(container->main_sizes);
	if (free_cross_sizes)
		free(container->cross_sizes);

	return free(container);
}