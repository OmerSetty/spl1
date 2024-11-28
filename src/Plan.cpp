#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>
#include <climits>

#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"

using std::string;
using std::vector;
using namespace std;

Plan::Plan() : {}
// Make sure theres no memory leak and that the method works
void Plan:: setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    if(getSelectionPolicy().toString() !=  (*selectionPolicy).toString())
        delete (*this).selectionPolicy;
        (*this).selectionPolicy = selectionPolicy;
        selectionPolicy = nullptr;
}

void Plan:: step() {
    vector<Facility*>& u = underConstruction;
    for(int i = 0; i < u.size(); i++) {
        (*u[i]).step();
    }
    while(status == AVALIABLE) {
        FacilityType& nextFacility = selectFacility(facilitiesOptions);
        u.push_element(nextFacility);
        nextFacilityacility.step();

        if(!hasLeftCapacity())
            setStatus(BUSY);
    }
    for(int i = 0; i < u.size(); i++) {
        if((*u[i]).getStatus() == OPERATIONAL) {
            (*u[i]).addFacility();
        }
    }
}

void Plan:: printStatus() {
    cout << status << endl;
}

const vector<Facility*>& Plan:: getFacilities() const {
    return facilities;
}

const SelectionPolicy& Plan:: getSelectionPolicy() {
    return selectionPolicy;
}
// Removes the facility from the underConstruction vector
// Adds it to the existing facilities vector
void Plan:: addFacility(Facility* facility) {
    vector<Facility*>& u = underConstruction;
    u.erase(find(u.begin(), u.end, facility));
    facilities.push_element(facility); // dont forget to deeply delete everything after the end of the use.
    setStatus(PlanStatus:: AVALIABLE);
}


const string Plan:: toString() const {
    return "Plan.toString() returns the plan's id for now: " + ""plan_id;
}

