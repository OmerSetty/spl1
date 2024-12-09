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
        static string facilityStatusAsString(const FacilityStatus& status);
        static FacilityCategory stringToFacilityCategory(const string& status);
        static string facilityCategoryToString(const FacilityCategory& status);
        static SettlementType stringToSettlementType(const string& status);
        static string getPlanStatusAsString(const PlanStatus& status);
        static string settlementTypeToString(const SettlementType& type);
        static int facilityCategoryToInt(const FacilityCategory& category);

};
