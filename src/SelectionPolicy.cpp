#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>
#include <climits>

#include "Facility.h"
#include "SelectionPolicy.h"

using std::string;
using std::vector;
using namespace std;

// NaiveSelection implementations 
NaiveSelection::NaiveSelection() : lastSelectedIndex(0) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex++;
    return facilitiesOptions[currentIndex];
}

const string NaiveSelection:: toString() const {
    return "Naive Selction";
}

// NaiveSelection* NaiveSelection::clone() {
//     return this;
// }
// // TODO
// NaiveSelection::~NaiveSelection() {}

int distanceCalculator (int lifeQualityScore, int economyScore, int environmentScore) {
    int max = lifeQualityScore;
    if(economyScore > max) max = economyScore;
    if(environmentScore > max) max = environmentScore;
    int min = lifeQualityScore;
    if(economyScore < min) min = economyScore;
    if(environmentScore < min) min = environmentScore;
    return max-min;
}


// BalancedSelection implementations
BalancedSelection::BalancedSelection(int currLifeQualityScore, int currEconomyScore, int currEnvironmentScore) :
    LifeQualityScore(currLifeQualityScore), EconomyScore(currEconomyScore), EnvironmentScore(currEnvironmentScore) {}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int min = INT_MAX;
    int index = 0;
    for (int i=0; i<facilitiesOptions.size(); i++) {
        int improvedLQScore = LifeQualityScore + facilitiesOptions[i].getLifeQualityScore();
        int improvedEcoScore = EconomyScore + facilitiesOptions[i].getEconomyScore();
        int improvedEnvScore = EnvironmentScore + facilitiesOptions[i].getEnvironmentScore();
        int distance = distanceCalculator(improvedLQScore, improvedEcoScore, improvedEnvScore);
        if(distance < min){
            min = distance;
            index = i;
        }
    }
    return facilitiesOptions[index];
}

const string BalancedSelection:: toString() const {
    return "Balanced Selection";
}

// EconomySelection implementations
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
    return "Economy Selection";
}

// virtual EconomySelection* EconomySelection::clone() {
//     return this;
// }
// // TODO
// virtual EconomySelection::~EconomySelection() {}



// SustainabilitySelection implementations
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
    return "Sustainability Selection";
}

// SustainabilitySelection* SustainabilitySelection::clone() {
//     return this;
// }
// // TODO
// virtual SustainabilitySelection::~SustainabilitySelection() {}