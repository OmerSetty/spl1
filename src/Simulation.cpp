#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Simulation.h"
#include "Facility.h"
#include "Settlement.h"
#include "Plan.h"
#include "Auxiliary.h"
#include "Action.h"
using std::string;
using std::vector;
using namespace std;


class BaseAction;
class SelectionPolicy;
class Auxiliary;
class Settlement;

Simulation::Simulation(const string &configFilePath) : isRunning(false) {
    cout << "in simulation constructor" << endl;
    std::ifstream file(configFilePath);
    string currentLine;
    while (std::getline(file, currentLine)) {
        cout << currentLine << endl;
        vector<string> parsedArgs = Auxiliary::parseArguments(currentLine);
        addConfigObject(parsedArgs);
    }
}

// should we initialize a vector of non-pointers like that? (e.g: plans, facilitiesOptons)
Simulation::Simulation(const Simulation& other) : isRunning(other.isRunning), planCounter(other.planCounter), plans(other.plans), facilitiesOptions(other.facilitiesOptions) {
    for (BaseAction* action : other.actionsLog) {
        actionsLog.push_back(action);
    }
    for (Settlement* settlement : other.settlements) {
        settlements.push_back(settlement);
    }
}

Simulation::Simulation(Simulation&& other) : isRunning(other.isRunning), planCounter(other.planCounter), actionsLog(other.actionsLog),
            plans(other.plans), settlements(other.settlements), facilitiesOptions(other.facilitiesOptions) {
    other.actionsLog.clear();
    other.settlements.clear();
}

Simulation& Simulation:: operator=(const Simulation &other) {
    if (this != &other) {
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        for (BaseAction* action: actionsLog) {
            delete action;
        }
        for (BaseAction* action: other.actionsLog) {
            actionsLog.push_back((*action).clone());
        }
        plans = other.plans;
        for (Settlement* settlement: settlements) {
            delete settlement;
        }
        for (Settlement* settlement: other.settlements) {

            settlements.push_back(settlement);
            settlements.push_back(new Settlement((*settlement).getName(), (*settlement).getType()));
        }
        facilitiesOptions = other.facilitiesOptions;
    }
    return *this;
}

Simulation& Simulation:: operator=(Simulation &&other) {
    if (this != &other) {
        isRunning = other.isRunning;
        planCounter = other.planCounter;

        for (BaseAction* action: actionsLog) {
            delete action;
        }
        actionsLog = other.actionsLog;
        // clear or nullptr?
        other.actionsLog.clear();

        plans = other.plans;

        for (Settlement* settlement: settlements) {
            delete settlement;
        }
        settlements = other.settlements;
        // clear or nullptr?
        other.settlements.clear();

        facilitiesOptions = other.facilitiesOptions;
    }
    return *this;
}

void Simulation::addConfigObject(vector<string> parsedArgs) {
    // cout << "in addCONfigObject" << endl;
    const string typeOfObject = parsedArgs[0];
    // NOT SURE - who should delete the values on the heap?
    if (typeOfObject == "settlement") {
        cout << "in settlement" << endl;
        addSettlement(new Settlement(parsedArgs[1], Auxiliary::getSettlementTypeStringAsSettlementType(parsedArgs[2])));
    } 
    else if (typeOfObject == "facility") {
        cout << "in facility" << endl;
        addFacility(FacilityType(parsedArgs[1], Auxiliary::getFacilityCategoryStringAsFacilityCategory(parsedArgs[2]), stoi(parsedArgs[3]), 
                                                                    stoi(parsedArgs[4]), stoi(parsedArgs[5]), stoi(parsedArgs[6])));
    }
    else if (typeOfObject == "plan") {
        cout << "in plan" << endl;
        const string selectionPolicyType = parsedArgs[2];
        if (selectionPolicyType == "nve") {
            addPlan(getSettlement(parsedArgs[1]), new NaiveSelection());
        }
        if (selectionPolicyType == "bal") {
            addPlan(getSettlement(parsedArgs[1]), new BalancedSelection(0, 0, 0));
        }
        if (selectionPolicyType == "eco") {
            addPlan(getSettlement(parsedArgs[1]), new EconomySelection());
        }
        if (selectionPolicyType == "env") {
            addPlan(getSettlement(parsedArgs[1]), new SustainabilitySelection());
        }
    }
}

// Rule of 5
// Distructor
Simulation:: ~Simulation() {
    for(BaseAction* action : actionsLog) {
        delete action;
    }
    actionsLog.clear();
    for(Settlement* settlement : settlements) {
        delete settlement;
    }
    settlements.clear();
}

