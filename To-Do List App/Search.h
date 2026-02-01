#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

#include "Case.h"
#include "addCase.h"

using namespace std;
using namespace std::chrono;

// Name search
void searchByName(vector<Case>& cases) {

	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}

	string search;
	cout << "Enter task name: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, search);

	bool found = false;
	for (auto& task : cases) {
		if (task.name == search) {
			found = true;
			time_t tt = system_clock::to_time_t(task.date);
			time_t term_tt = system_clock::to_time_t(task.termDate);

			string status = task.completed ? "Completed" : "Added";
			string timeStr = ctime(&tt);

			cout << "Found:" << endl;;
			cout << "Task: " << task.name << endl;
			cout << "Description: " << task.description << endl;
			cout << "Priority: " << (task.priority ? "high" : "low") << endl;
			cout << status << ": " << timeStr << endl;
			cout << "Deadline: " << ctime(&term_tt);
			cout << "---------------------------------------------" << endl;
		}
	}
	if (found == false) {
		cout << "Task " << search << " not found" << endl;
		cout << endl;
	}
}

// Search by description
void searchByDescription(vector<Case>& cases) {

	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}

	string search;
	cout << "Enter task description: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	getline(cin, search);

	bool found = false;
	for (auto& task : cases) {
		if (task.description == search) {
			found = true;
			time_t tt = system_clock::to_time_t(task.date);
			time_t term_tt = system_clock::to_time_t(task.termDate);

			string status = task.completed ? "Completed" : "Added";
			string timeStr = ctime(&tt);

			cout << "Found:" << endl;;
			cout << "Task: " << task.name << endl;
			cout << "Description: " << task.description << endl;
			cout << "Priority: " << (task.priority ? "high" : "low") << endl;
			cout << status << ": " << timeStr << endl;
			cout << "Deadline: " << ctime(&term_tt);
			cout << "---------------------------------------------" << endl;
		}
	}
	if (found == false) cout << "Task description " << search << " not found" << endl;
	cout << endl;
}

// Search by priority
void searchByPriority(vector<Case>& cases) {

	if (cases.empty()) {
		cout << "To-Do List empty" << endl << endl;
		return;
	}

	int prioInput;
	do {
		cout << "Enter priority to search (0 = low, 1 = high): ";
		if (!(cin >> prioInput)) {
			cout << "Error: please enter a number (0 or 1).\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (prioInput != 0 && prioInput != 1) {
			cout << "Error: only 0 or 1 allowed.\n";
		}
		else {
			break;
		}
	} while (true);

	bool targetPriority = (prioInput == 1);

	bool found = false;
	for (auto& task : cases) {
		if (task.priority == targetPriority) {
			found = true;
			time_t tt = system_clock::to_time_t(task.date);
			time_t term_tt = system_clock::to_time_t(task.termDate);

			string status = task.completed ? "Completed" : "Added";
			string timeStr = ctime(&tt);

			cout << "Found:" << endl;
			cout << "Task: " << task.name << endl;
			cout << "Description: " << task.description << endl;
			cout << "Priority: " << (task.priority ? "high" : "low") << endl;
			cout << status << ": " << timeStr << endl;
			cout << "Deadline: " << ctime(&term_tt);
			cout << "---------------------------------------------" << endl;
		}
	}
	if (found == false) cout << "Task priority " << (targetPriority ? "high" : "low") << " not found" << endl;
	cout << endl;
}


// Converts time_point to tm structure (date without hours)
tm toLocalDate(system_clock::time_point tp) {
	time_t tt = system_clock::to_time_t(tp);
	tm localTime;

	localtime_s(&localTime, &tt);
	return localTime;
}


// Date input from the user
bool inputDate(int& year, int& month, int& day) {
	cout << "Enter date (YYYY MM DD): ";
	if (!(cin >> year >> month >> day)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	if (year < 1970 || year > 2100 ||
		month < 1 || month > 12 ||
		day < 1 || day > 31) {
		return false;
	}
	return true;
}


// Date Search
void searchByDate(const vector<Case>& cases) {
	if (cases.empty()) {
		cout << "\nTo-Do List empty.\n";
		return;
	}

	int year, month, day;
	do {
		cout << "\nEnter date to search (e.g. 2026 01 31):\n";
	} while (!inputDate(year, month, day));

	bool found = false;
	for (const auto& task : cases) {
		tm taskDate = toLocalDate(task.date);

		if (taskDate.tm_year + 1900 == year &&
			taskDate.tm_mon + 1 == month &&
			taskDate.tm_mday == day) {

			time_t tt = system_clock::to_time_t(task.date);
			time_t term_tt = system_clock::to_time_t(task.termDate);

			string status = task.completed ? "Completed" : "Added";
			string timeStr = ctime(&tt);

			cout << "\nFound:\n";
			cout << "Task: " << task.name << "\n";
			cout << "Description: " << task.description << "\n";
			cout << "Priority: " << (task.priority ? "high" : "low") << "\n";
			cout << status << ": " << timeStr << endl;
			cout << "Deadline: " << ctime(&term_tt);
			cout << "---------------------------------------------" << endl;
			found = true;
		}
	}

	if (!found) {
		cout << "\nNo tasks found for "
			<< year << "-" << (month < 10 ? "0" : "") << month
			<< "-" << (day < 10 ? "0" : "") << day << ".\n";
	}
}