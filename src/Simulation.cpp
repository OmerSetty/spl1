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
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
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
        // cout << currentLine << endl;
        vector<string> parsedArgs = Auxiliary::parseArguments(currentLine);
        addConfigObject(parsedArgs);
    }
}

void Simulation::addConfigObject(vector<string> parsedArgs) {
    const string typeOfObject = parsedArgs[0];
    // NOT SURE - who should delete the values on the heap?
    if (typeOfObject == "Settlement") {
        addSettlement(new Settlement(parsedArgs[1], Auxiliary::getSettlementTypeStringAsSettlementType(parsedArgs[2])));
    } 
    else if (typeOfObject == "Facility") {
        addFacility(FacilityType(parsedArgs[1], Auxiliary::getFacilityCategoryStringAsFacilityCategory(parsedArgs[2]), stoi(parsedArgs[3]), 
                                                                    stoi(parsedArgs[4]), stoi(parsedArgs[5]), stoi(parsedArgs[6])));
    }
    else if (typeOfObject == "Plan") {
        const string selectionPilicyType = parsedArgs[2];
        if (selectionPilicyType == "nve") {
            addPlan(getSettlement(parsedArgs[1]), new NaiveSelection());
        }
        if (selectionPilicyType == "bal") {
            addPlan(getSettlement(parsedArgs[1]), new BalancedSelection(0, 0, 0));
        }
        if (selectionPilicyType == "eco") {
            addPlan(getSettlement(parsedArgs[1]), new EconomySelection());
        }
        if (selectionPilicyType == "env") {
            addPlan(getSettlement(parsedArgs[1]), new SustainabilitySelection());
        }
    }
}

