#include "Cell.h"
#include <iostream>
#include <vector>
#include <time.h> //for random seed
#include <Windows.h> //GetAsyncKeyState
using namespace std;
/** \brief Function that prints to the console all Cell objects that are currently stored in a vector.

	It's used for debugging.
*/
void printArray(vector<Cell> vector) {
	cout << "Print Array:" << endl;
	for (unsigned int i = 0; i < vector.size(); i++) {
		vector[i].printCell();
	}
}

/** \brief Updates the screen for the next game state.

	The purpose of this function is to go through aliveCellArray and update the screen using Cell::createRectangle, method that draws 'alive' or 'dead' rectangles(Cells).
		\param SDL_Window - window object from SDL library
		\param SDL_Renderer - 2D rendering context for a window from SDL library
		\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
		\param scale - size of Cell side
		\param speed - delay between game states
*/
void updateScreen(SDL_Window** window, SDL_Renderer** renderer, vector<Cell>* aliveCellArrayPointer, int scale, int speed) {

	for (unsigned int i = 0; i < (*aliveCellArrayPointer).size(); i++) {
		(*aliveCellArrayPointer).at(i).createRectangle(window, renderer, scale);
	}
	//Set delay between screen updates
	SDL_Delay(2000 - speed);
	//Update screen
	SDL_RenderPresent(*renderer);
}

/** \brief Updates alive status of main Cell matrix based on their status in aliveCellArray

The purpose of this function is to go through aliveCellArray, get every Cell posY and posX and update their status in cellMatrix.
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param fromArray - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param size - size of Cell side
*/
void updateMainMatrix(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* fromArray, int scale) {
	for (unsigned int i = 0; i < (*fromArray).size(); i++) {
		int posY = (*fromArray)[i].getPosY() / scale;
		int posX = (*fromArray)[i].getPosX() / scale;
		(*cellMatrixPointer)[posY][posX].setAlive((*fromArray)[i].getIsAlive());
	}
}

/** \brief Creates graphical grid on window.

The purpose of this function is to draw vertical and horizontal lines based on window width, window height and scale(based on Cell size).
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param windowWidth - window width based on current screen resolution
\param windowHeight - window height based on current screen resolution
\param scale - size of Cell side
*/
void createGrid(SDL_Window** window, SDL_Renderer** renderer, int windowWidth, int windowHeight, int scale) {
	//Render fill window background
	SDL_Rect fillRect = { 0, 0, windowWidth, windowHeight };
	SDL_SetRenderDrawColor(*renderer, 0x55, 0x55, 0x55, 0xFF);
	SDL_RenderFillRect(*renderer, &fillRect);

	//Draw horizontal lines
	SDL_SetRenderDrawColor(*renderer, 0x44, 0x44, 0x44, 0xFF);
	for (int i = 0; i < windowHeight; i += scale) {
		SDL_RenderDrawLine(*renderer, 0, i, windowWidth, i);
		SDL_RenderDrawLine(*renderer, 0, i - 1, windowWidth, i - 1);
	}
	//Draw vertical lines
	for (int i = 0; i < windowWidth; i += scale) {
		SDL_RenderDrawLine(*renderer, i, 0, i, windowHeight);
		SDL_RenderDrawLine(*renderer, i - 1, 0, i - 1, windowHeight);
	}
	//Update screen
	SDL_RenderPresent(*renderer);
}
/** \brief Gets screen resolution.

The purpose of this function get screen resolution width and height dimensions and store them in windowWidth and windowHeight variables.
\param windowWidth - pointer to window width variable
\param windowHeight - pointer to window height variable
*/
void getScreenResolution(int* windowWidth, int* windowHeight) {

	SDL_Rect rect;
	if (SDL_GetDisplayBounds(0, &rect) != 0) {
		cout << "Failed to get display bounds! SDL_Error: " << SDL_GetError() << endl;
	}
	*windowWidth = rect.w;
	*windowHeight = rect.h;
}

