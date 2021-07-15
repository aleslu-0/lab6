#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <math.h>
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
	Point2D pos;
public:
	Shape(Point2D p, int* arr) {
		pos = p;
		for (int k = 0; k < 4; k++) {
			colors[k] = arr[k];
		}
	}
	string getColors() {
		string s = to_string(colors[0]) + ", " + to_string(colors[1]) + ", " + to_string(colors[2]) + ", " + to_string(colors[3]);
		return s;
	}
	int getRed() {
		return colors[0];
	}
	int getGreen() {
		return colors[1];
	}
	int getBlue() {
		return colors[2];
	}
	int getAlpha() {
		return colors[3];
	}
	float getX() {
		return pos.getX();
	}
	float getY() {
		return pos.getY();
	}
	virtual void render(SDL_Renderer* r) = 0;

	virtual int getHeight() = 0;

	virtual string getKind() = 0;

	void setRed(int setRed) {
		if (colors[0] < 0 || colors[0] > 255) {
			colors[0] = colors[0];
		}
		else {
			colors[0] = setRed;
		}
	}
	void setGreen(int setGreen) {
		if (colors[1] < 0 || colors[1] > 255) {
			colors[1] = colors[1];
		}
		else {
			colors[1] = setGreen;
		}
	}
	void setBlue(int setBlue) {
		if (colors[2] < 0 || colors[2] > 255) {
			colors[2] = colors[2];
		}
		else {
			colors[2] = setBlue;
		}
	}
	void setAlpha(int setAlpha) {
		if (colors[3] < 0 || colors[3] > 255) {
			colors[3] = colors[3];
		}
		else {
			colors[3] = setAlpha;
		}
	}
};
class Rectangle : public Shape {
private:
	int width;
	int height;
	string kind;
public:
	Rectangle(Point2D p, int* arr, int nw, int nh) :
		Shape(p, arr), width(nw), height(nh) {
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	void setWidth(int nw) {
		width = nw;
	}
	void setHeight(int nh) {
		height = nh;
	}
	string getKind() {
		return kind;
	}
	void setKind(string newKind) {
		kind = newKind;
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a rectangle with the height of: " << width << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		float newWidth = width / 2;
		float newHeight = height / 2;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		SDL_RenderDrawLine(r, x, y, x, y);
		SDL_RenderDrawLine(r, x-newWidth, y-newHeight, x + newWidth, y-newHeight);
		SDL_RenderDrawLine(r, x + newWidth, y-newHeight, x + newWidth, y + newHeight);
		SDL_RenderDrawLine(r, x + newWidth, y + newHeight, x - newWidth, y + newHeight);
		SDL_RenderDrawLine(r, x - newWidth, y + newHeight, x-newWidth, y-newHeight);

		SDL_RenderPresent(r);

	}
};
class Triangle : public Shape {
private:
	int base;
	int height;
	bool upward;
public:
	Triangle(Point2D p, int* arr, int nb, int nh, bool dir) :
		Shape(p, arr), base(nb), height(nh), upward(dir) {
	}
	int getBase() {
		return base;
	}
	int getHeight() {
		return height;
	}
	void setBase(int nb) {
		base = nb;
	}
	void setHeight(int nh) {
		height = nh;
	}
	string getKind() {
		if (upward) {
			return "UpTriangle";
		}
		else {
			return "DownTriangle";
		}
		
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a triangle with the base of: " << base << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		float newBase = base / 2;
		float newHeight = height / 2;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		SDL_RenderDrawPoint(r, x, y);
		if (upward) {
			SDL_RenderDrawLine(r, x - newBase, y + newHeight, x + newBase, y + newHeight);
			SDL_RenderDrawLine(r, x + newBase, y + newHeight, x, y - newHeight);
			SDL_RenderDrawLine(r, x, y - newHeight, x - newBase, y + newHeight);
		}
		else {
			SDL_RenderDrawLine(r, x - newBase, y - newHeight, x + newBase, y - newHeight);
			SDL_RenderDrawLine(r, x + newBase, y - newHeight, x, y + newHeight);
			SDL_RenderDrawLine(r, x, y + newHeight, x - newBase, y - newHeight);
		}		

		SDL_RenderPresent(r);
	}
};
class Circle : public Shape {
private:
	int radius;
public:
	Circle(Point2D p, int* arr, int nr) :
		Shape(p, arr), radius(nr) {
	}
	int getRadius() {
		return radius;
	}
	void setRadius(int nr) {
		radius = nr;
	}
	string getKind() {
		return "Circle";
	}
	int getHeight() {
		return -1;
	}
	virtual void render(SDL_Renderer* r) {
		cout << "Drawing a circle with a radius of: " << radius << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		int pos_x = getX();
		int pos_y = getY();
		int theta = 0;
		int step = 2;
		SDL_RenderDrawPoint(r, pos_x , pos_y);
		while (theta <= 2160) {
			int x = radius * cos(theta);
			int y = radius * sin(theta);
			SDL_RenderDrawPoint(r, pos_x + x, pos_y + y);
			theta += step;
		}
		SDL_RenderPresent(r);
	}
};
class V : public Shape {
private:
	int base;
	int height;
	bool lessThan;
public:
	V(Point2D p, int* arr, int nb, int nh, bool nv) :
		Shape(p, arr), base(nb), height(nh), lessThan(nv) {
	}
	int getBase() {
		return base;
	}
	int getHeight() {
		return height;
	}
	void setBase(int nb) {
		base = nb;
	}
	void setHeight(int nh) {
		height = nh;
	}
	string getKind() {
		if (lessThan) {
			return "lesserV";
		}
		else {
			return "greaterV";
		}
		
	}
	virtual void render(SDL_Renderer* r) {
		float x = getX();
		float y = getY();
		cout << "Drawing a triangle with the base of: " << base << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		float newBase = base / 2;
		float newHeight = height / 2;
		SDL_RenderDrawPoint(r, x, y);
		if (lessThan) {
			SDL_RenderDrawLine(r, x + newBase, y - newHeight, x - newBase, y);
			SDL_RenderDrawLine(r, x - newBase, y, x + newBase, y + newHeight);
		}
		else {
			SDL_RenderDrawLine(r, x - newBase, y - newHeight, x + newBase, y);
			SDL_RenderDrawLine(r, x + newBase, y, x - newBase, y + newHeight);
		}
		SDL_RenderPresent(r);
	}
};
class X : public Shape {
private:
	int line;
public:
	X(Point2D p, int* arr, int nl) :
		Shape(p, arr), line(nl) {
	}
	int getLength1() {
		return line;
	}

