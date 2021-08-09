#include <iostream>
#include <SDL.h>
#include "task2.h"
#include <vector>
#include <ctime>
#include <string>

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

void testRendering(vector<Shape*>shapes, SDL_Renderer* r) {
    shapes[0]->render(r);
    shapes[1]->render(r);
    shapes[2]->render(r);
}
void drawIGuess(int i, Memory m, SDL_Renderer *r) {
    m.arr[i]->getType()->render(r);
}

int main(int arg, char* args[])
{  
    
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    Memory m(renderer);
    SDL_Event event;
    
    bool quit = false;
    int cardsRevealed = 0;
    int cardsFound = 0;
    int tries = 0;
    string firstCard;
    string secondCard;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            int low = 60;
            int randx = low + rand() % 400;
            int randy = low + rand() % 300;
            int size_x = low + rand() % 250;
            int size_y = low + rand() % 250;
            int size_rad = low + rand() % 250;

            if (cardsFound == 20) {
                cout << "\nYou win!\nTotal tries: " << tries << endl;
                quit = true;
            }

            Point2D p(randx, randy);
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
                        if (firstCard == secondCard) {
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
                            if (m.arr[i] != nullptr) {
                                if (x <= m.arr_x[i] + (m.arr[i]->getWidth() / 2) && x >= m.arr_x[i] - (m.arr[i]->getWidth() / 2)) {
                                    if (y <= m.arr_y[i] + (m.arr[i]->getHeight() / 2) && y >= m.arr_y[i] - (m.arr[i]->getHeight() / 2)) {   
                                        if (cardsRevealed == 0) {
                                            firstCard = m.arr[i]->getType()->getKind();
                                        }
                                        else if (cardsRevealed == 1) {
                                            secondCard = m.arr[i]->getType()->getKind();
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
            else if (event.button.button == SDL_BUTTON_RIGHT) {
                cardsRevealed = 0;
                tries = 0;
                m.clearAll(renderer);
                m.renderAll(renderer);
            }

            /*else if (SDL_KEYUP) {
                switch (event.key.keysym.sym) {

                case SDLK_q:
                    cout << "bruh";
                    quit = true;
                    break;
                }
            }*/
            
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit(); 
    return 0;
}