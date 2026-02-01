#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

#include "Case.h"
#include "addCase.h"
#include "Search.h"
#include "Save.h"

using namespace std;
using namespace std::chrono;

// Search Menu
void searchMenu(vector<Case>& cases) {
	int choice;
	do {
		cout << "---------------SEARCH MENU-----------------" << endl;
		cout << "1. Search by name" << endl;
		cout << "2. Search by priprity" << endl;
		cout << "3. Search by decription" << endl;
		cout << "4. Search by date" << endl;
		cout << "0. Back" << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << endl;
			searchByName(cases);
			break;
		case 2:
			cout << endl;
			searchByPriority(cases);
			break;
		case 3:
			cout << endl;
			searchByDescription(cases);
			break;
		case 4:
			cout << endl;
			searchByDate(cases);
			break;
		case 0:
			cout << endl;
			break;
		default:
			cout << endl;
			cout << "Unknown operation" << endl;
			break;
		}
	} while (choice != 0);
}

// Main Menu
void menu(vector<Case>& cases) {
	int choice;
	cout << "------------------To-Do List------------------" << endl << endl;
	do {
		cout << "  1. Display a to-do list" << endl;
		cout << "  2. Task search" << endl;
		cout << "  3. Add a case" << endl;
		cout << "  4. Edit a case" << endl;
		cout << "  5. Mark whether the task is completed" << endl;
		cout << "  6. Delete a case" << endl;
		cout << "  7. Delete all cases" << endl;
		cout << "  0. To close" << endl;
		cout << "Your choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << endl;
			printCase(cases);
			break;
		case 2:
			cout << endl;
			searchMenu(cases);
			break;
		case 3:
			cout << endl;
			addCase(cases);
			break;
		case 4:
			cout << endl;
			editCase(cases);
			break;
		case 5:
			cout << endl;
			taskComplete(cases);
			break;
		case 6:
			cout << endl;
			deleteCase(cases);
			break;
		case 7:
			cout << endl;
			clearFile();
			cases.clear();
			cout << "All tasks has been deleted" << endl;
			cout << endl;
			break;
		case 0:
			cout << endl;
			cout << "You're out" << endl;
			break;
		default:
			cout << endl;
			cout << "Unknown operation" << endl;
			break;
		}
	} while (choice != 0);
}

