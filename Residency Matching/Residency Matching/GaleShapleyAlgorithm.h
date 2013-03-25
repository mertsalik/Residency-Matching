#include "Helpers.h"
#include "StableMatchingProblem.h"
#pragma once
#include "algorithm.h"
class GaleShapleyAlgorithm :
	public Algorithm
{
private:
	string outputFileName;
	void createOutputFileName(){
		StableMatchingProblem* problem_ = this->getProblem();
		this->outputFileName = "output1_S";
		char a ;
		int charCounter = 0;
		for (std::string::reverse_iterator i = problem_->datafile_hospital_name.rbegin(); i != problem_->datafile_hospital_name.rend(); ++i){
			a = *i;
			charCounter++;
			if(charCounter == 5){
				break;
			}
		}
		this->outputFileName +=a;
		this->outputFileName +=".txt";
	}
	void createVariables();
public:
	GaleShapleyAlgorithm(StableMatchingProblem* problem): Algorithm(problem){}
	~GaleShapleyAlgorithm(void);
	void execute();
	StableMatchingProblem* getProblem(){return (StableMatchingProblem*)this->problem;}

	// solution variables
	Map Hospitals,HospitalCapacities,Residencies,UnPreferedHospitals,StableMatching;
	CustomList FreeResidencies;

	bool compareResidencyOverHospital(string Hospital, string Me, string OtherResidency);
};