/** \brief Creates loading screen.

The purpose of this function is to create a loading screen which displays 'CONWAY' sign from alive cells. It's showed during the intial creation of objects in the main cell matrix.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param windowWidth - window width based on current screen resolution
\param windowHeight - window height based on current screen resolution
\param scale - size of Cell side
*/
void createLoadingScreen(SDL_Window** window, SDL_Renderer** renderer, vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int windowWidth, int windowHeight, int scale) {
	int beginingX = windowWidth / scale / 2 - 15;
	int beginingY = windowHeight / scale / 2 - 3;

	//C
	(*cellMatrixPointer)[beginingY][beginingX].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 1].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 2].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 3].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 1].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 2].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 3].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);

	//O
	(*cellMatrixPointer)[beginingY][beginingX + 5].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 6].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 7].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 8].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 5].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 5].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 5].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 5].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 8].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 8].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 8].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 8].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 6].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 7].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);

	//N
	(*cellMatrixPointer)[beginingY][beginingX + 10].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 10].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 10].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 10].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 10].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 13].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 13].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 13].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 13].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 13].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 11].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 12].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);

	//W
	(*cellMatrixPointer)[beginingY][beginingX + 15].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 15].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 15].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 15].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 15].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 19].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 19].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 19].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 19].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 19].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 18].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 17].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 16].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);

	//A
	(*cellMatrixPointer)[beginingY][beginingX + 21].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 21].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 21].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 21].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 21].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 24].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 24].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 24].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 24].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 24].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 22].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 23].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 22].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 23].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);

	//Y
	(*cellMatrixPointer)[beginingY][beginingX + 30].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 29].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY][beginingX + 26].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 1][beginingX + 27].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 2][beginingX + 28].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 3][beginingX + 28].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
	(*cellMatrixPointer)[beginingY + 4][beginingX + 28].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);

	//Update screen
	SDL_RenderPresent(*renderer);
	for (unsigned int i = beginingY; i < (*cellMatrixPointer).size() - 1; i++) {
		for (unsigned int j = beginingX; j < (*cellMatrixPointer)[0].size() - 1; j++) {
			if ((*cellMatrixPointer)[i][j].getIsAlive()) (*cellMatrixPointer)[i][j].killCell(window, renderer, scale);
		}
	}
	vector<Cell>().swap(*aliveCellArrayPointer);
}

/** \brief Creates random seed generator.

The purpose of this function is to create random alive cells based on set seed.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param windowWidth - window width based on current screen resolution
\param windowHeight - window height based on current screen resolution
\param scale - size of Cell side
\param seed - seed variable determines how many alive Cells are going to be created
*/
void createRandomGenerator(SDL_Window** window, SDL_Renderer** renderer, vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int windowWidth, int windowHeight, int scale, int seed) {
	int random;
	vector<int> iContainer;
	vector<int> jContainer;

	for (int i = 200 / scale; (unsigned)i < (*cellMatrixPointer).size() - 200 / scale; i++) {
		for (int j = 200 / scale; (unsigned)j < (*cellMatrixPointer)[0].size() - 200 / scale; j++) {
			random = rand() % 100 + 1;
			if (random <= seed) {
				(*cellMatrixPointer)[i][j].createAliveCell(window, renderer, cellMatrixPointer, aliveCellArrayPointer, scale);
				iContainer.push_back(i);
				jContainer.push_back(j);
			}
		}
	}
	for (int i = 0; (unsigned)i < iContainer.size(); i++) {
		(*cellMatrixPointer)[iContainer[i]][jContainer[i]].addNeighborsToArray(cellMatrixPointer, aliveCellArrayPointer, scale);
	}
}

