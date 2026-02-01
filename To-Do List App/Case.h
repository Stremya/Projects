#pragma once

#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Case {
	string name;
	string description;
	bool priority = false;
	bool completed = false;
	system_clock::time_point date = system_clock::now();
	system_clock::time_point termDate;
};