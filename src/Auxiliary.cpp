#include "Auxiliary.h"
#include "Facility.h"
#include "Settlement.h"
#include "Plan.h"
using namespace std;
using std::string;
using std::vector;

/*
This is a 'static' method that receives a string(line) and returns a vector of the string's arguments.

For example:
parseArguments("settlement KfarSPL 0") will return vector with ["settlement", "KfarSPL", "0"]

To execute this method, use Auxiliary::parseArguments(line)
*/
vector<string> Auxiliary::parseArguments(const string& line) {  
    vector<string> arguments;
    istringstream stream(line);
    string argument;

    while (stream >> argument) {
        arguments.push_back(argument);
    }

    return arguments;
}

string Auxiliary::facilityStatusAsString (FacilityStatus status) {
    if (status == FacilityStatus::UNDER_CONSTRUCTIONS) return "UNDER_CONSTRUCTIONS";
    else if (status == FacilityStatus::OPERATIONAL) return "OPERATIONAL";
}

FacilityCategory Auxiliary::getFacilityCategoryStringAsFacilityCategory (string status) {
    if (status == "0") {
        return FacilityCategory::LIFE_QUALITY;
    }
    else if (status == "1") {
        return FacilityCategory::ECONOMY;
    }
    else if (status == "2") {
        return FacilityCategory::ENVIRONMENT;
    }
}
string Auxiliary::facilityCategoryToString (FacilityCategory status) {
    if (status == FacilityCategory::LIFE_QUALITY){
        cout << "in if: FacilityCategory::LIFE_QUALITY";
        return "LIFE_QUALITY";
    } 
    if (status == FacilityCategory::ECONOMY){
        cout << "in if: FacilityCategory::ECONOMY";
        return "ECONOMY";
    }   
    if (status == FacilityCategory::ENVIRONMENT){
        cout << "in if: FacilityCategory::ENVIRONMENT";
        return "ENVIRONMENT";
    } 
        
}

SettlementType Auxiliary::getSettlementTypeStringAsSettlementType (string status) {
    if (status == "0") return SettlementType::VILLAGE;
    else if (status == "1") return SettlementType::CITY;
    else if (status == "2") return SettlementType::METROPOLIS;
}

string Auxiliary::getPlanStatusAsString (PlanStatus status) {
    if (status == PlanStatus::BUSY) return "BUSY";
    else if (status == PlanStatus::AVALIABLE) return "AVALIABLE";
}

string Auxiliary:: settlementTypeToString(SettlementType type) {
    if(type == SettlementType:: VILLAGE) return "0";
    if(type == SettlementType:: CITY) return "1";
    if(type == SettlementType:: METROPOLIS) return "2";
}

int Auxiliary:: facilityCategoryToInt(FacilityCategory category) {
    if(category == FacilityCategory:: LIFE_QUALITY)
        return 0;
    else if(category == FacilityCategory:: ECONOMY)
        return 1;
    else if(category == FacilityCategory:: ENVIRONMENT)
        return 2;
    else {
        cout << "No legal facilityCategory detected. output is 300. Check config file";
        return 300;
    }
}