	void setLength(int nl) {
		line = nl;
	}
	string getKind() {
		return "V";
	}
	int getHeight() {
		return -1;
	}
	virtual void render(SDL_Renderer* r) {
		float x = getX();
		float y = getY();
		cout << "Drawing an X with the base of: " << line << " and height of: " << line << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		float halfLine = line / 2;
		SDL_RenderDrawPoint(r, x, y);
		SDL_RenderDrawLine(r, x - halfLine, y + halfLine, x + halfLine, y - halfLine);
		SDL_RenderDrawLine(r, x + halfLine, y + halfLine, x - halfLine, y - halfLine);
		SDL_RenderPresent(r);
	}
};

class Star : public Shape {
private:
	int line;
public:
	Star(Point2D p, int* arr, int nl) :
		Shape(p, arr), line(nl) {
	}
	int getLength() {
		return line;
	}

	void setLength1(int nl) {
		line = nl;
	}
	string getKind() {
		return "Star";
	}
	int getHeight() {
		return -1;
	}
	virtual void render(SDL_Renderer* r) {
		float x = getX();
		float y = getY();
		cout << "Drawing an X with the base of: " << line << " and height of: " << line << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		float halfLine = line / 2;
		SDL_RenderDrawPoint(r, x, y);
		SDL_RenderDrawLine(r, x - halfLine, y + halfLine, x, y - halfLine);
		SDL_RenderDrawLine(r, x, y - halfLine, x + halfLine, y + halfLine);
		SDL_RenderDrawLine(r, x + halfLine, y + halfLine, x - halfLine, y);
		SDL_RenderDrawLine(r, x - halfLine, y, x + halfLine, y);
		SDL_RenderDrawLine(r, x + halfLine, y, x - halfLine, y + halfLine);
		SDL_RenderPresent(r);
	}
};
class Z : public Shape {
private:
	int width;
	int height;
public:
	Z(Point2D p, int* arr, int nw, int nh) :
		Shape(p, arr), width(nw), height(nh) {
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	void setWidth(int nw) {
		width = nw;
	}
	void setHeight(int nh) {
		height = nh;
	}
	string getKind() {
		return "Z";
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a rectangle with the height of: " << width << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		float newWidth = width / 2;
		float newHeight = height / 2;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		//SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		SDL_RenderDrawLine(r, x, y, x, y);
		SDL_RenderDrawLine(r, x - newWidth, y - newHeight, x + newWidth, y - newHeight);
		SDL_RenderDrawLine(r, x + newWidth, y - newHeight, x - newWidth, y + newHeight);
		SDL_RenderDrawLine(r, x - newWidth, y + newHeight, x + newWidth, y + newHeight);

		SDL_RenderPresent(r);

		//SDL_Delay(500);

	}
};

class Card : public Shape {
private:
	int width = 75;
	int height = 125;
	Shape *s;
public:
	Card(Point2D p, int* arr) :
		Shape(p, arr) {
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a rectangle with the height of: " << width << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		float newWidth = width / 2;
		float newHeight = height / 2;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		//SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		for (int i = 0; i < width; i++) {
			SDL_RenderDrawLine(r, x-newWidth+i, y-newHeight, x-newWidth+i, y+newHeight);
		}
		SDL_RenderPresent(r);

