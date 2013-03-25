#include "StableMatchingProblem.h"


StableMatchingProblem::StableMatchingProblem(void)
{
}


StableMatchingProblem::~StableMatchingProblem(void)
{
}

bool StableMatchingProblem::initializeInputVariables(string DataFileName1, string DataFileName2, int Capacity){
	this->datafile_hospital_name = DataFileName1;
	this->datafile_rresidency_name = DataFileName2;
	this->capacity = Capacity;
	return true;
}