#include <iostream>
#include <SDL.h>
#include <vector>
#include <ctime>
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
        return "UpwardTriangle";
    }
    else {
        return "DownwardTriangle";
    }

}
void Triangle::render(SDL_Renderer* r) {
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
void Memory::randomizeOrder(int* arr) {
    srand(time(NULL));
    int slots[20];
    int count = 0;
    int* slotUsed;
    while (count < 20) {
        int randomIndex = rand() % 20;
        slotUsed = find(begin(slots), end(slots), randomIndex);
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
    //delete[] slotUsed;
   
}


void drawIGuess(int i, Memory m, SDL_Renderer *r) {
    m.arr[i]->getType()->render(r);
}

int main(int arg, char* args[])
{    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    Memory m(renderer);
    SDL_Event event;   
    
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
                cout << "\nYou win!\nTotal tries: " << tries << endl;
            }
          
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.button.button == SDL_BUTTON_LEFT) {
                if (event.type == SDL_MOUSEBUTTONUP) {
                    int x, y;
                    x = event.button.x;
                    y = event.button.y;
                    if (cardsRevealed == 2) {
                        tries++;
                        cout << endl << firstCard << " and " << secondCard << endl;
                        if (firstCard == secondCard && firstIndex != secondIndex) {
                            cout << "\nThe same\n";
                            for (int i = 0; i < 20; i++) {
                                if (m.arr[i] != nullptr) {
                                    if (m.arr[i]->getType()->getKind() == firstCard) {
                                        cout << "\nwow";
                                        m.arr[i] = nullptr;
                                        cardsFound += 1;
                                    }
                                }
                            }
                        }
                        cardsRevealed = 0;
                        m.clearAll(renderer);
                        m.renderAll(renderer);
                    }
                    else {
                        for (int i = 0; i < 20; i++) {
                            if (m.arr[i] != nullptr) { //if it exists
                                if (x <= m.arr_x[i] + (m.arr[i]->getWidth() / 2) && x >= m.arr_x[i] - (m.arr[i]->getWidth() / 2)) { //if click is on a card width
                                    if (y <= m.arr_y[i] + (m.arr[i]->getHeight() / 2) && y >= m.arr_y[i] - (m.arr[i]->getHeight() / 2)) {   //if click is on a card height
                                        if (cardsRevealed == 0) {
                                            firstCard = m.arr[i]->getType()->getKind();
                                            firstIndex = m.arr[i]->getType()->getIndex();
                                        }
                                        else if (cardsRevealed == 1) {
                                            secondCard = m.arr[i]->getType()->getKind();
                                            secondIndex = m.arr[i]->getType()->getIndex();
                                        }
                                        cardsRevealed++;                                      
                                        drawIGuess(i, m, renderer);                                       
                                    }
                                }
                            }
                        }
                    }
                
                }
                                                           
            }

           else if(event.type != SDL_MOUSEMOTION)  {
                switch (event.key.keysym.sym) {

                case SDLK_q:
                    cout << "bruh";
                    quit = true;
                    break;
                case SDLK_r:
                    if (event.type == SDL_KEYUP) {
                        cout << "test\n";
                        cardsRevealed = 0;
                        tries = 0;
                        cardsFound = 0;
                        m.clearAll(renderer);
                        m.initCards(renderer);
                        m.doStuff(renderer);
                        m.renderAll(renderer);
                    }
                    
                }                                
            }
            
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit(); 
    return 0;
}