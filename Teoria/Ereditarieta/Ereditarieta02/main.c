#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>

#include "canvas.h"
#include <string.h>
#include <stdlib.h>

typedef struct shape {
	char *type_;
	int x0_, y0_, x1_, y1_, r_;
	char ch_;
} shape;
shape *shape_create(shape *this, const char *type, int x0, int y0, int x1, int y1, int r, char ch) {
	this->type_ = strcpy(malloc(strlen(type) + 1), type);
	this->x0_ = x0;
	this->y0_ = y0;
	this->x1_ = x1;
	this->y1_ = y1;
	this->r_ = r;
	this->ch_ = ch;
	return this;
}
shape *shape_destroy(shape *this) {
	free(this->type_);
	return this;
}
shape *new_shape(const char *type, int x0, int y0, int x1, int y1, int r, char ch) {
	return shape_create(malloc(sizeof(shape)), type, x0, y0, x1, y1, r, ch);
}
void delete_shape(shape *this) {
	free(shape_destroy(this));
}
void shape_print(const shape *this, canvas *c) {
	if (strcmp(this->type_, "point") == 0) {
		canvas_set(c, this->x0_, this->y0_, this->ch_);
	}
	else if (strcmp(this->type_, "line") == 0) {
		canvas_line(c, this->x0_, this->y0_, this->x1_, this->y1_, this->ch_);
	}
	else if (strcmp(this->type_, "rectangle") == 0) {
		canvas_rectangle(c, this->x0_, this->y0_, this->x1_, this->y1_, this->ch_);
	}
	else if (strcmp(this->type_, "circle") == 0) {
		canvas_circle(c, this->x0_, this->y0_, this->r_, this->ch_);
	}
}


/*
type_of_object parameter_1 parameter_2 ... parameter_n

rectangle 0 0 79 24 *
point 5 15 ?
circle 10 10 4 @
circle 70 10 4 @
line 40 15 40 20 |
*/

shape **read_shapes(FILE *f, size_t *size)
{
	shape **sv = NULL;
	size_t n = 0;

	char type[30];
	while (fscanf(f, "%29s", type) == 1) {
		int x0, y0, x1, y1, r;
		char ch;
		sv = realloc(sv, ++n * sizeof *sv);
		if (strcmp(type, "point") == 0) {
			fscanf(f, "%d%d %c", &x0, &y0, &ch);
			sv[n - 1] = new_shape(type, x0, y0, 0, 0, 0, ch);
		}
		else if (strcmp(type, "line") == 0) {
			fscanf(f, "%d%d%d%d %c", &x0, &y0, &x1, &y1, &ch);
			sv[n - 1] = new_shape(type, x0, y0, x1, y1, 0, ch);
		}
		else if (strcmp(type, "rectangle") == 0) {
			fscanf(f, "%d%d%d%d %c", &x0, &y0, &x1, &y1, &ch);
			sv[n - 1] = new_shape(type, x0, y0, x1, y1, 0, ch);
		}
		else if (strcmp(type, "circle") == 0) {
			fscanf(f, "%d%d%d %c", &x0, &y0, &r, &ch);
			sv[n - 1] = new_shape(type, x0, y0, 0, 0, r, ch);
		}
	}
	
	*size = n;
	return sv;
}

int main(void)
{
	canvas* c = new_canvas(80, 25);

	size_t n = 0;
	shape **sv = read_shapes(stdin, &n);

	for (size_t i = 0; i < n; ++i) {
		shape_print(sv[i], c);
	}

	canvas_out(c, stdout);

	for (size_t i = 0; i < n; ++i) {
		delete_shape(sv[i]);
	}
	delete_canvas(c);
}