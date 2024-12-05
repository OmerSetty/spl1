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

// Increase Index - Increases the index if possible,
// or resets it to 0 if we gor to the end of the vector
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
    return "Naive Selction";
}

NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}


int SelectionPolicy:: distanceCalculator (int lifeQualityScore, int economyScore, int environmentScore) {
    int max = lifeQualityScore;
    if(economyScore > max) max = economyScore;
    if(environmentScore > max) max = environmentScore;
    int min = lifeQualityScore;
    if(economyScore < min) min = economyScore;
    if(environmentScore < min) min = environmentScore;
    return max-min;
}

////////////////////////////////////////////////////////////////////////////////////////////////

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

BalancedSelection* BalancedSelection:: clone() const {
    return new BalancedSelection(*this);
}

const string BalancedSelection:: toString() const {
    return "Balanced Selection";
}

// EconomySelection implementations
EconomySelection::EconomySelection() : lastSelectedIndex(0) {}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    while (facilitiesOptions[lastSelectedIndex].getCategory() != FacilityCategory::ECONOMY) {
        lastSelectedIndex = increaseIndex(lastSelectedIndex, facilitiesOptions.size());
    }
    int currentIndex = lastSelectedIndex; 
    increaseIndex(currentIndex, facilitiesOptions.size());
    return facilitiesOptions[currentIndex];
}

const string EconomySelection::toString() const {
    return "Economy Selection";
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
    increaseIndex(currentIndex, facilitiesOptions.size());
    return facilitiesOptions[currentIndex];
}

const string SustainabilitySelection::toString() const {
    return "Sustainability Selection";
}

SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}
