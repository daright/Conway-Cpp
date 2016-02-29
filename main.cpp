#include <iostream>
#include <string>
#include <SDL.h> //graphics library
#include "Cell.h"
#include "screen.h"
using namespace std;

/** \brief Opens the console and takes initial input from user and sets parameters for cell size, delay, seed and game variant.
*
*	Size takes values from 2 to 10 and it means that side of one cell is 2-10 pixels.
*	Speed sets the delay between two states.
*	Seed sets how many cells are alive at runtime.
*	Variant takes values from 1 to 7 and it sets the rules that apply to the game.
*/
void takeInput() {
	cout << "Conway's Game of Life settings:" << endl << endl;
	string input;
	int scale;
	do {
		cout << "Set size of square cell in pixels (enter value from 2 to 10): ";
		cin >> input;
		scale = stoi(input);
	} while (scale < 2 || scale > 10);
	int speed;
	do {
		cout << "Set delay in miliseconds (enter value from 0 to 2000): ";
		cin >> input;
		speed = 2000 - stoi(input);
	} while (speed < 0 || speed > 2000);
	int seed;
	cout << "Set seed (enter value from 1 to 100): ";
	cin >> input;
	seed = stoi(input);
	if (seed < 1 || seed > 100) {
		cout << "Set to default seed value 7." << endl;
		seed = 7;
	}
	int variant;
	cout << "List of variants: " << endl;
	cout << "1. 23/3 - Basic Conway rules." << endl;
	cout << "2. 34/34 - Many small oscilators and ships." << endl;
	cout << "3. 245/368 - Cells die fast, some small oscilators and ships." << endl;
	cout << "4. 238/357 - Similar to basic Conway." << endl;
	cout << "5. 125/36 - Many oscilators and ships" << endl;
	cout << "6. 5/345 - Oscilators." << endl;
	cout << "7. 235678/3678 - Growing spots, cells never die." << endl;
	cout << "8. 245/368 - Cells create square-like shapes, cells never die." << endl;
	cout << "Set variant (enter value from 1 to 8): ";
	cin >> input;
	variant = stoi(input);
	if (variant < 1 || variant > 8) {
		cout << "Set to default variant 1." << endl;
		variant = 1;
	}
	setWindow(scale, speed, seed, variant);
}

int main(int argc, char *argsp[]) {
	takeInput();
	return 0;
}