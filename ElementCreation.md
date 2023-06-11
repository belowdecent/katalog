# Example usage
KN_Element root = KN_CreateRootElement(window);
root.container = FLX_ContainerNew(FLX_ROW);
FLX_SetAxis(&root.container.main, 5, (FLX_Axis[]){
	FLX_PX(13),
	FLX_AUTO(1),
	FLX_PERCENT(20),
	FLX_PX(13)
});

KN_AddChildren(&root);

# okay flex logic
direction switches x,y coords at the end or pointers
main_coord(bounds, AXIS_TYPE)  = &((AXIS_TYPE == ROW) ? bounds.x : bounds.y)
main_size(bounds, AXIS_TYPE)   = &((AXIS_TYPE == ROW) ? bounds.w : bounds.h)
cross_coord(bounds, AXIS_TYPE) = &((AXIS_TYPE == ROW) ? bounds.y : bounds.x)
cross_size(bounds, AXIS_TYPE)  = &((AXIS_TYPE == ROW) ? bounds.h : bounds.w)

1. count auto elements in main axis
2. calculate free space in main axis
3. calculate auto size in main
4. set auto size in cross as the size of the cross axis
5. calculate the starting main coord
6. complete the main part of the bounds
7. calculate the starting cross coord
8. complete the cross part of bounds
9. return bounds

align:
- baseline:
	coord(0) = 0
	coord(N) = coord(N-1) + size(N-1)
- center:
	evaluate freespace
	coord(0) = freespace / 2
	coord(N) = coord(N-1) + size(N-1)
- right:
	evaluate freespace
	coord(0) = freespace
	coord(N) = coord(N-1) + size(N-1)
- space-between:
	evaluate freespace
	coord(0) = 0
	coord(N) = freespace / (count - 1) * N + coord(N-1) + size(N-1)
- space-around:
	coord(0) = freespace / (count + 1)
	coord(N) = freespace / (count + 1) * N + coord(N-1) + size(N-1)
	
