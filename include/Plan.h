#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        Plan(const Plan& other);
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        const int getPlanID() const;
        const Settlement& getSettlment() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void setStatus(PlanStatus status);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        const vector<Facility*> &getUnderConstructionFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;

    // // Our new methods
    //     // Copy Counstructor
    //     Plan(Plan& other);
    //     // Destructor
    //     ~Plan();
    //     // Assignment Opertaor
        Plan& Opertaor=(const Plan& other) = delete; // maybe should be void?
    //     // Move Constructor
        const SelectionPolicy& getSelectionPolicy() const;
        bool hasLeftCapacity();
        const PlanStatus getStatus() const;
    private:
        int plan_id;
        const Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};