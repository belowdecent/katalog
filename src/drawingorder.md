window
	searchbox
		label
			text
		search-field
			text
	itemlist
		item x infinite
			text

struct vec2 {
	int x;
	int y;
}

struct element {
	text text;
	layout_direction;
	sizing;
	element_list children;
}

element_list {
	element;
	next;
}

layout {
	direction: KNTR_LayoutDirection
	
}