/** \brief Creates Cell matrix.

The purpose of this function is to create Cell matrix from vectors. Each vector 'row' is a vector containing Cell objects.
\param windowWidth - window width based on current screen resolution
\param windowHeight - window height based on current screen resolution
\param scale - size of Cell side
*/
vector< vector<Cell> > createCellMatrix(int windowWidth, int windowHeight, int scale) {
	const int NumOfColumns = windowWidth / scale;
	const int NumOfRows = windowHeight / scale;
	vector<Cell> row;
	vector< vector<Cell> > cellMatrix;
	for (int i = 0; i < NumOfRows; i++) {
		for (int j = 0; j < NumOfColumns; j++) {
			//insert cells in row
			row.push_back(Cell(j * scale, i * scale));
		}
		//insert row into matrix
		cellMatrix.push_back(row);
		vector<Cell>().swap(row);
	}
	return cellMatrix;
}

/** \brief Cleanup function.

The purpose of this function is to cleanup memory before program quits.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
*/

void quit(SDL_Window* window, SDL_Renderer* renderer) {
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
	//close console
	exit(0);
}

/** \brief Starts the game.

The purpose of this function is to start the game, that means set Cell matrix, run loading screen function, run random generator and call in a loop functions like countAliveNeighbors and update the screen.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param windowWidth - window width based on current screen resolution
\param windowHeight - window height based on current screen resolution
\param scale - size of Cell side
\param seed - seed variable determines how many alive Cells are going to be created
\param variant - determines which game variant is set
*/
void playGame(SDL_Window** window, SDL_Renderer** renderer, int windowWidth, int windowHeight, int scale, int speed, int seed, int variant) {
	srand((unsigned int)time(NULL));
	vector< vector<Cell> > cellMatrix = createCellMatrix(windowWidth, windowHeight, scale);
	vector<Cell> aliveCellArray;
	vector<Cell> aliveCellArrayBuffer;

	createLoadingScreen(window, renderer, &cellMatrix, &aliveCellArray, windowWidth, windowHeight, scale);

	createRandomGenerator(window, renderer, &cellMatrix, &aliveCellArray, windowWidth, windowHeight, scale, seed);
	//Update screen
	SDL_RenderPresent(*renderer);

	//start game
	while (true) {
		//if Escape key pressed quit
		if (GetAsyncKeyState(VK_ESCAPE)) break;

		//if 'X' pressed quit
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)	quit(*window, *renderer);

		for (unsigned int i = 0; i < aliveCellArray.size(); i++) {
			aliveCellArray[i].countAliveNeighbors(&cellMatrix, &aliveCellArray, &aliveCellArrayBuffer, scale, variant);
		}

		updateMainMatrix(&cellMatrix, &aliveCellArray, scale);
		int size = aliveCellArrayBuffer.size();
		for (int i = 0; i < size; i++) {
			aliveCellArrayBuffer[i].addNeighborsToArray(&cellMatrix, &aliveCellArrayBuffer, scale);
		}

		updateScreen(window, renderer, &aliveCellArray, scale, speed);
		vector<Cell>().swap(aliveCellArray);
		aliveCellArray = move(aliveCellArrayBuffer);
		vector<Cell>().swap(aliveCellArrayBuffer);
	}
}

/** \brief Sets program window.

The purpose of this function is to create program window on which all graphics will be shown.
\param scale - size of Cell side
\param seed - seed variable determines how many alive Cells are going to be created
\param seed - seed variable determines how many alive Cells are going to be created
\param variant - determines which game variant is set
*/
void setWindow(int scale, int speed, int seed, int variant) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	int windowWidth = 0;
	int windowHeight = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Sdl could not initialize! SDL_Error:" << SDL_GetError() << endl;
	}
	else {
		//Create window
		getScreenResolution(&windowWidth, &windowHeight);
		windowHeight -= 60;
		window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	}
	if (!window) {
		cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
	}
	else {
		//Create renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		//Fill the surface white
		createGrid(&window, &renderer, windowWidth, windowHeight, scale);
		//Start the game
		playGame(&window, &renderer, windowWidth, windowHeight, scale, speed, seed, variant);
	}
	quit(window, renderer);
}
