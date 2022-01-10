#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
#include <math.h>
#include <string>
#include "task2.h"

//Point2D definitions
#pragma region Point2D 
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
    float dist = static_cast<float>(sqrt(pow(a, 2) + pow(b, 2)));
    return dist;
}
string Point2D::Location() {
    string sx = to_string(x);
    string sy = to_string(y);
    string p = "[" + sx + "," + sy + "]";
    return p;
}
#pragma endregion

//Shape definitions
#pragma region Shape

int Shape::getIndex() {
    return pos_index;
}
void Shape::setIndex(int setIndex) {
    pos_index = setIndex;
}
string Shape::getColors() {
    string s = to_string(colors[0]) + ", " + to_string(colors[1]) + ", " + to_string(colors[2]) + ", " + to_string(colors[3]);
    return s;
}
int Shape::getRed() {
    return colors[0];
}
int Shape::getGreen() {
    return colors[1];
}
int Shape::getBlue() {
    return colors[2];
}
int Shape::getAlpha() {
    return colors[3];
}
int Shape::getX() {
    return static_cast<int>(pos.getX());
}
int Shape::getY() {
    return static_cast<int>(pos.getY());
}
void Shape::setRed(int setRed) {
    if (colors[0] < 0 || colors[0] > 255) {
        colors[0] = colors[0];
    }
    else {
        colors[0] = setRed;
    }
}
void Shape::setGreen(int setGreen) {
    if (colors[1] < 0 || colors[1] > 255) {
        colors[1] = colors[1];
    }
    else {
        colors[1] = setGreen;
    }
}
void Shape::setBlue(int setBlue) {
    if (colors[2] < 0 || colors[2] > 255) {
        colors[2] = colors[2];
    }
    else {
        colors[2] = setBlue;
    }
}
void Shape::setAlpha(int setAlpha) {
    if (colors[3] < 0 || colors[3] > 255) {
        colors[3] = colors[3];
    }
    else {
        colors[3] = setAlpha;
    }
}

#pragma endregion

//Rectangle definitions
#pragma region Rectangle
int Rectangle::getWidth() {
    return width;
}
int Rectangle::getHeight() {
    return height;
}
void Rectangle::setWidth(int nw) {
    if (nw > 0)
    {
        width = nw;
    }
}
void Rectangle::setHeight(int nh) {
    if (nh > 0) {
        height = nh;
    }
}
string Rectangle::getKind() {
    return kind;
}
void Rectangle::setKind(string newKind) {
    kind = newKind;
}
void Rectangle::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
    int halfWidth = (width / 2);
    int halfHeight = (height / 2);
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
    SDL_RenderDrawLine(r, x, y, x, y);
    SDL_RenderDrawLine(r, x - halfWidth, y - halfHeight, x + halfWidth, y - halfHeight);
    SDL_RenderDrawLine(r, x + halfWidth, y - halfHeight, x + halfWidth, y + halfHeight);
    SDL_RenderDrawLine(r, x + halfWidth, y + halfHeight, x - halfWidth, y + halfHeight);
    SDL_RenderDrawLine(r, x - halfWidth, y + halfHeight, x - halfWidth, y - halfHeight);

    SDL_RenderPresent(r);

}
#pragma endregion

//Triangle definitions
#pragma region Triangle
int Triangle::getBase() {
    return base;
}
int Triangle::getHeight() {
    return height;
}
void Triangle::setBase(int nb) {
    if (nb > 0) {
        base = nb;
    }
}
void Triangle::setHeight(int nh) {
    if (nh > 0) {
        height = nh;
    }
}
string Triangle::getKind() {
    if (upward) {
        return "Upward Triangle";
    }
    else {
        return "Downward Triangle";
    }

}
void Triangle::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
    int halfBase = base / 2;
    int halfHeight = height / 2;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
    SDL_RenderDrawPoint(r, x, y);
    if (upward) {
        SDL_RenderDrawLine(r, x - halfBase, y + halfHeight, x + halfBase, y + halfHeight);
        SDL_RenderDrawLine(r, x + halfBase, y + halfHeight, x, y - halfHeight);
        SDL_RenderDrawLine(r, x, y - halfHeight, x - halfBase, y + halfHeight);
    }
    else {
        SDL_RenderDrawLine(r, x - halfBase, y - halfHeight, x + halfBase, y - halfHeight);
        SDL_RenderDrawLine(r, x + halfBase, y - halfHeight, x, y + halfHeight);
        SDL_RenderDrawLine(r, x, y + halfHeight, x - halfBase, y - halfHeight);
    }

    SDL_RenderPresent(r);
}
#pragma endregion

