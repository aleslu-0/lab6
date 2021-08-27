#pragma once
#include <iostream>
#include <string>
#include "task2.h"

Point2D Point2D::operator+(const Point2D& p) {
	Point2D P;
	P.x = this->x + p.x;
	P.y = this->y + p.y;
	return P;
}
Point2D& Point2D::operator=(const Point2D& p) {
	x = p.x;
	y = p.y;
	return *this;
}
bool Point2D::operator==(const Point2D& p) {
	return (x == p.x && y == p.y);
}

float Point2D::Distance(float px, float py) {
	float a = px - x;
	float b = py - y;
	float dist = sqrt(pow(a, 2) + pow(b, 2));
	return dist;
}
string Point2D::Location() {
	string sx = to_string(x);
	string sy = to_string(y);
	string p = "[" + sx + "," + sy + "]";
	return p;
}

void Memory::randomizeOrder(int* arr) {
	srand(time(NULL));
	int slots[20];
	int count = 0;
	while (count < 20) {
		int randomIndex = rand() % 20;
		int* slotUsed = find(begin(slots), end(slots), randomIndex);
		// When the element is not found, std::find returns the end of the range
		if (slotUsed != end(slots)) {
			//cerr << "Found" << endl;
		}
		else {
			//cerr << "Not found" << endl;
			//cout << randomIndex;
			slots[count] = randomIndex;
			count++;
		}
	}
	for (int i = 0; i < 20; i++) {
		arr[i] = slots[i];
	}
}