		//SDL_Delay(500);

	}
	void remove(SDL_Renderer* r) {
		SDL_RenderClear(r);
	}
	void setType(Shape* ns){
		s = ns;
	}
	Shape* getType() {
		return s;
	}
	int getHeight() {
		return -1;
	}
	string getKind() {
		return "Card";
	}
};

class Memory{
public:
	Card* arr[20];
	int arr_x[20] = {};
	int arr_y[20] = {};
	Memory(SDL_Renderer* r) {
		fillArrays(arr_x, arr_y);
		int arr_r[4] = { 255, 255, 255, 0 };
		for (int i = 0; i < 20; i++) {
			Point2D p(arr_x[i], arr_y[i]);
			arr[i] = new Card(p, arr_r);
			arr[i]->render(r);
		}
		//Point2D p(10, 10);

		Shape* s[20];
		for (int i = 0; i < 20; i++) {
			s[i] = createCards(i);
		}
		for (int i = 0; i < 20; i++) {
			arr[i]->setType(s[i]);
			arr[i]->getType()->render(r); //draw
		}
		
		//bool what = arr[0]->getType() == arr[1]->getType();
		cout << s[0]->getKind() << " " << s[1]->getKind() << endl;
		
		bool what = s[0]->getKind() == s[1]->getKind();
		cout << boolalpha << what;
		cout << endl << arr[0]->getX();
		//arr[0]->remove(r);		
	}
	Shape* createCards(int i) {
		if (i == 0 || i == 1) {
			return newSqr(i);
		}
		else if (i == 2 || i == 3) {
			return newTri(i, true);
		}
		else if (i == 4 || i == 5) {
			return newTri(i, false);		
		}
		else if (i == 6 || i == 7) {
			return newCir(i);
		}
		else if (i == 8 || i == 9) {
			return newV(i, true);
		}
		else if (i == 10 || i == 11) {
			return newV(i, false);
		}
		else if (i == 12 || i == 13) {
			return newRec(i);
		}
		else if (i == 14 || i == 15) {
			return newX(i);
		}
		else if (i == 16 || i == 17) {
			return newStar(i);
		}
		else if (i == 18 || i == 19) {
			return newZ(i);
		}
		else {
			return newSqr(i);
		}
		
	}
	Rectangle* newSqr(int i) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Rectangle *r = new Rectangle(p, arr_r, 30, 30);
		r->setKind("Square");
		return r;	
	}
	Rectangle* newRec(int i) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Rectangle* r = new Rectangle(p, arr_r, 15, 40);
		r->setKind("Rectangle");
		return r;
	}
	Triangle* newTri(int i, bool dir) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Triangle* t = new Triangle(p, arr_r, 20, 20, dir);
		return t;
	}
	Circle* newCir(int i) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Circle* c = new Circle(p, arr_r, 20);
		return c;
	}
	V* newV(int i, bool less) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		V* v = new V(p, arr_r, 20, 20, less);
		return v;
	}
	X* newX(int i) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		X* x = new X(p, arr_r, 20);
		return x;
	}
	Star* newStar(int i) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Star* s = new Star(p, arr_r, 40);
		return s;
	}
	Z* newZ(int i) {
		Point2D p(arr_x[i], arr_y[i]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Z* z = new Z(p, arr_r, 20, 20);
		return z;
	}

	void fillArrays(int* arr_x, int* arr_y) {
		int x;
		int y = 100;
		int pos = 0;
		for (int i = 0; i < 4; i++) {
			x = 100;
			for (int k = 0; k < 5; k++) {
				arr_x[pos] = x;
				arr_y[pos] = y;
				x += 125;
				pos++;
			}
			y += 200;
		}
	}
};



