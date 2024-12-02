#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Facility.h"
#include "Settlement.h"
using std::string;
using std::vector;

class Auxiliary{
    public:
        static vector<string> parseArguments(const string& line);
        static string facilityStatusAsString(FacilityStatus status);
        static FacilityCategory getFacilityCategoryStringAsFacilityCategory(string status);
        static SettlementType getSettlementTypeStringAsSettlementType(string status);
        static string settlementTypeToString(SettlementType type);
        static int facilityCategoryToInt(FacilityCategory category);
        
};
