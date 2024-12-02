#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
#include "Auxiliary.h"
enum class SettlementType;
enum class FacilityCategory;
using namespace std;
extern Simulation* backup;

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

PrintPlanStatus:: PrintPlanStatus(int planId) : planId(planId) {}

void PrintPlanStatus:: act(Simulation &simulation) {
    if (!simulation.isPlanExists(planId)) {
        error("Cannot change selection policy");
        return;
    }
    Plan& plan = simulation.getPlan(planId);
    string planStatus = "PlanID: " + to_string(planId) + "\nSettlementName: " + plan.getSettlment().getName() +
        "\nPlanStatus: " + Auxiliary::getPlanStatusAsString(plan.getStatus()) + "\nSelectionPolicy: " + plan.getSelectionPolicy().toString()
        + "\nLifeQualityScore: " + to_string(plan.getlifeQualityScore()) + "\nEconomyScore: " + to_string(plan.getEconomyScore()) + "EnvrionmentScore: "
        + to_string(plan.getEnvironmentScore());
    for (const Facility* facility: plan.getFacilities()) {
        planStatus += "\nFacilityName: " + facility->getName() + "\nFacilityStatus: OPERATIONALS";
    }
    for (const Facility* facility: plan.getUnderConstructionFacilities()) {
        planStatus += "\nFacilityName: " + facility->getName() + "\nFacilityStatus: UNDER CONSTRUCTION";
    }
    complete();
}
PrintPlanStatus* PrintPlanStatus:: clone() const {
    return new PrintPlanStatus(*this);
}
const string PrintPlanStatus:: toString() const {
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ChangePlanPolicy methods

ChangePlanPolicy:: ChangePlanPolicy(const int planId, const string &newPolicy) : BaseAction(), planId(planId), newPolicy(newPolicy), prevPolicy(""){}

void ChangePlanPolicy:: act(Simulation &simulation) {
    if (!simulation.isPlanExists(planId)) {
        error("Cannot change selection policy");
        return;
    }
    Plan& plan = simulation.getPlan(planId);
    if (prevPolicy == newPolicy) {
        error("Cannot change selection policy");
        return;
    }
    if (newPolicy == "nve") {
        plan.setSelectionPolicy(new NaiveSelection());
        complete();
    }
    else if (newPolicy == "bal") {
        plan.setSelectionPolicy(new BalancedSelection(0, 0, 0));
        complete();
    }
    else if (newPolicy == "eco") {
        plan.setSelectionPolicy(new EconomySelection());
        complete();
    }
    else if (newPolicy == "env") {
        plan.setSelectionPolicy(new SustainabilitySelection());
    }
    if (newPolicy == "nve" || newPolicy == "bal" || newPolicy == "eco" || newPolicy == "env") {
        cout << "PlanID: " + to_string(planId) + "\npreviousPolicy: " + prevPolicy + "\nnewPolicy: " + newPolicy << endl;
        prevPolicy = newPolicy;
        complete();
    }
}

ChangePlanPolicy* ChangePlanPolicy:: clone() const {
    return new ChangePlanPolicy(*this);
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
    return new PrintActionsLog(*this);
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

BackupSimulation:: BackupSimulation() {}

void BackupSimulation:: act(Simulation &simulation) {
    *backup = simulation;
    complete();
}

BackupSimulation* BackupSimulation:: clone() const {
    return new BackupSimulation(*this);
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