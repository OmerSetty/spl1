#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
#include "Auxiliary.h"
enum class SettlementType;
enum class FacilityCategory;
using namespace std;

// Base Action Methods
// Constructor
BaseAction:: BaseAction(): errorMsg("Error Message Initial Value"), status(ActionStatus:: ERROR) {

}

ActionStatus BaseAction:: getStatus() const {
    return status;
}

void BaseAction:: complete() {
    status = ActionStatus:: COMPLETED;
}

void BaseAction:: error(string errorMsg) {
    status = ActionStatus:: ERROR;
    (*this).errorMsg = errorMsg;
}

const string& BaseAction:: getErrorMsg() const {
    return errorMsg;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SimulateStep methods

SimulateStep:: SimulateStep(const int numOfSteps): BaseAction(), numOfSteps(numOfSteps) {}

void SimulateStep:: act(Simulation &simulation) {
    for(int i=0; i < numOfSteps; i++){
        simulation.step();
    }
    complete();
}

const string SimulateStep:: SimulateStep:: toString() const {
    return "step" + numOfSteps;
}

SimulateStep* SimulateStep:: clone() const {
    return new SimulateStep(*this); // Make sure this is a good idea
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddPlan methods

AddPlan:: AddPlan(const string &settlementName, const string &selectionPolicy):
BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy) {}

void AddPlan:: act(Simulation &simulation) {
    // look for the settlement with the same name in 
    if(!simulation.isSettlementExists(settlementName)) {
        error("Cannot create this plan");
    }
    else {
        Settlement& planSettlement = simulation.getSettlement(settlementName);
        if(selectionPolicy == "nve") {
            simulation.addPlan(planSettlement, new NaiveSelection());
            complete();
        }
        else if(selectionPolicy == "bal") {
            simulation.addPlan(planSettlement, new BalancedSelection(0,0,0));
            complete();
        }
        else if(selectionPolicy == "eco") {
            simulation.addPlan(planSettlement, new NaiveSelection());
            complete();
        }
            
        else if(selectionPolicy == "env") {
            simulation.addPlan(planSettlement, new SustainabilitySelection());
            complete();
        }    
        else
            error("did not get a leagal selectionPolicy. Check the config file");
    }
}

const string AddPlan:: toString() const {
    if(getStatus() == ActionStatus:: ERROR)
        return getErrorMsg();
    else
        return "plan " + settlementName + " " + selectionPolicy;
}

AddPlan* AddPlan:: clone() const {
    return new AddPlan(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddSettlement methods

AddSettlement:: AddSettlement(const string &settlementName,SettlementType settlementType) :
BaseAction(), settlementName(settlementName), settlementType(settlementType) {}

void AddSettlement:: act(Simulation &simulation) {
    if(simulation.isSettlementExists(settlementName))
        error("Settlement already exists");
    else {
        Settlement* newSettlement = new Settlement(settlementName, settlementType);
        simulation.addSettlement(newSettlement);
        complete();
    }
}

const string AddSettlement:: toString() const {
    if(getStatus() == ActionStatus:: ERROR)
        return getErrorMsg();
    else
        return "settlement " + settlementName + " " + Auxiliary:: settlementTypeToString(settlementType);
}

AddSettlement* AddSettlement:: clone() const {
    return new AddSettlement(*this);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddFacility methods

AddFacility:: AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
BaseAction(), facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore) {}

void AddFacility:: act(Simulation &simulation) {
    FacilityType newFacilityType = FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore); // Maybe should be a pointer?
    bool added = simulation.addFacility(newFacilityType);
    if(!added) {
        error("Facility already exists");
    }
    else
        complete();
}

const string AddFacility:: toString() const {
    if(getStatus() == ActionStatus:: ERROR)
        return getErrorMsg();
    else
        return "facility" + facilityName + to_string(Auxiliary:: facilityCategoryToInt(facilityCategory)) + to_string(price) + to_string(lifeQualityScore) +to_string(economyScore) + to_string(environmentScore);
}

AddFacility* AddFacility:: clone() const {
    return new AddFacility(*this);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PrintPlanStatus methods

PrintPlanStatus:: PrintPlanStatus(int planId) {

}

void PrintPlanStatus:: act(Simulation &simulation) {

}
PrintPlanStatus* PrintPlanStatus:: clone() const {

}

const string PrintPlanStatus:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ChangePlanPolicy methods

ChangePlanPolicy:: ChangePlanPolicy(const int planId, const string &newPolicy) {

}

void ChangePlanPolicy:: act(Simulation &simulation) {

}

ChangePlanPolicy* ChangePlanPolicy:: clone() const {

}

const string ChangePlanPolicy:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PrintActionsLog methods

PrintActionsLog:: PrintActionsLog(): BaseAction() {}

void PrintActionsLog:: act(Simulation &simulation) {
    for(BaseAction* action : simulation.getActionsLog()) {
        cout << action->toString() << endl;
    }
}

PrintActionsLog* PrintActionsLog:: clone() const {

}

const string PrintActionsLog:: toString() const {
    return "log";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Close methods

Close:: Close() {
    
}

void Close:: act(Simulation &simulation) {

}

Close* Close:: clone() const {

}

const string Close:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BackupSimulation methods

BackupSimulation:: BackupSimulation() {

}

void BackupSimulation:: act(Simulation &simulation) {

}

BackupSimulation* BackupSimulation:: clone() const {

}

const string BackupSimulation:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RestoreSimulation methods

RestoreSimulation:: RestoreSimulation() {

}

void RestoreSimulation:: act(Simulation &simulation) {

}

RestoreSimulation* RestoreSimulation:: clone() const {

}

const string RestoreSimulation:: toString() const {

}