/*
 * shapes.c
 *
 *  Created on: Feb 9, 2023
 *      Author: seandavidreed
 */

#include <stdio.h>

const double PI = 3.14159;

struct Square {
	unsigned int side;
};

struct Rectangle {
	unsigned int width;
	unsigned int height;
};

struct Circle {
	unsigned int radius;
};

struct Triangle {
	unsigned int base;
	unsigned int height;
};

enum shapeType {
	SHAPE_SQUARE, SHAPE_RECTANGLE, SHAPE_CIRCLE, SHAPE_TRIANGLE
};

struct Shape {
	enum shapeType type;
	union {
		struct Square square;
		struct Rectangle rectangle;
		struct Circle circle;
		struct Triangle triangle;
	} dimensions;
};

void drawSquare(const unsigned int side) {
	printf("Square\n");
	printf("Perimeter is %d\n", side * 4);
	printf("Area is %d\n", side * side);
}

void drawRectangle(const unsigned int height, const unsigned int width) {
	printf("Rectangle\n");
	printf("Perimeter is %d\n", (height * 2) + (width * 2));
	printf("Area is %d\n", height * width);
}

void drawCircle(const unsigned int radius) {
	printf("Circle\n");
	printf("Circumference is %.2lf\n", radius * radius * PI);
	printf("Area is %.2lf\n", 2 * PI * radius);
}

void drawTriangle(const unsigned int base, const unsigned int height) {
	printf("Triangle\n");
	printf("Perimeter is %d\n", base * 3);
	printf("Area is %.2lf\n", (base * height) / 2.0);
}

void drawShape(const struct Shape* const shape) {
	switch (shape->type) {
		case SHAPE_SQUARE:
			drawSquare(shape->dimensions.square.side);
			break;
		case SHAPE_RECTANGLE:
			drawRectangle(shape->dimensions.rectangle.height,
					shape->dimensions.rectangle.width);
			break;
		case SHAPE_CIRCLE:
			drawCircle(shape->dimensions.circle.radius);
			break;
		case SHAPE_TRIANGLE:
			drawTriangle(shape->dimensions.triangle.base,
					shape->dimensions.triangle.height);
	}
}

int main() {
	struct Shape myCircle = {
		.type = SHAPE_CIRCLE,
		.dimensions.circle.radius = 3
	};

	drawShape(&myCircle);

	struct Shape shape = {
		.type = SHAPE_SQUARE,
		.dimensions.square.side = 4
	};

	drawShape(&shape);

	shape.type = SHAPE_RECTANGLE;
	shape.dimensions.rectangle.height = 3;
	shape.dimensions.rectangle.width = 2;

	drawShape(&shape);

	struct Shape myTriangle = {
		.type = SHAPE_TRIANGLE,
		.dimensions.triangle.base = 5,
		.dimensions.triangle.height = 2
	};

	drawShape(&myTriangle);

	return 0;
}
