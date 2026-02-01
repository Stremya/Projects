// disables compiler warnings
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
                
// Structure
#include "Case.h"
// Basic functions for working with tasks
#include "addCase.h"
// all Menu
#include "Menu.h"
// Work with file
#include "Save.h"
// Functions for search
#include "Search.h"

using namespace std;
using namespace std::chrono;

int main() {
	// The main array
	vector<Case> task = loadFile();
	menu(task);
	saveFile(task);
	return 0;
}