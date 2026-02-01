#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Case.h"

using namespace std;
using namespace std::chrono;

// Saving to a file
void saveFile(const vector<Case>& cases, const string& filename = "tasks.txt") {
	ofstream file(filename);
	
	if (!file.is_open()) {
		cout << "Error: couldn't open the file for writing" << endl;
		return;
	}
	
	for (const auto& task : cases) {
		time_t tt = system_clock::to_time_t(task.date);
		time_t term_tt = system_clock::to_time_t(task.termDate);
		file << task.name << "|"
			<< task.description << "|"
			<< (task.priority ? "high" : "low") << "|"
			<< (task.completed ? "done" : "pending") << "|"
			<< tt << "|"
			<< term_tt << "\n";
	}
	file.close();
}

// Downloading from a file
vector<Case> loadFile(const string& filename = "tasks.txt") {
	vector<Case> tasks;
	ifstream file(filename);

	if (!file.is_open()) {
		return tasks;
	}

	string line;
	while (getline(file, line)) {
		if (line.empty()) continue;

		size_t p1 = line.find('|');
		size_t p2 = line.find('|', p1 + 1);
		size_t p3 = line.find('|', p2 + 1);
		size_t p4 = line.find('|', p3 + 1);
		size_t p5 = line.find('|', p4 + 1);

		if (p1 == string::npos || p2 == string::npos || 
			p3 == string::npos || p4 == string::npos || p5 == string::npos) {
			continue; 
		}

		string name = line.substr(0, p1);
		string desc = line.substr(p1 + 1, p2 - p1 - 1);
		string prioStr = line.substr(p2 + 1, p3 - p2 - 1);
		bool prio = (prioStr == "high");
		string statusStr = line.substr(p3 + 1, p4 - p3 - 1);
		string timeStr = line.substr(p4 + 1, p5 - p4 - 1);
		string termTimeStr = line.substr(p5 + 1);

		if (timeStr.empty() || !all_of(timeStr.begin(), timeStr.end(), ::isdigit)) {
			cout << "Error: Incorrect time in the row: " << line << endl;
			continue;
		}

		try {
			time_t tt = stoll(timeStr); 
			time_t term_tt = stoll(termTimeStr);

			system_clock::time_point date = system_clock::from_time_t(tt);
			system_clock::time_point termDate = system_clock::from_time_t(term_tt);

			Case task;
			task.name = name;
			task.description = desc;
			task.priority = (prioStr == "high");
			task.completed = (statusStr == "done");
			task.date = date;
			task.termDate = termDate;
			tasks.push_back(task);
		}
		catch (...) {
			cout << "[ERROR] Time conversion error: " << timeStr << endl;
			continue;
		}
	}

	return tasks;
}

// Clears the file
void clearFile(const string& filename = "tasks.txt") {
	ofstream file(filename);

	file.close();
}