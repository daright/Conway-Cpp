#include "Cell.h"
#include <iostream>
#include <vector>
#include <SDL.h> //graphics library
using namespace std;
/** \class Cell
	\brief Class used to store information about the state of a single cell block.

	This class contains information of alive state, neighbor count, position on the board and methods to count neighbors, check if neighbors are alive and to update the screen if cell dies or is alive.
*/
/** \brief Class default constructor.

	Sets isAlive parameter to false and neighborCounter to 0.
*/
Cell::Cell() {
	this->isAlive = false;
	this->neighborCounter = 0;
}

/** \brief Class constructor with position parameters.

Sets isAlive parameter to false and neighborCounter to 0, enables to set Cell postition relative to the screen.
\param posX - vertical position relative to the screen
\param posY - horizontal position relative to the screen
*/
Cell::Cell(int posX, int posY) {
	this->isAlive = false;
	this->posX = posX;
	this->posY = posY;
	this->neighborCounter = 0;
}

/** \brief Class equals operator.

Enables to check if two cells are equal, equality is based only on position.
*/
bool Cell::operator==(const Cell &cell) const {
	if (this->posX == cell.posX && this->posY == cell.posY) return true;
	return false;
}

/** \brief Class not equal operator.

Enables to check if two cells are not equal, not equality is based only on position.
*/
bool Cell::operator!=(const Cell &cell) const {
	return !(*this == cell);
}

/** \brief Returns isAlive parameter.

\return isAlive - boolean value, true if cell is alive, false if it's dead.
*/
bool Cell::getIsAlive() {
	return isAlive;
}

/** \brief Sets isAlive parameter.

\param isAlive - boolean value, true if cell is alive, false if it's dead.
*/
void Cell::setAlive(bool isAlive) {
	this->isAlive = isAlive;
}

/** \brief Adds alive cell to an array.

Method is used to add alive cells to an array.
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param vectorArray - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param scale - size of Cell side
*/
void Cell::addToArray(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* vectorArray, int scale) {

	if ((find((*vectorArray).begin(), (*vectorArray).end(), *this)) == (*vectorArray).end()) {
		(*vectorArray).push_back(*this);
	}
}

/** \brief Adds neighbors of alive cells to an array.

This method is used in conjunction with Cell::addToArray.
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param scale - size of Cell side
*/
void Cell::addNeighborsToArray(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int scale) {

	int posX = this->posX / scale;
	int posY = this->posY / scale;
	Cell current;
	if (posX - 1 < 0 || posY - 1 < 0 || (unsigned)posX + 1 > (*cellMatrixPointer)[0].size() || (unsigned)posY + 1 > (*cellMatrixPointer).size()) {
		return;
	}
	else {
		//top
		current = (*cellMatrixPointer)[posY + 1][posX];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		//top right
		current = (*cellMatrixPointer)[posY + 1][posX + 1];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		//right
		current = (*cellMatrixPointer)[posY][posX + 1];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		//bottom right
		current = (*cellMatrixPointer)[posY - 1][posX + 1];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		//bottom
		current = (*cellMatrixPointer)[posY - 1][posX];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		//bottom left
		current = (*cellMatrixPointer)[posY - 1][posX - 1];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		//left
		current = (*cellMatrixPointer)[posY][posX - 1];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}

		// top left
		current = (*cellMatrixPointer)[posY + 1][posX - 1];
		if (find((*aliveCellArrayPointer).begin(), (*aliveCellArrayPointer).end(), current) == (*aliveCellArrayPointer).end()) {
			(*aliveCellArrayPointer).push_back(current);
		}
	}
}
/** \brief Creates an alive Cell object.

Sets isAlive parameter to true, adds this Cell to aliveCellArray and draws it on the screen.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param scale - size of Cell side
*/
void Cell::createAliveCell(SDL_Window** window, SDL_Renderer** renderer, vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, int scale) {
	this->isAlive = true;
	this->addToArray(cellMatrixPointer, aliveCellArrayPointer, scale);
	this->createRectangle(window, renderer, scale);
}

/** \brief 'Kills' an alive Cell object.

Sets isAlive parameter to false, and deletes it from the screen.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param scale - size of Cell side
*/
void Cell::killCell(SDL_Window** window, SDL_Renderer** renderer, int scale) {
	this->isAlive = false;
	this->createRectangle(window, renderer, scale);
}

