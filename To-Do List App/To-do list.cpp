// disables compiler warnings
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
                

#include "Case.h" // Structure
#include "addCase.h" // Basic functions for working with tasks
#include "Menu.h" // all Menu
#include "Save.h" // Work with file
#include "Search.h" // Functions for search

using namespace std;
using namespace std::chrono;

int main() {
	// The main array
	vector<Case> task = loadFile();
	menu(task);
	saveFile(task);
	return 0;

}
