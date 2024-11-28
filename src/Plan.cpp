#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>
#include <climits>

#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Plan.h"

using std::string;
using std::vector;
using namespace std;

Plan::Plan(const int currPlanId, const Settlement &currSettlement, SelectionPolicy *currSelectionPolicy, const vector<FacilityType> &currFacilityOptions)
    : plan_id(currPlanId), settlement(currSettlement), selectionPolicy(currSelectionPolicy), facilityOptions(currFacilityOptions),
      life_quality_score(0), economy_score(0), environment_score(0), status(PlanStatus::AVALIABLE) {}

const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}
const int Plan::getEconomyScore() const {
    return economy_score;
}
const int Plan::getEnvironmentScore() const {
    return environment_score;
}

int getCapacityByType (SettlementType type) {
    if (type == SettlementType::VILLAGE) return 1;
    if (type == SettlementType::CITY) return 2;
    if (type == SettlementType::METROPOLIS) return 3;
}

bool hasLeftCapacity() {
    return (getCapacityByType(settlement.getType()) - underConstruction.size()) > 0;
}