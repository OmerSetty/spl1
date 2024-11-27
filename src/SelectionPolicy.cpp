#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>

#include "Facility.h"
#include "SelectionPolicy.h"

using std::string;
using std::vector;
using namespace std;

NaiveSelection::NaiveSelection() : lastSelectedIndex(0) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex++;
    return facilitiesOptions[currentIndex];
}
// TODO? (Not in assignment)
const string NaiveSelection::toString() const {
    return to_string(lastSelectedIndex);
}
// // TODO? (Not in assignment)
// NaiveSelection* NaiveSelection::clone() {}
// // TODO
// NaiveSelection::~NaiveSelection() {}

EconomySelection::EconomySelection() : lastSelectedIndex(0) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY) {
        lastSelectedIndex++;
    }
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex++;
    return facilitiesOptions[currentIndex];
}
// TODO? (Not in assignment)
const string EconomySelection::toString() const {
    return to_string(lastSelectedIndex);
}
// // TODO? (Not in assignment)
// EconomySelection* EconomySelection::clone() {}
// // TODO
// EconomySelection::~EconomySelection() {}

SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(0) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ENVIRONMENT) {
        lastSelectedIndex++;
    }
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex++;
    return facilitiesOptions[currentIndex];
}
// TODO? (Not in assignment)
const string SustainabilitySelection::toString() const {
    return to_string(lastSelectedIndex);
}
// // TODO? (Not in assignment)
// SustainabilitySelection* SustainabilitySelection::clone() {}
// // TODO
// SustainabilitySelection::~SustainabilitySelection() {}
