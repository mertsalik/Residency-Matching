#include "GaleShapleyAlgorithm.h"


void GaleShapleyAlgorithm::createVariables(){
	StableMatchingProblem* problem_ = this->getProblem();
	std::ifstream input( problem_->datafile_hospital_name);

	int counter = 0;
	for( std::string line; getline( input, line ); )
	{
		string word;
		istringstream iss(line, istringstream::in);
		while( iss >> word )     
		{
			Hospitals[Helpers::convertToInt(counter)].push_back(word);

			HospitalCapacities[Helpers::convertToInt(counter)] = CustomList();
		}
		counter++;
	}
	counter = 0;

	std::ifstream input2( problem_->datafile_rresidency_name );
	for( std::string line; getline( input2, line ); )
	{
		string word;
		istringstream iss(line, istringstream::in);
		while( iss >> word )     
		{
			Residencies[Helpers::convertToInt(counter)].push_back(word);
			UnPreferedHospitals[Helpers::convertToInt(counter)].push_back(word);
		}
		FreeResidencies.push_back(Helpers::convertToInt(counter));
		counter++;
	}
}

void GaleShapleyAlgorithm::execute(){
	this->clock_start = clock();
	this->createVariables();
	this->createOutputFileName();

	StableMatchingProblem* problem_ = this->getProblem();

	while(FreeResidencies.size() != 0){
		//cout << FreeResidencies.size() << "	residencies remain." << endl;
		string residency = FreeResidencies.front();
		//cout << "Checking for " << residency << " residency" << endl;
		bool matched = false;
		while(UnPreferedHospitals[residency].size() != 0 && !matched){
			string preferableHospital = UnPreferedHospitals[residency].front();
			Helpers::removeFromCustomList(UnPreferedHospitals[residency],preferableHospital);
			if((HospitalCapacities[preferableHospital].size() < problem_->capacity )){
				// add residency
				matched = true;
				HospitalCapacities[preferableHospital].push_back(residency);
				Helpers::removeFromCustomList(FreeResidencies,residency);
			}else{
				// already have another and capacity is full
				for(CustomList::iterator it = HospitalCapacities[preferableHospital].begin(); it != HospitalCapacities[preferableHospital].end(); ++it){
					string versusResidency = it->data();
					if(this->compareResidencyOverHospital(preferableHospital,residency,versusResidency)){
						// change operation
						Helpers::removeFromCustomList(HospitalCapacities[preferableHospital],versusResidency);
						HospitalCapacities[preferableHospital].push_back(residency);
						Helpers::removeFromCustomList(FreeResidencies,residency);
						FreeResidencies.push_back(versusResidency);
						matched = true;
						// win
						break;
					}else{
						// lose
					}
				}
			}
		}
	}
	clock_end = clock();

	ofstream outputFile;
	outputFile.open(this->outputFileName);

	//outputFile << "Quota " << problem_->capacity << endl;
	for(int i = 0;i<Hospitals.size();i++){
		for(CustomList::iterator it = HospitalCapacities[Helpers::convertToInt(i)].begin(); it != HospitalCapacities[Helpers::convertToInt(i)].end(); ++it){
			StableMatching[Helpers::convertToInt(i)].push_back(it->data());	
			outputFile << i << " " << it->data() << endl;
		}
	}
	
	cout << "Time :" << this->getCalculationTime() << endl << "----" << endl;

}

bool GaleShapleyAlgorithm::compareResidencyOverHospital(string Hospital, string Me, string OtherResidency){
	int myIndex = Helpers::getCustomListValueIndex(Hospitals[Hospital],Me);
	int otherIndex = Helpers::getCustomListValueIndex(Hospitals[Hospital],OtherResidency);
	if(myIndex < otherIndex){
		return true;
	}else{
		return false;
	}
}


GaleShapleyAlgorithm::~GaleShapleyAlgorithm(void)
{
}
