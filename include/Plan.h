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
        
        // RULE OF 5-ish
        Plan(const Plan& other);
        Plan(const Plan& other, const Settlement& otherSettlementClone);
        Plan(Plan&& other);
        // Since it's logically wrong to assign an existing plan to another,
        // based on a forum response we declared those methods as 'delete'.
        Plan& operator=(const Plan& other) = delete;
        Plan& operator=(const Plan&& other) = delete;
        ~Plan();

        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        const int getPlanID() const;
        const Settlement& getSettlment() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void setStatus(PlanStatus status);
        void deleteSelectionPolicy();
        void clearFacilities();
        void clearUnderConstruction();
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        const vector<Facility*> &getUnderConstructionFacilities() const;
        const vector<FacilityType>& getFacilityOptions() const;
        void addFacility(Facility* facility);
        const string toString() const;
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