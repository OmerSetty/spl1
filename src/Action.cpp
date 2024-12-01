#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
enum class SettlementType;
enum class FacilityCategory;

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
}

const string SimulateStep:: SimulateStep:: toString() const {
    return "step" + numOfSteps;
}

SimulateStep* SimulateStep:: clone() const {
    return new SimulateStep(*this); // Make sure this is a good idea
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddPlan methods

AddPlan:: AddPlan(const string &settlementName, const string &selectionPolicy): BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy) {}

void AddPlan:: act(Simulation &simulation) {
    // look for the settlement with the same name in 
    if(simulation.isSettlementExists(settlementName)) {
        Settlement& planSettlement = simulation.getSettlement(settlementName);
        if(selectionPolicy == "nve")
            simulation.addPlan(planSettlement, new NaiveSelection());
        if(selectionPolicy == "bal")
            simulation.addPlan(planSettlement, new BalancedSelection(0,0,0));
        if(selectionPolicy == "eco")
            simulation.addPlan(planSettlement, new NaiveSelection());
        if(selectionPolicy == "env")
            simulation.addPlan(planSettlement, new SustainabilitySelection());
    }
    else
        error("Cannot create this plan");
}

const string AddPlan:: toString() const {
    if(getStatus() == ActionStatus:: ERROR)
        return getErrorMsg();
    else
        return "plan " + settlementName + " " + selectionPolicy;
}

AddPlan* AddPlan:: clone() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddSettlement methods

AddSettlement:: AddSettlement(const string &settlementName,SettlementType settlementType) {

}

void AddSettlement:: act(Simulation &simulation) {

}

AddSettlement* AddSettlement:: clone() const {

}
const string AddSettlement:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddFacility methods

AddFacility:: AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) {

}

void AddFacility:: act(Simulation &simulation) {

}

AddFacility* AddFacility:: clone() const {

}

const string AddFacility:: toString() const {

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

PrintActionsLog:: PrintActionsLog() {

}

void PrintActionsLog:: act(Simulation &simulation) {

}

PrintActionsLog* PrintActionsLog:: clone() const {

}

const string PrintActionsLog:: toString() const {

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