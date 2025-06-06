#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>

#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
#include "Plan.h"
#include "Auxiliary.h"

using std::string;
using std::vector;
using namespace std;

// Constructor
Plan::Plan(const int currPlanId, const Settlement& currSettlement, SelectionPolicy* currSelectionPolicy, const vector<FacilityType> &currFacilityOptions)
      : plan_id(currPlanId), settlement(currSettlement), selectionPolicy(currSelectionPolicy), status(PlanStatus::AVALIABLE),
        facilities(), underConstruction(), facilityOptions(currFacilityOptions),
        life_quality_score(0), economy_score(0), environment_score(0) {
        }
// RULE OF 5-ish
//Copy Constructor
Plan::Plan(const Plan& other) : plan_id(other.plan_id), settlement(other.settlement), selectionPolicy(other.selectionPolicy->clone()), status(other.getStatus()),
        facilities(), underConstruction(), facilityOptions(other.facilityOptions), 
        life_quality_score(other.getlifeQualityScore()), economy_score(other.getEconomyScore()), environment_score(other.getEnvironmentScore()) {
            for (size_t i = 0; i < other.facilities.size(); i++) {
                facilities.push_back(new Facility(*other.facilities[i]));
            }
            for (size_t i = 0; i < other.underConstruction.size(); i++) {
                underConstruction.push_back(new Facility(*other.underConstruction[i]));
            }
        }

// Another Copy Constructor - CLONES the other plan's settlements
Plan::Plan(const Plan& other, const Settlement& otherSettlementClone) :
Plan(other.plan_id, otherSettlementClone, other.selectionPolicy->clone(), other.facilityOptions) {
    status = other.status;
    life_quality_score = other.life_quality_score;
    economy_score = other.economy_score;
    environment_score = other.environment_score;
    for (size_t i = 0; i < other.facilities.size(); i++) {
        facilities.push_back(new Facility(*other.facilities[i]));
    }
    for (size_t i = 0; i < other.underConstruction.size(); i++) {
        underConstruction.push_back(new Facility(*other.underConstruction[i]));
    }
}

// Move Constructor
Plan:: Plan(Plan&& other) : plan_id(other.plan_id), settlement(other.settlement), selectionPolicy(other.selectionPolicy), status(other.getStatus()),
        facilities(other.facilities), underConstruction(other.underConstruction), facilityOptions(other.facilityOptions), 
        life_quality_score(other.getlifeQualityScore()), economy_score(other.getEconomyScore()), environment_score(other.getEnvironmentScore()) {
    other.selectionPolicy = nullptr;
    other.facilities.clear();
    other.underConstruction.clear();
}

// Destructor
Plan:: ~Plan() {
    if (selectionPolicy != nullptr)
        delete selectionPolicy;
    for(Facility* f : facilities) {
        delete f;
    }
    facilities.clear();
    for(Facility* uc : underConstruction) {
        delete uc;
    }
    underConstruction.clear();
}


void Plan:: setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    if (getSelectionPolicy().toString() !=  (*selectionPolicy).toString()) {
        delete (*this).selectionPolicy;
        (*this).selectionPolicy = selectionPolicy;
    }
}

void Plan:: setStatus(PlanStatus newStatus) {
    status = newStatus;
}

void Plan:: deleteSelectionPolicy() {
    delete selectionPolicy;
}

void Plan:: clearFacilities() {
    facilities.clear();
}

void Plan:: clearUnderConstruction() {
    underConstruction.clear();
}

// Removes the facility from the underConstruction vector
// Adds it to the existing facilities vector
// Changes planStatus to AVAILABLE
void Plan:: addFacility(Facility* facility) {
    vector<Facility*>& u = underConstruction;
    u.erase(find(u.begin(), u.end(), facility));
    facilities.push_back(facility);
    setStatus(PlanStatus:: AVALIABLE);
    life_quality_score += facility->getLifeQualityScore();
    economy_score += facility->getEconomyScore();
    environment_score += facility->getEnvironmentScore();
}

void Plan:: step() {
    vector<Facility*>& u = underConstruction;
    // promoting the construction of every facility under construction
    for (Facility* uc : u) {
        (*uc).step();
    }
    // Adding new facilitues to construct if possible
    while(status == PlanStatus::AVALIABLE) {
        const FacilityType& nextFacilityType = (*selectionPolicy).selectFacility(facilityOptions);
        Facility* nextFacility = new Facility(nextFacilityType, settlement.getName());
        u.push_back(nextFacility);
        (*nextFacility).step();

        if(!hasLeftCapacity())
            setStatus(PlanStatus::BUSY);
    }
    // Moving all the constructed facilities to the facilities list
    for(size_t i = 0; i < u.size(); i++) {
        if((*u[i]).getStatus() == FacilityStatus::OPERATIONAL) {
            addFacility(u[i]);
        }
    }
}

void Plan:: printStatus() {
    cout << Auxiliary::getPlanStatusAsString(status) << endl;
}

const PlanStatus Plan:: getStatus() const {
    return status;
}

const vector<Facility*>& Plan:: getFacilities() const {
    return facilities;
}

const vector<Facility*>& Plan:: getUnderConstructionFacilities() const {
    return underConstruction;
}

const vector<FacilityType>& Plan:: getFacilityOptions() const {
    return facilityOptions;
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
    return "PlanID: " + to_string(plan_id)
            + "\nSettlementName: " + settlement.getName()
            + "\nLifeQuality_Score: " + to_string(getlifeQualityScore())
            + "\nEconomy_Score: " + to_string(getEconomyScore())
            + "\nEnvironment_Score: " + to_string(getEnvironmentScore());
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
    if (type == SettlementType::VILLAGE) {
        return 1;
    }
    if (type == SettlementType::CITY) {
        return 2;
    }
    if (type == SettlementType::METROPOLIS) {
        return 3;
    }
    return 0;
}

bool Plan::hasLeftCapacity() {
    return (getCapacityByType(settlement.getType()) - underConstruction.size()) > 0;
}