//Circle definitions
#pragma region Circle

int Circle::getRadius() {
    return radius;
}
void Circle::setRadius(int nr) {
    if (nr > 0) {
        radius = nr;
    }
}
string Circle::getKind() {
    return "Circle";
}
int Circle::getHeight() {
    return -1;
}
void Circle::render(SDL_Renderer* r) {
    //draw shape at coordinate
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
    int center_x = getX();
    int center_y = getY();
    int theta = 0;
    int accuracy = 2;
    SDL_RenderDrawPoint(r, center_x, center_y);
    while (theta <= 2160) {
        int x = static_cast<int>(radius * cos(theta));
        int y = static_cast<int>(radius * sin(theta));
        SDL_RenderDrawPoint(r, center_x + x, center_y + y);
        theta += accuracy;
    }
    SDL_RenderPresent(r);
}
#pragma endregion 

//V definitions, for < and >
#pragma region V

int V::getBase() {
    return base;
}
int V::getHeight() {
    return height;
}
void V::setBase(int nb) {
    if (nb > 0) {
        base = nb;
    }
}
void V::setHeight(int nh) {
    if (nh > 0) {
        height = nh;
    }
}
string V::getKind() {
    if (lessThan) {
        return "lesser V";
    }
    else {
        return "greater V";
    }

}
void V::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
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

#pragma endregion

//X definitions
#pragma region X

int X::getLength1() {
    return line;
}

void X::setLength(int nl) {
    line = nl;
}
string X::getKind() {
    return "X";
}
int X::getHeight() {
    return -1;
}
void X::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
    int halfLine = (line / 2);
    SDL_RenderDrawPoint(r, x, y);
    SDL_RenderDrawLine(r, x - halfLine, y + halfLine, x + halfLine, y - halfLine);
    SDL_RenderDrawLine(r, x + halfLine, y + halfLine, x - halfLine, y - halfLine);
    SDL_RenderPresent(r);
}

#pragma endregion

//Star definitions
#pragma region Star

int Star::getLength() {
    return line;
}

void Star::setLength1(int nl) {
    line = nl;
}
string Star::getKind() {
    return "Star";
}
int Star::getHeight() {
    return -1;
}
void Star::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
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

#pragma endregion

//Z definitions
#pragma region Z

int Z::getWidth() {
    return width;
}
int Z::getHeight() {
    return height;
}
void Z::setWidth(int nw) {
    width = nw;
}
void Z::setHeight(int nh) {
    height = nh;
}
string Z::getKind() {
    return "Z";
}
void Z::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
    int newWidth = width / 2;
    int newHeight = height / 2;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
    SDL_RenderDrawLine(r, x, y, x, y);
    SDL_RenderDrawLine(r, x - newWidth, y - newHeight, x + newWidth, y - newHeight);
    SDL_RenderDrawLine(r, x + newWidth, y - newHeight, x - newWidth, y + newHeight);
    SDL_RenderDrawLine(r, x - newWidth, y + newHeight, x + newWidth, y + newHeight);

    SDL_RenderPresent(r);

}

#pragma endregion

//Card definitions
#pragma region Card

