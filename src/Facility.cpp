#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>
#include <Facility.h>

using std::string;
using std::vector;
using namespace std;

// FacilityType
// Constructors
// Parameterized
FacilityType:: FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
    name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score){}


// Methods
const string& FacilityType:: getName() const {
    return name;
}

int FacilityType:: getCost() const {
    return price;
}

int FacilityType:: getLifeQualityScore() const {
    return lifeQuality_score;
}

int FacilityType:: getEnvironmentScore() const {
    return environment_score;
}

int FacilityType:: getEconomyScore() const {
    return economy_score;
}

FacilityCategory FacilityType:: getCategory() const {
    return category;
}

// Facility
// Constructors
// Parameterized
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score) : 
    FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), settlementName(settlementName), status(FacilityStatus:: UNDER_CONSTRUCTIONS), timeLeft(price) {}

// Partial
Facility:: Facility(const FacilityType &type, const string &settlementName) :
    Facility(type.getName(), getSettlementName(), type.getCategory(), type.getCost(), type.getLifeQualityScore(), type.getEconomyScore(), type.getEnvironmentScore()) {}

const string& Facility::getSettlementName() const {
    return settlementName;
}
const int Facility::getTimeLeft() const {
    return timeLeft;
}
void Facility::setStatus(FacilityStatus newStatus) {
    status = newStatus;
}
const FacilityStatus& Facility::getStatus() const {
    return status;
}
// NOT SURE - how to treat the enum
FacilityStatus Facility::step() {
    if (getStatus() == FacilityStatus:: UNDER_CONSTRUCTIONS) {
        timeLeft--;
        cout << "timeleft: " + to_string(timeLeft) << endl;
        if (timeLeft == 0) {
            cout << "finished" << endl;
            setStatus(FacilityStatus:: OPERATIONAL);
        }
    }
    return getStatus();
}

string getStatusAsString (FacilityStatus status) {
    if (status == FacilityStatus::UNDER_CONSTRUCTIONS) return "UNDER_CONSTRUCTIONS";
    if (status == FacilityStatus::OPERATIONAL) return "OPERATIONAL";
}

// NOT SURE - how to implement methods like
// that (that has no details in the guide) 
const string Facility::toString() const {
    return "name: " + getName() + " status: " + getStatusAsString(getStatus()) + " timeLeft: " + to_string(getTimeLeft());
}

