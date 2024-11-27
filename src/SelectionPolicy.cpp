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
    // FacilityType& facility = facilitiesOptions[lastSelectedIndex];
    // lastSelectedIndex++;
    // return facility;
    
    int currentIndex = lastSelectedIndex; 
    lastSelectedIndex++;
    // MAKE SURE: Do we need to return a reference? and why?
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

// BalancedSelection::BalancedSelection(int newLifeQualityScore, int newEconomyScore, int newEnvironmentScore) 
//     LifeQualityScore(newLifeQualityScore), EconomyScore(newEconomyScore), EnvironmentScore(newEnvironmentScore): {}

// const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
//     for (int i=0; i<facilitiesOptions.size(); i++) {
//         FacilityType& facility = facilitiesOptions[i];
//         // int lifeQualityScore = facility.getLifeQualityScore();
//         // int environmentScore = facility.getEnvironmentScore();
//         // int economyScore = facility.getEconomyScore();
//         // if ((lifeQualityScore - environmentScore == 1 || lifeQualityScore - environmentScore == -1) &&
//         //     (environmentScore - economyScore == 1 || environmentScore - economyScore == -1) &&
//         //     (lifeQualityScore - economyScore == 1 || lifeQualityScore - economyScore == -1)) {
//         //     return facility;
//         // }
//         cout << facility.getLifeQualityScore() << endl; 
//     }
// }

// // TODO? (Not in assignment)
// const string NaiveSelection::toString() {}
// // TODO? (Not in assignment)
// NaiveSelection* NaiveSelection::clone() {}
// // TODO
// NaiveSelection::~NaiveSelection() {}

