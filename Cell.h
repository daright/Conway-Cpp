#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
using namespace std;

class Cell {
private:
	bool isAlive; /**< bool Value isAlive stores information about life state of a Cell object. */
	int posX, posY;
	int neighborCounter;

public:
	Cell();
	Cell(int, int);
	bool operator==(const Cell & cell) const;
	bool operator!=(const Cell & cell) const;
	bool getIsAlive();
	void setAlive(bool);
	/** \brief Returns posX of a Cell.

	\return posX - vertical position relative to the screen
	*/
	int getPosX() {
		return posX;
	}
	/** \brief Returns posX of a Cell.

	\return posY - horizontal position relative to the screen
	*/
	int getPosY() {
		return posY;
	}
	void addToArray(vector< vector<Cell> >*, vector<Cell>*, int);
	void addNeighborsToArray(vector< vector<Cell> >*, vector<Cell>*, int);
	void createAliveCell(SDL_Window**, SDL_Renderer**, vector< vector<Cell> >*, vector<Cell>*, int);
	void killCell(SDL_Window**, SDL_Renderer**, int);
	void countAliveNeighbors(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int, int);
	void checkLifeStatus1(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus2(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus3(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus4(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus5(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus6(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus7(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void checkLifeStatus8(vector< vector<Cell> >*, vector<Cell>*, vector<Cell>*, int);
	void createRectangle(SDL_Window**, SDL_Renderer**, int);
	/** \brief Prints Cell informations to the console.

	Method used for debugging
	*/
	void printCell() {
		cout << "Cell [" << posY / 10 << "][" << posX / 10 << "]" << endl;
		cout << "isAlive = " << isAlive << endl;
		cout << "Neighbor counter = " << neighborCounter << endl;
		cout << endl;
	}
};
