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

string Auxiliary::facilityStatusAsString (const FacilityStatus& status) {
    if (status == FacilityStatus::UNDER_CONSTRUCTIONS) return "UNDER_CONSTRUCTIONS";
    else if (status == FacilityStatus::OPERATIONAL) return "OPERATIONAL";
    cout << "INVALID facility status was given!" << endl;
    return "";
}

FacilityCategory Auxiliary::stringToFacilityCategory (const string& status) {
    if (status == "0") {
        return FacilityCategory::LIFE_QUALITY;
    }
    else if (status == "1") {
        return FacilityCategory::ECONOMY;
    }
    else if (status == "2") {
        return FacilityCategory::ENVIRONMENT;
    }
    // This section of code will never happen, assuming the config_file and the user input data is valid.
    // So we return an arbitrary FacilityCategory in order to return a value anyway
    cout << "INVALID facility category status was given!" << endl;
    return FacilityCategory::LIFE_QUALITY;
}

SettlementType Auxiliary::stringToSettlementType (const string& status) {
    if (status == "0") return SettlementType::VILLAGE;
    else if (status == "1") return SettlementType::CITY;
    else if (status == "2") return SettlementType::METROPOLIS;
    // This section of code will never happen, assuming the config_file and the user input data is valid.
    // So we return an arbitrary SettlementType in order to return a value anyway
    cout << "INVALID settlement status was given!" << endl;
    return SettlementType::VILLAGE;
}

string Auxiliary::getPlanStatusAsString (const PlanStatus& status) {
    if (status == PlanStatus::BUSY) return "BUSY";
    else if (status == PlanStatus::AVALIABLE) return "AVALIABLE";
    // This section of code will never happen, assuming the config_file and the user input data is valid.
    // So we return an arbitrary string in order to return a value anyway
    cout << "INVALID plan status was given!" << endl;
    return "";
}

string Auxiliary:: settlementTypeToString(const SettlementType& type) {
    if(type == SettlementType:: VILLAGE) return "0";
    if(type == SettlementType:: CITY) return "1";
    if(type == SettlementType:: METROPOLIS) return "2";
    // This section of code will never happen, assuming the config_file and the user input data is valid.
    // So we return an arbitrary string in order to return a value anyway
    cout << "INVALID settlement type was given!" << endl;
    return "";
}

int Auxiliary:: facilityCategoryToInt(const FacilityCategory& category) {
    if(category == FacilityCategory:: LIFE_QUALITY)
        return 0;
    else if(category == FacilityCategory:: ECONOMY)
        return 1;
    else if(category == FacilityCategory:: ENVIRONMENT)
        return 2;
    else {
        cout << "INVALID facility category was given!" << endl;
        return -1;
    }
}
