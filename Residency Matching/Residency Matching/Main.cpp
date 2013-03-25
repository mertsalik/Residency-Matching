#include "Common.h"
#include "GaleShapleyAlgorithm.h"
#include "StableMatchingProblem.h"

int main(int argc, char* argv[]){
	if (argc < 4) { 
		std::cerr << "Usage: " << argv[0] << " datafile_h1 datafile_r1 capacity(int)" << std::endl;
		return 1;
	}else if(argc == 4){
		StableMatchingProblem* problem = new StableMatchingProblem();
		problem->initializeInputVariables(argv[1],argv[2],atoi(argv[3]));
		GaleShapleyAlgorithm* algorithm = new GaleShapleyAlgorithm(problem);
		algorithm->execute();
	}else{
		std::cerr << "Too many command arguments given!";
		return 1;
	}
}