#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <climits>

#include "Facility.h"
#include "SelectionPolicy.h"
#include "Auxiliary.h"

using std::string;
using std::vector;
using namespace std;

// Increase Index - Increases the index if possible,
// or resets it to 0 if we got to the end of the vector
int SelectionPolicy:: increaseIndex(int currIndex, int facilitiesOptionsSize) {
    currIndex += 1;
    if(currIndex >= facilitiesOptionsSize)
        currIndex = 0;
    return currIndex;
}

////////////////////////////////////////////////////////////////////////////////////////////////

// NaiveSelection implementations
NaiveSelection::NaiveSelection() : lastSelectedIndex(0) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex = increaseIndex(currentIndex, facilitiesOptions.size());
    return facilitiesOptions[currentIndex];
}

const string NaiveSelection:: toString() const {
    return "nve";
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}



////////////////////////////////////////////////////////////////////////////////////////////////

// BalancedSelection implementations
BalancedSelection::BalancedSelection(int currLifeQualityScore, int currEconomyScore, int currEnvironmentScore) :
    LifeQualityScore(currLifeQualityScore), EconomyScore(currEconomyScore), EnvironmentScore(currEnvironmentScore) {}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    int min = INT_MAX;
    int index = 0;
    // Finds the facilityType which will keep the difference between settlement's scores minimal
    for (size_t i=0; i<facilitiesOptions.size(); i++) {
        int improvedLQScore = LifeQualityScore + facilitiesOptions[i].getLifeQualityScore();
        int improvedEcoScore = EconomyScore + facilitiesOptions[i].getEconomyScore();
        int improvedEnvScore = EnvironmentScore + facilitiesOptions[i].getEnvironmentScore();
        int distance = distanceCalculator(improvedLQScore, improvedEcoScore, improvedEnvScore);
        if(distance < min) {
            min = distance;
            index = i;
        }
    }
    LifeQualityScore = facilitiesOptions[index].getLifeQualityScore();
    EconomyScore = facilitiesOptions[index].getEconomyScore();
    EnvironmentScore = facilitiesOptions[index].getEnvironmentScore();
    return facilitiesOptions[index];
}

// Calculate the maxumum difference between scores of the settlement
int SelectionPolicy:: distanceCalculator (int lifeQualityScore, int economyScore, int environmentScore) {
    int max = lifeQualityScore;
    if(economyScore > max) max = economyScore;
    if(environmentScore > max) max = environmentScore;
    int min = lifeQualityScore;
    if(economyScore < min) min = economyScore;
    if(environmentScore < min) min = environmentScore;
    return max-min;
}

BalancedSelection* BalancedSelection:: clone() const {
    return new BalancedSelection(*this);
}

const string BalancedSelection:: toString() const {
    return "bal";
}


////////////////////////////////////////////////////////////////////////////////////////////////

// EconomySelection implementations
EconomySelection::EconomySelection() : lastSelectedIndex(0) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY) {
        lastSelectedIndex = increaseIndex(lastSelectedIndex, facilitiesOptions.size());
    }
    int currentIndex = lastSelectedIndex;
    lastSelectedIndex = increaseIndex(currentIndex, facilitiesOptions.size());
    return facilitiesOptions[currentIndex];
}

const string EconomySelection::toString() const {
    return "eco";
}

EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this);
}


////////////////////////////////////////////////////////////////////////////////////////////////

// SustainabilitySelection implementations
SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(0) {}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ENVIRONMENT) {
        lastSelectedIndex = increaseIndex(lastSelectedIndex, facilitiesOptions.size());
    }
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex = increaseIndex(currentIndex, facilitiesOptions.size());
    return facilitiesOptions[currentIndex];
}

const string SustainabilitySelection::toString() const {
    return "env";
}

SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}
