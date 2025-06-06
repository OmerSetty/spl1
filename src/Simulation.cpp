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

// Constructor
Simulation::Simulation(const string &configFilePath) : isRunning(false), planCounter(0), actionsLog(), plans(),
        settlements(), facilitiesOptions() {
    std::ifstream file(configFilePath);
    string currentLine;
    while (std::getline(file, currentLine)) {
        vector<string> parsedArgs = Auxiliary::parseArguments(currentLine);
        addConfigObject(parsedArgs);
    }
}

// Adds the parsed arguments to the new simulation.
void Simulation::addConfigObject(vector<string>& parsedArgs) {
    const string typeOfObject = parsedArgs[0];
    if (typeOfObject == "settlement") {
        addSettlement(new Settlement(parsedArgs[1], Auxiliary::stringToSettlementType(parsedArgs[2])));
    } 
    else if (typeOfObject == "facility") {
        addFacility(FacilityType(parsedArgs[1], Auxiliary::stringToFacilityCategory(parsedArgs[2]), stoi(parsedArgs[3]), 
                                                                    stoi(parsedArgs[4]), stoi(parsedArgs[5]), stoi(parsedArgs[6])));
    }
    else if (typeOfObject == "plan") {
        const string selectionPolicyType = parsedArgs[2];
        if (isSettlementExists(parsedArgs[1])) {
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
}

// RULE OF 5
// Copy Constructor
Simulation::Simulation(const Simulation& other) 
: isRunning(other.getIsRunning()), planCounter(other.getPlanCounter()), actionsLog(), plans(),
settlements(), facilitiesOptions(other.getFacilityOptions()) {
    for (BaseAction* action : other.getActionsLog()) {
        actionsLog.push_back((*action).clone());
    }
    for (Settlement* settlement : other.getSettlements()) {
        settlements.push_back(new Settlement(*settlement));
    }
    for (size_t i = 0; i < other.plans.size(); i++) {
        Plan p1 = Plan(other.plans[i], getSettlement(other.plans[i].getSettlment().getName()));
        plans.push_back(p1);
    }
}

// Move Copy Constructor
Simulation::Simulation(Simulation&& other) : isRunning(other.getIsRunning()), planCounter(other.getPlanCounter()), actionsLog(other.getActionsLog()),
            plans(other.getPlans()), settlements(other.getSettlements()), facilitiesOptions(other.getFacilityOptions()) {
    other.actionsLog.clear();
    other.settlements.clear();
    other.plans.clear();
}

// Assignment Operator
Simulation& Simulation:: operator=(const Simulation &other) {
    if (this != &other) {
        isRunning = other.getIsRunning();
        planCounter = other.getPlanCounter();
        for (BaseAction* action: actionsLog) {
            delete action;
        }
        actionsLog.clear();
        for (BaseAction* action: other.getActionsLog()) {
            actionsLog.push_back((*action).clone());
        }
        // make sure
        for (Settlement* settlement: settlements) {
            delete settlement;
        }
        settlements.clear();
        for (Settlement* settlement: other.getSettlements()) {
            settlements.push_back(new Settlement(*settlement));
        }
        plans.clear();
        
        for (size_t i = 0; i < other.plans.size(); i++) {
            Plan p1 = Plan(other.plans[i], getSettlement(other.plans[i].getSettlment().getName()));
            plans.push_back(p1);
        }
        
        facilitiesOptions.clear();
        for (size_t i = 0; i < other.getFacilityOptions().size(); i++) {
            facilitiesOptions.push_back(other.getFacilityOptions()[i]);
        }
    }
    return *this;
}

Simulation& Simulation:: operator=(Simulation &&other) {
    if (this != &other) {
        isRunning = other.getIsRunning();
        planCounter = other.getPlanCounter();

        for (BaseAction* action: actionsLog) {
            delete action;
        }
        actionsLog = other.getActionsLog();
        other.actionsLog.clear();

        for (size_t i = 0; i < plans.size(); i++) {
            Plan& p = plans[i];
            delete &p;
        }
        plans.clear();
        for (size_t i = 0; i < other.getPlans().size(); i++) {
            plans.push_back(other.getPlans()[i]);
        }
        other.plans.clear();

        for (Settlement* settlement: settlements) {
            delete settlement;
        }
        
        settlements = other.getSettlements();
        other.settlements.clear();

        facilitiesOptions.clear();
        for (size_t i = 0; i < other.facilitiesOptions.size(); i++) {
            facilitiesOptions.push_back(other.getFacilityOptions()[i]);
        }
    }
    return *this;
}

// Distructor
Simulation:: ~Simulation() {
    if (actionsLog.size() > size_t(0)) {
        for (BaseAction* action : actionsLog) {
            delete action;
        }
    }
    for (Settlement* settlement : settlements) {
        delete settlement;
    }
}

void Simulation:: open() {
    while(isRunning) {
        string input;
        // cin >> input;
        // cin.ignore();
        getline(cin, input);
        vector<string> inputArguments = Auxiliary:: parseArguments(input);
        BaseAction* action;
        vector<string>& ia = inputArguments;
        bool isPrintActionsLog = false, isLegalAction = true;
        if(ia[0] == "step") {
            action = new SimulateStep(stoi(ia[1]));
        }
        else if(ia[0] == "plan") {
            action = new AddPlan(ia[1], ia[2]);
        }
        else if(ia[0] == "settlement") {
            action = new AddSettlement(ia[1], Auxiliary:: stringToSettlementType(ia[2]));
        }
        else if(ia[0] == "facility") {
            action = new AddFacility(ia[1], Auxiliary:: stringToFacilityCategory(ia[2]), stoi(ia[3]), stoi(ia[4]), stoi(ia[5]), stoi(ia[6]));
        }
        else if(ia[0] == "planStatus") {
            action = new PrintPlanStatus(stoi(ia[1]));
        }
        else if(ia[0] == "changePolicy") {
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
        else {
            isLegalAction = false;
        }
        if (isLegalAction) {
            action->act(*this);
            if(!isPrintActionsLog)
                actionsLog.push_back(action);
            else
                delete action;
        }
        else
            cout << "INVALID ACTION!" << endl;
    }
}

void Simulation::setIsRunning(bool isRunningStatus) {
    isRunning = isRunningStatus;
}

void Simulation:: start() {
    cout << "The simulation has started" << endl;
    isRunning = true;
    Simulation:: open();
}

void Simulation:: addPlan(const Settlement &settlement, SelectionPolicy* selectionPolicy) {
    Plan p1 = Plan(planCounter, settlement, selectionPolicy, facilitiesOptions);
    plans.push_back(p1);
    planCounter++;
}
void Simulation:: addAction(BaseAction *action) {
    actionsLog.push_back(action);
}
bool Simulation:: addSettlement(Settlement* settlement) {
    if(!isSettlementExists(settlement->getName())) {
        settlements.push_back(settlement);
        return true;
    }
    delete settlement;
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
    // This section of code will never happen, because getSettlement() is called only after isSettlementExists() returns true.
    // So we return an arbitrary Settlement instance in order to return a value anyway
    Settlement* s = new Settlement(settlementName, SettlementType::METROPOLIS);
    return *s;
}

bool Simulation:: isPlanExists(const int planID) {
    for (size_t i = 0; i < plans.size(); i++) {
        if(plans[i].getPlanID() == planID)
            return true;
    }
    return false;
}

const vector<BaseAction*>& Simulation:: getActionsLog() const {
    return actionsLog;
}

Plan& Simulation:: getPlan(const int planID) {
    for (size_t i = 0; i < plans.size(); i++) {
        if(plans[i].getPlanID() == planID) {
            return plans[i];
        }
    }
    // This section of code will never happen, because getPlan() is called only after isPlanExists() returns true.
    // So we return an arbitrary Plan instance in order to return a value anyway
    Settlement* s = new Settlement("", SettlementType::METROPOLIS);
    Plan* p = new Plan(-1, *s, new NaiveSelection(), facilitiesOptions);
    return *p;
}

const vector<Plan>& Simulation:: getPlans() const {
    return plans;
}

const vector<Settlement*>& Simulation::getSettlements() const {
    return settlements;
}

const vector<FacilityType>& Simulation::getFacilityOptions() const {
    return facilitiesOptions;
}

const bool Simulation::getIsRunning() const {
    return isRunning;
}

const int Simulation::getPlanCounter() const {
    return planCounter;
}

void Simulation:: step() {
    for (size_t i = 0; i < plans.size(); i++) {
        plans[i].step();
    }
}

void Simulation:: printSimulationStatus() {
    for (size_t i = 0; i < plans.size(); i++) {
        cout << plans[i].toString() << endl;
    }
}

void Simulation:: close() {
    printSimulationStatus();
    isRunning = false;
}
