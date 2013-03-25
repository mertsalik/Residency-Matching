#pragma once
#include "problem.h"
class StableMatchingProblem :
	public Problem
{
public:
	StableMatchingProblem(void);
	~StableMatchingProblem(void);
	bool initializeInputVariables(string DataFileName1, string DataFileName2, int Capacity);

	// data files
	string datafile_hospital_name;
	string datafile_rresidency_name;
	int capacity;
};

