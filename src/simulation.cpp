#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Simulation.h"
using std::string;
using std::vector;
using namespace std;


class BaseAction;
class SelectionPolicy;

Simulation:: Simulation(const string &configFilePath) {

}

void Simulation:: open() {
    isRunning = true;
}

void Simulation:: start() {
    cout << "The simulation has started" << endl;
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
    if(!isSettlementExists()){
        settlements.push_back(settlement);
        return true;
    }
    return false;
}

bool Simulation:: addFacility(FacilityType facility) {
    for(FacilityType existingFacility : facilitiesOptions) {
        if(facility.getName() != existingFacility.getName())
        facilitiesOptions.push_back(facility);
        return true;
    }
    return false;
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

Plan& Simulation:: getPlan(const int planID) {
    for(Plan p : plans) {
        if(p.getPlanID() == planID)
            return p;
    }
}
void Simulation:: step() {
    for(Plan p : plans) {
        p.step();
    }
}

void Simulation:: printSimulationStatus() {
    for(Plan p : plans) {
        cout << "PlanID: " + p.getPlanID() << endl;
        cout << "SettlementName" + p.getSettlment().getName() << endl;
        cout << "LifeQuality_Score:" + p.getlifeQualityScore() << endl;
        cout << "Economy_Score:" + p.getEconomyScore() << endl;
        cout << "Economy_Score:" + p.getEconomyScore() << endl;
        cout << "Environment_Score:" + p.getEnvironmentScore() << endl;
    }  
}

void Simulation:: close() {
    printSimulationStatus();
    isRunning = false;
}
