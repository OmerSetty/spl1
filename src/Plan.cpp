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

Plan::Plan(const int currPlanId, const Settlement& currSettlement, SelectionPolicy* currSelectionPolicy, const vector<FacilityType> &currFacilityOptions)
    : plan_id(currPlanId), settlement(currSettlement), selectionPolicy(currSelectionPolicy), facilityOptions(currFacilityOptions),
      life_quality_score(0), economy_score(0), environment_score(0), status(PlanStatus::AVALIABLE) {}

// Make sure theres no memory leak and that the method works
void Plan:: setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    if(getSelectionPolicy().toString() !=  (*selectionPolicy).toString())
        delete (*this).selectionPolicy;
        (*this).selectionPolicy = selectionPolicy;
        selectionPolicy = nullptr;
}

void Plan:: setStatus(PlanStatus newStatus) {
    status = newStatus;
}

// Removes the facility from the underConstruction vector
// Adds it to the existing facilities vector
void Plan:: addFacility(Facility* facility) {
    vector<Facility*>& u = underConstruction;
    u.erase(find(u.begin(), u.end(), facility));
    facilities.push_back(facility); // dont forget to deeply delete everything after the end of the use.
    setStatus(PlanStatus:: AVALIABLE);
}

void Plan:: step() {
    vector<Facility*>& u = underConstruction;
    for(int i = 0; i < u.size(); i++) {
        (*u[i]).step();
    }
    while(status == PlanStatus::AVALIABLE) {
        const FacilityType& nextFacilityType = (*selectionPolicy).selectFacility(facilityOptions);
        // stack or heap?
        Facility* nextFacility = new Facility(nextFacilityType, settlement.getName());
        u.push_back(nextFacility);
        (*nextFacility).step();

        if(!hasLeftCapacity())
            setStatus(PlanStatus::BUSY);
    }
    for(int i = 0; i < u.size(); i++) {
        if((*u[i]).getStatus() == FacilityStatus::OPERATIONAL) {
            cout << "facility " + (*u[i]).getName() + " finished" << endl;
            addFacility(u[i]);
        }
    }
    for(int i = 0; i < u.size(); i++) {
        cout << (*u[i]).toString() << endl;
    }
}

string getStatusAsString (PlanStatus status) {
    if (status == PlanStatus::AVALIABLE) return "AVALIABLE";
    if (status == PlanStatus::BUSY) return "BUSY";
}

void Plan:: printStatus() {
    cout << getStatusAsString(status) << endl;
}

const vector<Facility*>& Plan:: getFacilities() const {
    return facilities;
}

const SelectionPolicy& Plan:: getSelectionPolicy() const {
    return *selectionPolicy;
}

const int Plan:: getPlanID() const {
    return plan_id;
}

const Settlement& Plan:: getSettlment() const {
    return settlement;
}

const string Plan:: toString() const {
    return "Plan.toString() returns the plan's id for now: " + to_string(plan_id);
}

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

bool Plan::hasLeftCapacity() {
    return (getCapacityByType(settlement.getType()) - underConstruction.size()) > 0;
}
