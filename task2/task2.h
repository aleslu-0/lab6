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
	Point2D(const float &nx, const float &ny) {
		x = nx;
		y = ny;
	}
	Point2D(const int &nx, const int &ny) {
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
	int getBase() {
		return base;
	}
	int getHeight() {
		return height;
	}
	void setBase(int nb) {
		if (nb > 0) {
			base = nb;
		}	
	}
	void setHeight(int nh) {
		if (nh > 0) {
			height = nh;
		}		
	}
	virtual string getKind() {
		if (lessThan) {
			return "lesserV";
		}
		else {
			return "greaterV";
		}
		
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a V with the base of: " << base << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		int newBase = (base / 2);
		int newHeight = (height / 2);
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
	X(Point2D p, int* arr, int i, int nl) :
		Shape(p, arr, i), line(nl) {
	}
	int getLength1() {
		return line;
	}

	void setLength(int nl) {
		line = nl;
	}
	virtual string getKind() {
		return "X";
	}
	int getHeight() {
		return -1;
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing an X with the base of: " << line << " and height of: " << line << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		int halfLine = (line / 2);
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
	Star(Point2D p, int* arr, int i, int nl) :
		Shape(p, arr, i), line(nl) {
	}
	int getLength() {
		return line;
	}

	void setLength1(int nl) {
		line = nl;
	}
	virtual string getKind() {
		return "Star";
	}
	int getHeight() {
		return -1;
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing an X with the base of: " << line << " and height of: " << line << " at: " << getX() << ", " << getY() << endl;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		int halfLine = line / 2;
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
	Z(Point2D p, int* arr, int i, int nw, int nh) :
		Shape(p, arr, i), width(nw), height(nh) {
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
	virtual string getKind() {
		return "Z";
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a rectangle with the height of: " << width << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		int newWidth = width / 2;
		int newHeight = height / 2;
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
	Shape *s = nullptr;
public:
	Card(Point2D p, int* arr, int i) :
		Shape(p, arr, i) {
	}
	virtual void render(SDL_Renderer* r) {
		int x = getX();
		int y = getY();
		cout << "Drawing a rectangle with the height of: " << width << " and height of: " << height << " at: " << getX() << ", " << getY() << endl;
		int newWidth = width / 2;
		int newHeight = height / 2;
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
		for (int i = 0; i < width; i++) {
			SDL_RenderDrawLine(r, x-newWidth+i, y-newHeight, x-newWidth+i, y+newHeight);
		}
		SDL_RenderPresent(r);

		//SDL_Delay(500);

	}
	~Card() {
		delete s;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
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
	virtual string getKind() {
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
		initCards(r);
		//Point2D p(10, 10);
		renderAll(r);
		doStuff(r);
		
	}
	
	void initCards(SDL_Renderer* r) {
		int arr_r[4] = { 255, 255, 255, 0 };
		for (int i = 0; i < 20; i++) {
			Point2D p(arr_x[i], arr_y[i]);
			arr[i] = new Card(p, arr_r, i);
			//arr[i]->render(r);
		}
	}
	void doStuff(SDL_Renderer* r) {
		Shape* s[20];
		int arr_order[20] = {};
		randomizeOrder(arr_order);
		for (int i = 0; i < 20; i++) {
			s[i] = createCards(arr_order[i], i);
		}

		for (int i = 0; i < 20; i++) {
			//cout << arr_order[i] << endl;
			arr[i]->setType(s[i]);
		}
	}
	void clearAll(SDL_Renderer* r) {
		SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
		SDL_RenderClear(r);
		
		SDL_RenderPresent(r);
	}
	void renderAll(SDL_Renderer* r) {
		
		for (int i = 0; i < 20; i++) {
			if(arr[i] != nullptr)
				arr[i]->render(r);
		}
	}

	void randomizeOrder(int* aarr); 

	Shape* createCards(int i, int pos) {
		if (i == 0 || i == 1) {
			return newSqr(pos);
		}
		else if (i == 2 || i == 3) {
			return newTri(pos, true);
		}
		else if (i == 4 || i == 5) {
			return newTri(pos, false);		
		}
		else if (i == 6 || i == 7) {
			return newCir(pos);
		}
		else if (i == 8 || i == 9) {
			return newV(pos, true);
		}
		else if (i == 10 || i == 11) {
			return newV(pos, false);
		}
		else if (i == 12 || i == 13) {
			return newRec(pos);
		}
		else if (i == 14 || i == 15) {
			return newX(pos);
		}
		else if (i == 16 || i == 17) {
			return newStar(pos);
		}
		else if (i == 18 || i == 19) {
			return newZ(pos);
		}
		else {
			cerr << "Error"; 
		}
		return nullptr;
	}
	Rectangle* newSqr(int pos) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Rectangle *r = new Rectangle(p, arr_r, pos, 30, 30);
		r->setKind("Square");
		return r;	
	}
	Rectangle* newRec(int pos) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Rectangle* r = new Rectangle(p, arr_r, pos, 15, 40);
		r->setKind("Rectangle");
		return r;
	}
	Triangle* newTri(int pos, bool dir) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Triangle* t = new Triangle(p, arr_r, pos, 20, 20, dir);
		return t;
	}
	Circle* newCir(int pos) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Circle* c = new Circle(p, arr_r, pos, 20);
		return c;
	}
	V* newV(int pos, bool less) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		V* v = new V(p, arr_r, pos, 20, 20, less);
		return v;
	}
	X* newX(int pos) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		X* x = new X(p, arr_r, pos, 20);
		return x;
	}
	Star* newStar(int pos) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Star* s = new Star(p, arr_r, pos, 40);
		return s;
	}
	Z* newZ(int pos) {
		Point2D p(arr_x[pos], arr_y[pos]);
		int arr_r[4] = { 255, 0, 50, 255 };
		Z* z = new Z(p, arr_r, pos, 20, 20);
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



