/* ************************************************************************ */
/*																			*/
/*	Neko VM source															*/
/*  (c)2005 Nicolas Cannasse												*/
/*																			*/
/* ************************************************************************ */
#include <string.h>
#include "objtable.h"

objtable otable_empty() {
	objtable t2 = (objtable)alloc(sizeof(objtable));
	t2->count = 0;
	t2->cells = NULL;
	return t2;
}

void otable_replace(objtable t, field id, value data) {
	int min = 0;
	int max = t->count;
	int mid;
	field cid;
	cell *c = t->cells;
	while( min < max ) {
		mid = (min + max) >> 1;
		cid = c[mid].id;
		if( cid < id )
			max = mid;
		else if( cid > id )
			min = mid;
		else {
			c[mid].v = data;
			return;
		}
	}
	c = (cell*)alloc(sizeof(cell)*(t->count+1));
	min = 0;
	while( min < mid ) {
		c[min] = t->cells[min];
		min++;
	}
	c[mid].id = id;
	c[mid].v = data;
	while( min < t->count ) {
		c[min+1] = t->cells[min];
		min++;
	}
	t->cells = c;
	t->count++;
}

objtable otable_copy(objtable t) {
	objtable t2 = (objtable)alloc(sizeof(objtable));
	t2->count = t->count;
	t2->cells = (cell*)alloc(sizeof(cell)*t->count);
	memcpy(t2->cells,t->cells,sizeof(cell)*t->count);
	return t2;
}

/* ************************************************************************ */
