#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

using namespace std;

class Point2D {
private:
	float x, y;
public:

	Point2D operator+(const Point2D& p);
	Point2D& operator=(const Point2D& p);
	bool operator==(const Point2D& p);

	Point2D() {
		x = 0.0;
		y = 0.0;
	}
	Point2D(const float& nx, const float& ny) {
		x = nx;
		y = ny;
	}
	Point2D(const int& nx, const int& ny) {
		x = static_cast<float>(nx);
		y = static_cast<float>(ny);
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float Distance(float p1, float p2);

	string Location();
};

class Shape {
private:
	int colors[4];
	int pos_index;
	Point2D pos;
public:
	Shape(Point2D p, int* arr, int i) {
		pos = p;
		pos_index = i;
		for (int k = 0; k < 4; k++) {
			colors[k] = arr[k];
		}
	}

	int getIndex();
	void setIndex(int setIndex);
	string getColors();
	int getRed();
	int getGreen();
	int getBlue();
	int getAlpha();
	int getX();
	int getY();

	virtual void render(SDL_Renderer* r) = 0;
	virtual int getHeight() = 0;
	virtual string getKind() = 0;

	void setRed(int setRed);
	void setGreen(int setGreen);
	void setBlue(int setBlue);
	void setAlpha(int setAlpha);
};
class Rectangle : public Shape {
private:
	int width;
	int height;
	string kind;
public:
	Rectangle(Point2D p, int* arr, int i, int nw, int nh) :
		Shape(p, arr, i), width(nw), height(nh) {
	}
	int getWidth();
	int getHeight();
	void setWidth(int nw);
	void setHeight(int nh);
	virtual string getKind();
	void setKind(string newKind);
	virtual void render(SDL_Renderer* r);
};
class Triangle : public Shape {
private:
	int base;
	int height;
	bool upward;
public:
	Triangle(Point2D p, int* arr, int i, int nb, int nh, bool dir) :
		Shape(p, arr, i), base(nb), height(nh), upward(dir) {
	}
	int getBase();
	int getHeight();
	void setBase(int nb);
	void setHeight(int nh);
	virtual string getKind();
	virtual void render(SDL_Renderer* r);
};
class Circle : public Shape {
private:
	int radius;
public:
	Circle(Point2D p, int* arr, int i, int nr) :
		Shape(p, arr, i), radius(nr) {
	}
	int getRadius();
	void setRadius(int nr);
	virtual string getKind();
	int getHeight();
	virtual void render(SDL_Renderer* r);
};

class V : public Shape {
private:
	int base;
	int height;
	bool lessThan;
public:
	V(Point2D p, int* arr, int i, int nb, int nh, bool nv) :
		Shape(p, arr, i), base(nb), height(nh), lessThan(nv) {
	}
	int getBase();
	int getHeight();
	void setBase(int nb);
	void setHeight(int nh);
	virtual string getKind();
	virtual void render(SDL_Renderer* r);
};

class X : public Shape {
private:
	int line;
public:
	X(Point2D p, int* arr, int i, int nl) :
		Shape(p, arr, i), line(nl) {
	}
	int getLength1();
	void setLength(int nl);
	virtual string getKind();
	int getHeight();
	virtual void render(SDL_Renderer* r);
};

class Star : public Shape {
private:
	int line;
public:
	Star(Point2D p, int* arr, int i, int nl) :
		Shape(p, arr, i), line(nl) {
	}
	int getLength();
	void setLength1(int nl);
	virtual string getKind();
	int getHeight();
	virtual void render(SDL_Renderer* r);
};
class Z : public Shape {
private:
	int width;
	int height;
public:
	Z(Point2D p, int* arr, int i, int nw, int nh) :
		Shape(p, arr, i), width(nw), height(nh) {
	}
	int getWidth();
	int getHeight();
	void setWidth(int nw);
	void setHeight(int nh);
	virtual string getKind();
	virtual void render(SDL_Renderer* r);
};

class Card : public Shape {
private:
	int width = 75;
	int height = 125;
	Shape* s = nullptr;
public:
	Card(Point2D p, int* arr, int i) :
		Shape(p, arr, i) {
	}
	~Card() {
		delete s;
	}

	int getWidth();
	int getHeight();
	void remove(SDL_Renderer* r);
	void setType(Shape* ns);
	Shape* getType();
	virtual string getKind();
	virtual void render(SDL_Renderer* r);
};

class Memory {
public:
	Card* arr[20];
	int arr_x[20] = {};
	int arr_y[20] = {};
	Memory(SDL_Renderer* r) {
		fillArrays(arr_x, arr_y);
		initCards(r);
		renderAll(r);
		assignCards(r);

	}

	void initCards(SDL_Renderer* r);
	void assignCards(SDL_Renderer* r);
	void clearAll(SDL_Renderer* r);
	void renderAll(SDL_Renderer* r);

	void randomizeOrder(int* aarr);

	Shape* createCardTypes(int i, int pos);
	Rectangle* newSqr(int pos);
	Rectangle* newRec(int pos);
	Triangle* newTri(int pos, bool dir);
	Circle* newCir(int pos);
	V* newV(int pos, bool less);
	X* newX(int pos);
	Star* newStar(int pos);
	Z* newZ(int pos);

	void fillArrays(int* arr_x, int* arr_y);
};