void Simulation:: open() {
    while(isRunning) {
        string input;
        cin >> input;
        vector<string> inputArguments = Auxiliary:: parseArguments(input);
        BaseAction* action;
        vector<string>& ia = inputArguments;
        bool isPrintActionsLog = false;
        if(ia[0] == "step") {
            action = new SimulateStep(stoi(ia[1]));
        }
        else if(ia[0] == "plan") {
            action = new AddPlan(ia[1], ia[2]);
        }
        else if(ia[0] == "settlement") {
            action = new AddSettlement(ia[1], Auxiliary:: getSettlementTypeStringAsSettlementType(ia[2]));
        }
        else if(ia[0] == "facility") {
            action = new AddFacility(ia[1], Auxiliary:: getFacilityCategoryStringAsFacilityCategory(ia[2]), stoi(ia[3]), stoi(ia[4]), stoi(ia[5]), stoi(ia[6]));
        }
        else if(ia[0] == " planStatus") {
            action = new PrintPlanStatus(stoi(ia[1]));
        }
        else if(ia[0] == " changePolicy") {
            action = new ChangePlanPolicy(stoi(ia[1]), ia[2]);
        }
        else if(ia[0] == "log") {
            action = new PrintActionsLog();
            isPrintActionsLog = true;
        }
        else if(ia[0] == "close") {
            action = new Close();
        }
        else if(ia[0] == "backup") {
            action = new BackupSimulation();
        }
        else if(ia[0] == "restore") {
            action = new RestoreSimulation();
        }
        action->act(*this);
        if(!isPrintActionsLog)
            actionsLog.push_back(action);
    }
}

void Simulation::setIsRunning(bool isRunningStatus) {
    isRunning = isRunningStatus;
}

void Simulation:: start() {
    cout << "The simulation has started" << endl;
    isRunning = true;
    open();
}

void Simulation:: addPlan(const Settlement &settlement, SelectionPolicy* selectionPolicy) {
    plans.push_back(Plan(planCounter, settlement, selectionPolicy, facilitiesOptions)); // We must save the plans on the stack??
    planCounter++;
}
void Simulation:: addAction(BaseAction *action) {
    actionsLog.push_back(action);   // Check whether there is an action that shouldnt be added (maybe restore).
}
bool Simulation:: addSettlement(Settlement* settlement) {
    if(!isSettlementExists(settlement->getName())){
        settlements.push_back(settlement);
        return true;
    }
    return false;
}

bool Simulation:: addFacility(FacilityType facility) {
    for(FacilityType existingFacility : facilitiesOptions) {
        if(facility.getName() == existingFacility.getName())
            return false;
    }
    facilitiesOptions.push_back(facility);
    return true;
}
bool Simulation:: isSettlementExists(const string &settlementName) {
    for(Settlement* s : settlements) {
        if(s->getName() == settlementName)
            return true;
    }
    return false;
}
Settlement& Simulation:: getSettlement(const string &settlementName) {
    for(Settlement* s : settlements) {
        if(s->getName() == settlementName)
            return *s;
    }
    cout << "Simulation.getSettlement(const string &settlementName) was called but there is no settlement with the given name!" << endl;
}

bool Simulation:: isPlanExists(const int planID) {
    for(Plan p : plans) {
        if(p.getPlanID() == planID)
            return true;
    }
    return false;
}

const vector<BaseAction*>& Simulation:: getActionsLog() const {
    return actionsLog;
}

Plan& Simulation:: getPlan(const int planID) {
    for(Plan p : plans) {
        if(p.getPlanID() == planID)
            return p;
    }
}

const vector<Plan>& Simulation:: getPlans() const {
    return plans;
}

void Simulation:: step() {
    for(Plan p : plans) {
        p.step();
    }
}

void Simulation:: printSimulationStatus() {
    for(Plan p : plans) {
        cout << "PlanID: " + to_string(p.getPlanID()) << endl;
        cout << "SettlementName: " + p.getSettlment().getName() << endl;
        cout << "LifeQuality_Score:" + to_string(p.getlifeQualityScore()) << endl;
        cout << "Economy_Score:" + to_string(p.getEconomyScore()) << endl;
        cout << "Environment_Score:" + to_string(p.getEnvironmentScore()) << endl;
    }  
}

void Simulation:: close() {
    printSimulationStatus();
    isRunning = false;
}
