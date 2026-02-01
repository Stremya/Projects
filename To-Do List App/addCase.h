#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>

#include "Case.h"

using namespace std;
using namespace std::chrono;


// The comparison function
bool compareByDeadlineAndPriority(const Case& a, const Case& b) {
	if (a.termDate != b.termDate) {
		return a.termDate < b.termDate;
	}
	return a.priority > b.priority;
}

// Choosing a date
system_clock::time_point getTerm() {
	auto now = system_clock::now();

	int choice;
	cout << "Choose term" << endl;
	cout << "  1. Today" << endl;
	cout << "  2. On week" << endl;
	cout << "  3. On month" << endl;
	cout << "Your choice: ";

	do {
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter 1, 2 or 3: ";
		}
		else if (choice < 1 || choice > 3) {
			cout << "Invalid choice. Enter 1, 2 or 3: ";
		}
		else {
			break;
		}
	} while (true);

	switch (choice) {
	case 1: return now + 24h;
	case 2: return now + 7 * 24h;
	case 3: return now + 30 * 24h;
	}
	return now;
}


// Adds a new task
void addCase(vector<Case>& cases) {
	Case newCases;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Enter the task name: ";
	getline(cin, newCases.name);

	cout << "Enter a description: ";
	getline(cin, newCases.description);

	int prioInput;
	do {
		cout << "Enter priority (0 = low, 1 = high): ";
		if (!(cin >> prioInput)) {
			cout << "Error: please enter a number (0 or 1)." << endl;
			cin.clear(); 
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (prioInput != 0 && prioInput != 1) {
			cout << "Error: only 0 or 1 allowed." << endl;
		}
		else {
			break;
		}
	} while (true);

	newCases.priority = (prioInput == 1);
	
	newCases.termDate = getTerm();

	cases.push_back(newCases);

	cout << endl;
	cout << "Task: " << newCases.name << " added" << endl;
}

// Outputs the task
void printCase(vector<Case>& cases) {
	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}
	
	sort(cases.begin(), cases.end(), compareByDeadlineAndPriority);

	for (size_t i = 0; i < cases.size(); i++) {
		time_t tt = system_clock::to_time_t(cases[i].date);
		time_t term_tt = system_clock::to_time_t(cases[i].termDate);

		
		string timeStr = ctime(&tt);
		timeStr.pop_back(); // removing \n from ctime

		cout << (i+1) << ".Task: " << cases[i].name << endl;
		cout << "Priority - " << (cases[i].priority ? "high" : "low") << endl;
		cout << "Description: " << cases[i].description << endl;
		if (cases[i].completed) {
			cout << "Completed" << endl;;
		}
		else {
			cout << "Added: " << timeStr << endl;;
		}
		cout << "Deadline: " << ctime(&term_tt);
		cout << "===========================================" << endl;
	}
}

// Edits an issue
void editCase(vector<Case>& cases) {
	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}

	int index;
	cout << "Enter a number task for edit (1 - " << cases.size() << "):";
	cin >> index;
	index--;

	if (index < 0 || index > cases.size()) {
		cout << "Invalid index" << endl << endl;;
		return;
	}

	cout << "Editing the issue: " << cases[index].name << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "Enter new name: ";
	getline(cin, cases[index].name);

	cout << "Enter new description: ";
	getline(cin, cases[index].description);

	int prioInput;
	do {
		cout << "Enter new priority (0 = low, 1 = high): ";
		if (!(cin >> prioInput)) {
			cout << "Error: please enter a number (0 or 1)." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (prioInput != 0 && prioInput != 1) {
			cout << "Error: only 0 or 1 allowed." << endl;
		}
		else {
			break;
		}
	} while (true);

	cases[index].priority = (prioInput == 1);

	cout << endl;
	cout << "The task has been updated!" << endl;
	cout << endl;
}

// Deletes a task
void deleteCase(vector<Case>& cases) {
	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}

	size_t index;
	cout << "Enter a number task for delete (1 - " << cases.size() << "):";
	cin >> index;
	
	if (index < 0 || index > cases.size()) {
		cout << "Invalid index" << endl << endl;;
		return;
	}
	index--;

	cout << "The task " << cases[index].name << " has been deleted." << endl;
	cout << endl;
	cases.erase(cases.begin() + index);
}

// Marks whether the task is completed
void taskComplete(vector<Case>& cases) {
	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}

	cout << "\nEnter task number to mark as completed (1 - " << cases.size() << "): ";
	int index;
	cin >> index;
	index--;

	if (index < 0 || static_cast<size_t>(index) >= cases.size()) {
		cout << "Invalid number!\n";
		return;
	}

	cases[index].completed = true;
	cout << "Task " << cases[index].name << " marked as completed!" << endl;
	cout << endl;
}