int Card::getWidth() {
    return width;
}
int Card::getHeight() {
    return height;
}
void Card::remove(SDL_Renderer* r) {
    SDL_RenderClear(r);
}
void Card::setType(Shape* ns) {
    s = ns;
}
Shape* Card::getType() {
    return s;
}
string Card::getKind() {
    return "Card";
}
void Card::render(SDL_Renderer* r) {
    //draw shape at coordinate
    int x = getX();
    int y = getY();
    int newWidth = width / 2;
    int newHeight = height / 2;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(r, getRed(), getGreen(), getBlue(), getAlpha());
    for (int i = 0; i < width; i++) {
        SDL_RenderDrawLine(r, x - newWidth + i, y - newHeight, x - newWidth + i, y + newHeight);
    }
    SDL_RenderPresent(r);
}

#pragma endregion 

#pragma region Memory

void Memory::initCards(SDL_Renderer* r) {
    //create the base cards
    int arr_r[4] = { 255, 255, 255, 0 };
    for (int i = 0; i < 20; i++) {
        Point2D p(arr_x[i], arr_y[i]);
        arr[i] = new Card(p, arr_r, i);
    }
}
void Memory::assignCards(SDL_Renderer* r) {
    //add different shapes to the cards
    Shape* s;
    int arr_order[20] = {};
    randomizeOrder(arr_order);
    for (int i = 0; i < 20; i++) {
        s = createCardTypes(arr_order[i], i);
        arr[i]->setType(s);
    }
    s = nullptr;
    delete s;
}
void Memory::clearAll(SDL_Renderer* r) {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    SDL_RenderClear(r);
    SDL_RenderPresent(r);
}
void Memory::renderAll(SDL_Renderer* r) {
    //render every card
    for (int i = 0; i < 20; i++) {
        if (arr[i] != nullptr)
            arr[i]->render(r);
    }
}
void Memory::randomizeOrder(int* arr) {
    srand(time(NULL));
    int slots[20];
    int count = 0;
    int* slotUsed;
    //randomize order
    while (count < 20) {
        int randomIndex = rand() % 20;
        slotUsed = find(begin(slots), end(slots), randomIndex);
        // When the element is not found, std::find returns the end of the range
        if (slotUsed != end(slots)) {

        }
        else {
            slots[count] = randomIndex;
            count++;
        }
    }
    //add shapes to original array
    for (int i = 0; i < 20; i++) {
        arr[i] = slots[i];
    }
    slotUsed = NULL;
    delete slotUsed;
}

Shape* Memory::createCardTypes(int i, int pos) {
    //Based off of index i, create and return a shape
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

//Methods that create and return shapes

Rectangle* Memory::newSqr(int pos) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 0, 255, 50, 255 };
    Rectangle* r = new Rectangle(p, arr_r, pos, 30, 30);
    r->setKind("Square");
    return r;
}
Rectangle* Memory::newRec(int pos) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 0, 100, 180, 255 };
    Rectangle* r = new Rectangle(p, arr_r, pos, 15, 40);
    r->setKind("Rectangle");
    return r;
}
Triangle* Memory::newTri(int pos, bool dir) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 100, 0, 100, 255 };
    Triangle* t = new Triangle(p, arr_r, pos, 20, 20, dir);
    return t;
}
Circle* Memory::newCir(int pos) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 50, 150, 50, 255 };
    Circle* c = new Circle(p, arr_r, pos, 20);
    return c;
}
V* Memory::newV(int pos, bool less) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 50, 175, 255, 255 };
    V* v = new V(p, arr_r, pos, 20, 20, less);
    return v;
}
X* Memory::newX(int pos) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 25, 150, 150, 255 };
    X* x = new X(p, arr_r, pos, 20);
    return x;
}
Star* Memory::newStar(int pos) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 50, 255, 50, 255 };
    Star* s = new Star(p, arr_r, pos, 40);
    return s;
}
Z* Memory::newZ(int pos) {
    Point2D p(arr_x[pos], arr_y[pos]);
    int arr_r[4] = { 100, 100, 100, 255 };
    Z* z = new Z(p, arr_r, pos, 20, 20);
    return z;
}

