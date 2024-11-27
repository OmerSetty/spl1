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


BalancedSelection::BalancedSelection(int currLifeQualityScore, int currEconomyScore, int currEnvironmentScore) 
    LifeQualityScore(currLifeQualityScore), EconomyScore(currEconomyScore), EnvironmentScore(currEnvironmentScore): {}

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

const string BalancedSelection:: toString() {
    cout << "Balanced selection toString. DONT FORGET TO IMPLEMENT THE DESTRUCTOR AND THE CLONE METHOD!!!"
}

public int distanceCalculator (int lifeQualityScore, economyScore, environmentScore) {
    int max(lifeQualityScore);
    if(economyScore > max) max(economyScore);
    if(environmentScore > max) max(environmentScore);
    int min(lifeQualityScore);
    if(economyScore < min) min(economyScore);
    if(environmentScore < min) min(environmentScore);
    return max-min;
}




