#include "Common.h"
#pragma once
class Helpers
{
public:
	Helpers(void){};
	~Helpers(void){};
	string static convertToInt(int number)
	{
		stringstream ss;
		ss << number;
		return ss.str();
	}
	bool static hasCustomListValue(CustomList v,string Value){
		if (std::find(v.begin(), v.end(), Value) != v.end())
		{
			return true;
		}else{
			return false;
		}
	}

	void static removeFromCustomList(CustomList& v, string Value){
		v.erase(std::remove(v.begin(), v.end(),Value), v.end());
	}

	int static getCustomListValueIndex(CustomList v, string Value){
		int counter = 0;
		for(CustomList::iterator it = v.begin(); it != v.end(); ++it){
			if(it->data() == Value){
				return counter; 
			}
			counter++;
		}
		return -1;
	}


};