void Memory::fillArrays(int* arr_x, int* arr_y) {
    //fill the 2 arrays with x and y coordinates respectively, 4 rows of 5 cards each
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

#pragma endregion



void revealCard(int i, Memory m, SDL_Renderer* r) {
    //render card at position i
    m.arr[i]->getType()->render(r);
}

int main(int arg, char* args[])
{
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    Memory m(renderer);
    SDL_Event event;

    //Variables for while loop to work
    bool quit = false;
    int cardsRevealed = 0;
    int cardsFound = 0;
    int tries = 0;
    string firstCard;
    string secondCard;
    int firstIndex;
    int secondIndex;

    while (!quit) {
        if (SDL_PollEvent(&event)) {
            if (cardsFound == 20) {
                cout << "\nYou win!\nTotal tries: " << tries << "\nPress r to reset\nPress q to quit\n";
            }

            if (event.type == SDL_QUIT) {
                quit = true;
            }
            //On left click
            else if (event.button.button == SDL_BUTTON_LEFT) {
                if (event.type == SDL_MOUSEBUTTONUP) { //Once let go off left click
                    int x, y;
                    //x and y coordinates of click
                    x = event.button.x;
                    y = event.button.y;
                    if (cardsRevealed == 2) { //If 2 cards are flipped
                        tries++;
                        if (firstCard == secondCard && firstIndex != secondIndex) {
                            cout << endl << firstCard << " matched\n";
                            for (int i = 0; i < 20; i++) { //Find the 2 flipped cards and remove from list
                                if (m.arr[i] != nullptr) {
                                    if (m.arr[i]->getType()->getKind() == firstCard) {
                                        cout << firstCard << " card removed from the board\n";
                                        m.arr[i] = nullptr;
                                        cardsFound += 1;
                                    }
                                }
                            }
                        }
                        else {
                            cout << "\nCards did not match\n";
                        }
                        cardsRevealed = 0;
                        m.clearAll(renderer);
                        m.renderAll(renderer);
                    }
                    else {
                        for (int i = 0; i < 20; i++) {
                            if (m.arr[i] != nullptr) { //if it exists
                                if (x <= m.arr_x[i] + (m.arr[i]->getWidth() / 2) && x >= m.arr_x[i] - (m.arr[i]->getWidth() / 2)) { //if click is within a card's width
                                    if (y <= m.arr_y[i] + (m.arr[i]->getHeight() / 2) && y >= m.arr_y[i] - (m.arr[i]->getHeight() / 2)) {   //if click is within a card's height
                                        if (cardsRevealed == 0) { //first flip
                                            firstCard = m.arr[i]->getType()->getKind();
                                            firstIndex = m.arr[i]->getType()->getIndex();
                                            cardsRevealed++;
                                        }
                                        else if (cardsRevealed == 1 && m.arr[i]->getType()->getIndex() != firstIndex) { //second flip, checks that same card isnt flipped twice
                                            secondCard = m.arr[i]->getType()->getKind();
                                            secondIndex = m.arr[i]->getType()->getIndex();
                                            cardsRevealed++;
                                        }
                                        revealCard(i, m, renderer);
                                    }
                                }
                            }
                        }
                    }

                }

            }

            else if (event.type != SDL_MOUSEMOTION) {
                switch (event.key.keysym.sym) {
                    //Quit on q
                case SDLK_q:
                    cout << "\nQuitting\n";
                    quit = true;
                    break;
                    //Reset game on r
                case SDLK_r:
                    if (event.type == SDL_KEYUP) {
                        cout << "\nResetting\n";
                        cardsRevealed = 0;
                        tries = 0;
                        cardsFound = 0;
                        m.clearAll(renderer);
                        m.initCards(renderer);
                        m.assignCards(renderer);
                        m.renderAll(renderer);
                    }

                }
            }

        }
    }
    //Cleanup
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}