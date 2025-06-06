#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
#include "Plan.h"
#include "Simulation.h"
#include "Auxiliary.h"
enum class SettlementType;
enum class FacilityCategory;
using namespace std;
extern Simulation* backup;

// Base Action

BaseAction:: BaseAction(): errorMsg("Error Message Initial Value"), status(ActionStatus:: ERROR) {}

ActionStatus BaseAction:: getStatus() const {
    return status;
}

void BaseAction:: complete() {
    status = ActionStatus:: COMPLETED;
}

void BaseAction:: error(string errorMsg) {
    status = ActionStatus:: ERROR;
    (*this).errorMsg = errorMsg;
    cout << "Error: " + errorMsg << endl;
}

const string& BaseAction:: getErrorMsg() const {
    return errorMsg;
}

const string BaseAction:: actionStatusToString() const {
    if (getStatus() == ActionStatus:: COMPLETED) {
        return "COMPLETED";
    }
    return "ERROR";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SimulateStep

SimulateStep:: SimulateStep(const int numOfSteps): BaseAction(), numOfSteps(numOfSteps) {}

void SimulateStep:: act(Simulation &simulation) {
    for(int i=0; i < numOfSteps; i++){
        simulation.step();
    }
    complete();
}

const string SimulateStep:: SimulateStep:: toString() const {
    return "step " + to_string(numOfSteps) + " " + actionStatusToString();
}

SimulateStep* SimulateStep:: clone() const {
    return new SimulateStep(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddPlan

AddPlan:: AddPlan(const string &settlementName, const string &selectionPolicy):
BaseAction(), settlementName(settlementName), selectionPolicy(selectionPolicy) {}

void AddPlan:: act(Simulation &simulation) {
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
            error("Cannot create this plan");
    }
}

const string AddPlan:: toString() const {
        return "plan " + settlementName + " " + selectionPolicy + " " +actionStatusToString();
}

AddPlan* AddPlan:: clone() const {
    return new AddPlan(*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddSettlement

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
        return "settlement " + settlementName + " " + Auxiliary:: settlementTypeToString(settlementType) + " " + actionStatusToString();
}

AddSettlement* AddSettlement:: clone() const {
    return new AddSettlement(*this);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddFacility

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
    return "facility " + facilityName + " " + to_string(Auxiliary:: facilityCategoryToInt(facilityCategory)) + " " + to_string(price) + " " + to_string(lifeQualityScore) + " " +to_string(economyScore) + " " + to_string(environmentScore) + " " + actionStatusToString();
}

AddFacility* AddFacility:: clone() const {
    return new AddFacility(*this);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PrintPlanStatus

PrintPlanStatus:: PrintPlanStatus(int planId) : BaseAction(), planId(planId) {}

void PrintPlanStatus:: act(Simulation &simulation) {
    if (!simulation.isPlanExists(planId)) {
        error("Plan doesn’t exist");
        return;
    }
    Plan& plan = simulation.getPlan(planId);
    string planStatus = 
        "PlanID: " + to_string(planId) +
        "\nSettlementName: " + plan.getSettlment().getName() +
        "\nPlanStatus: " + Auxiliary::getPlanStatusAsString(plan.getStatus()) +
        "\nSelectionPolicy: " + plan.getSelectionPolicy().toString()
        + "\nLifeQualityScore: " + to_string(plan.getlifeQualityScore()) +
        "\nEconomyScore: " + to_string(plan.getEconomyScore()) +
        "\nEnvrionmentScore: " + to_string(plan.getEnvironmentScore());
    for (const Facility* facility: plan.getFacilities()) {
        planStatus.append("\nFacilityName: " + facility->getName() + "\nFacilityStatus: OPERATIONAL");
    }
    for (const Facility* facility: plan.getUnderConstructionFacilities()) {
        planStatus.append("\nFacilityName: " + facility->getName() + "\nFacilityStatus: UNDER CONSTRUCTION");
    }
    cout << planStatus << endl;
    complete();
}
PrintPlanStatus* PrintPlanStatus:: clone() const {
    return new PrintPlanStatus(*this);
}

const string PrintPlanStatus:: toString() const {
    return "planStatus " + to_string(planId) + " " + actionStatusToString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ChangePlanPolicy

ChangePlanPolicy:: ChangePlanPolicy(const int planId, const string &newPolicy) : BaseAction(), planId(planId), newPolicy(newPolicy) {}

void ChangePlanPolicy:: act(Simulation &simulation) {
    if (!simulation.isPlanExists(planId)) {
        error("Cannot change selection policy");
        return;
    }
    Plan& plan = simulation.getPlan(planId);
    string prevPolicy = plan.getSelectionPolicy().toString();
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
        complete();
    }
}

ChangePlanPolicy* ChangePlanPolicy:: clone() const {
    return new ChangePlanPolicy(*this);
}

const string ChangePlanPolicy:: toString() const {
    return "changePolicy " + to_string(planId) + " newPolicy: " + newPolicy + " " + actionStatusToString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PrintActionsLog

PrintActionsLog:: PrintActionsLog(): BaseAction() {}

void PrintActionsLog:: act(Simulation &simulation) {
    for(BaseAction* actionToString : simulation.getActionsLog()) {
        cout << actionToString->toString() << endl;
    }
}

PrintActionsLog* PrintActionsLog:: clone() const {
    return new PrintActionsLog(*this);
}

const string PrintActionsLog:: toString() const {
    return "log " + actionStatusToString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Close

Close:: Close() : BaseAction() {}

void Close:: act(Simulation &simulation) {
    simulation.close();
    complete();
}

Close* Close:: clone() const {
    return new Close(*this);
}

const string Close:: toString() const {
    return "close" + actionStatusToString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BackupSimulation

BackupSimulation:: BackupSimulation() : BaseAction() {}

void BackupSimulation:: act(Simulation &simulation) {
    if (backup == nullptr) {
        backup = new Simulation(simulation);
    }
    else {
        *backup = simulation;
    }
    complete();
}

BackupSimulation* BackupSimulation:: clone() const {
    return new BackupSimulation(*this);
}

const string BackupSimulation:: toString() const {
    return "backup " + actionStatusToString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RestoreSimulation

RestoreSimulation:: RestoreSimulation(): BaseAction() {}

void RestoreSimulation:: act(Simulation &simulation) {
    if(backup == nullptr)
        error("No backup available");
    else {
        simulation = *backup;
        complete();
    }
}

RestoreSimulation* RestoreSimulation:: clone() const {
    return new RestoreSimulation(*this);
}

const string RestoreSimulation:: toString() const {
    return "restore " + actionStatusToString();
}