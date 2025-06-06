#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
#include "Action.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
        // RULE OF 5
        Simulation(const Simulation& other);
        Simulation(Simulation&& other);
        Simulation& operator=(const Simulation& other);
        Simulation& operator=(Simulation&& other);
        ~Simulation();
        
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement* settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        Settlement &getSettlement(const string &settlementName);
        bool isPlanExists(const int planID);
        Plan &getPlan(const int planID);
        const vector<Plan>& getPlans() const;
        const vector<Settlement*>& getSettlements() const;
        const vector<FacilityType>& getFacilityOptions() const;
        const bool getIsRunning() const;
        const int getPlanCounter() const;
        void step();
        void addConfigObject(vector<string>& parsedArgs);
        void close();
        void open();
        void printSimulationStatus();
        void setIsRunning(bool isRunningStatus);
        const vector<BaseAction*>& getActionsLog() const;

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;

};