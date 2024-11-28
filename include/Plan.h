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
    // Given methods
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;

    // // Our new methods
    //     // Copy Counstructor
    //     Plan(Plan& other);
    //     // Destructor
    //     ~Plan();
    //     // Assignment Opertaor
    //     Plan& Opertaor=(const Plan& other); // maybe should be void?
    //     // Move Constructor
        const 
        const SelectionPolicy& getSelectionPolicy() const;
    private:
        int plan_id;
        Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};