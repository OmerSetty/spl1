#include "Auxiliary.h"
#include "Facility.h"
#include "Settlement.h"
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
    cout << "in Auxiliary::parseArguments" << endl;    
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
    if (status == "LIFE_QUALITY") return FacilityCategory::LIFE_QUALITY;
    else if (status == "ECONOMY") return FacilityCategory::ECONOMY;
    else if (status == "ENVIRONMENT") return FacilityCategory::ENVIRONMENT;
}

SettlementType Auxiliary::getSettlementTypeStringAsSettlementType (string status) {
    if (status == "VILLAGE") return SettlementType::VILLAGE;
    else if (status == "CITY") return SettlementType::CITY;
    else if (status == "METROPOLIS") return SettlementType::METROPOLIS;
}

static string settlementTypeToString(SettlementType type) {
    if(type == SettlementType:: VILLAGE) return "0";
    if(type == SettlementType:: CITY) return "1";
    if(type == SettlementType:: METROPOLIS) return "2";
}

