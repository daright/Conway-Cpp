#pragma once
#include "Cell.h"
#include <iostream>
#include <vector>
#include <time.h> //for random seed
#include <Windows.h> //GetAsyncKeyState

using namespace std;

void printArray(vector<Cell> vector);
void updateScreen(SDL_Window** window, SDL_Renderer** renderer, vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int scale, int speed);
void updateMainMatrix(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* fromArray, int scale);
void createGrid(SDL_Window** window, SDL_Renderer** renderer, int windowWidth, int windowHeight, int scale);
void getScreenResolution(int* windowWidth, int* windowHeight);
void createLoadingScreen(SDL_Window** window, SDL_Renderer** renderer, vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int windowWidth, int windowHeight, int scale);
void createRandomGenerator(SDL_Window** window, SDL_Renderer** renderer, vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int windowWidth, int windowHeight, int scale, int seed);
vector< vector<Cell> > createCellMatrix(int windowWidth, int windowHeight, int scale);
void quit(SDL_Window* window, SDL_Renderer* renderer);
void playGame(SDL_Window** window, SDL_Renderer** renderer, int windowWidth, int windowHeight, int scale, int speed, int seed, int variant);
void setWindow(int scale, int speed, int seed, int variant);