/** \brief Counts how many objects arround this Cell are alive.

Checks 8 neighbors around this Cell if they are alive, and if so incriments it's neighborCounter by the amount of alive neighbor Cells. 
After that it checks if this Cell is going to be alive or dead in the next state which is based on the picked variant.
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param scale - size of Cell side
\param variant - determines which game variant is set
*/
void Cell::countAliveNeighbors(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale, int variant) {

	this->neighborCounter = 0;
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	if (posX - 1 < 0 || posY - 1 < 0 || (unsigned)posX + 1 > (*cellMatrixPointer)[0].size() - 1 || (unsigned)posY + 1 > (*cellMatrixPointer).size() - 1) {
		return;
	}
	else {
		//top
		if ((*cellMatrixPointer)[posY + 1][posX].isAlive) this->neighborCounter++;
		//top right
		if ((*cellMatrixPointer)[posY + 1][posX + 1].isAlive) this->neighborCounter++;
		//right
		if ((*cellMatrixPointer)[posY][posX + 1].isAlive) this->neighborCounter++;
		//bottom right
		if ((*cellMatrixPointer)[posY - 1][posX + 1].isAlive) this->neighborCounter++;
		//bottom
		if ((*cellMatrixPointer)[posY - 1][posX].isAlive) this->neighborCounter++;
		//bottom left
		if ((*cellMatrixPointer)[posY - 1][posX - 1].isAlive) this->neighborCounter++;
		//left
		if ((*cellMatrixPointer)[posY][posX - 1].isAlive) this->neighborCounter++;
		// top left
		if ((*cellMatrixPointer)[posY + 1][posX - 1].isAlive) this->neighborCounter++;
		if (variant == 1) this->checkLifeStatus1(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 2) this->checkLifeStatus2(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 3) this->checkLifeStatus3(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 4) this->checkLifeStatus4(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 5) this->checkLifeStatus5(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 6) this->checkLifeStatus6(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 7) this->checkLifeStatus7(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
		else if (variant == 8) this->checkLifeStatus8(cellMatrixPointer, aliveCellArrayPointer, aliveCellArrayBufferPointer, scale);
	}
}
//Conway rules 23/3 (liczba sasiadów dla których komórki przezywaja/liczba sasiadów dla których martwe komórki ozywaja)
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state. 
This method is for variant 23/3(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus1(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (neighborCounter < 2) {
		this->setAlive(false);
	}
	else if (!isAlive && neighborCounter == 3) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (isAlive && (neighborCounter == 2 || neighborCounter == 3)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//34 / 34
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 34/34(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus2(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (!isAlive && (neighborCounter == 3 || neighborCounter == 4)) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (isAlive && (neighborCounter == 3 || neighborCounter == 4)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//245/368
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 245/368(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus3(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (isAlive && (neighborCounter == 2 || neighborCounter == 4 || neighborCounter == 5)) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (!isAlive && (neighborCounter == 3 || neighborCounter == 6 || neighborCounter == 8)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//238/357
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 238/357(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus4(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (isAlive && (neighborCounter == 2 || neighborCounter == 3 || neighborCounter == 8)) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (!isAlive && (neighborCounter == 3 || neighborCounter == 5 || neighborCounter == 7)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//125/36
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 125/36(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus5(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (isAlive && (neighborCounter == 1 || neighborCounter == 2 || neighborCounter == 5)) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (!isAlive && (neighborCounter == 3 || neighborCounter == 6)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//5/345
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 5/345(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus6(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (isAlive && neighborCounter == 5) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (!isAlive && (neighborCounter == 3 || neighborCounter == 4 || neighborCounter == 5)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//235678/3678
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 235678/3678(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus7(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (isAlive && (neighborCounter > 4 || neighborCounter == 2 || neighborCounter || 3)) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (!isAlive && (neighborCounter == 3 || neighborCounter > 5)) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}

//012345678/1
/** \brief Checks if current Cell is going to be alive in the next state.

Based on picked variant and neighbor counter method determines if current cell will live in the next game state.
This method is for variant 012345678/1(number of alive neighbors for which cells stay alive/number of alive neighbors for which cells are set alive).
\param cellMatrixPointer - pointer to cellMatrix(matrix that stores all Cells)
\param aliveCellArrayPointer - pointer to aliveCellArray(array that stores only alive Cells and their neighbors)
\param aliveCellArrayBufferPointer - pointer to aliveCellArrayBuffer(array that stores only alive Cells and their neighbors that are going to live in the next game state)
\param scale - size of Cell side
*/
void Cell::checkLifeStatus8(vector< vector<Cell> >* cellMatrixPointer, vector<Cell>* aliveCellArrayPointer, vector<Cell>* aliveCellArrayBufferPointer, int scale) {
	int posX = this->posX / scale;
	int posY = this->posY / scale;
	//	cout << "Check life status of [" << posY << "][" << posX << "] Neighbor counter: " << neighborCounter << endl;

	if (isAlive && neighborCounter > 0) {
		this->setAlive(true);
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else if (!isAlive && neighborCounter == 1) {
		//	cout << "adding [" << posY << "][" << posX << "]" << endl;
		this->setAlive(true);
		if ((find((*aliveCellArrayBufferPointer).begin(), (*aliveCellArrayBufferPointer).end(), *this)) == (*aliveCellArrayBufferPointer).end())
			this->addToArray(cellMatrixPointer, aliveCellArrayBufferPointer, scale);
	}
	else {
		this->setAlive(false);
	}
}
/** \brief Draws cell on screen.

Based on Cell isAlive value method draws appropriate Cell on screen window.
\param SDL_Window - window object from SDL library
\param SDL_Renderer - 2D rendering context for a window from SDL library
\param scale - size of Cell side
*/
void Cell::createRectangle(SDL_Window** window, SDL_Renderer** renderer, int scale) {
	SDL_Rect fillRect = { posX + 1, posY + 1, scale - 2, scale - 2 };
	SDL_Rect outline = { posX, posY, scale, scale };

	if (isAlive) {
		SDL_SetRenderDrawColor(*renderer, 0xAA, 0xAA, 0xAA, 0xFF);
		SDL_RenderFillRect(*renderer, &fillRect);
		SDL_SetRenderDrawColor(*renderer, 0xDB, 0xDB, 0x93, 0xFF);
		SDL_RenderDrawRect(*renderer, &outline);
	}
	else {
		SDL_SetRenderDrawColor(*renderer, 0x55, 0x55, 0x55, 0xFF);
		SDL_RenderFillRect(*renderer, &fillRect);
		SDL_SetRenderDrawColor(*renderer, 0x44, 0x44, 0x44, 0xFF);
		SDL_RenderDrawRect(*renderer, &outline);
	}
}

