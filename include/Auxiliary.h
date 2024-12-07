#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "Facility.h"
#include "Settlement.h"
#include "Plan.h"
using std::string;
using std::vector;

class Auxiliary{
    public:
        static vector<string> parseArguments(const string& line);
        static string facilityStatusAsString(FacilityStatus status);
        static FacilityCategory stringToFacilityCategory(string status);
        static string facilityCategoryToString(FacilityCategory status);
        static SettlementType stringToSettlementType(string status);
        static string getPlanStatusAsString(PlanStatus status);
        static string settlementTypeToString(SettlementType type);
        static int facilityCategoryToInt(FacilityCategory category);
        
};
