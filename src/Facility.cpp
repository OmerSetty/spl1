#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>
#include "Facility.h"

using std::string;
using std::vector;
using namespace std;

class FacilityType {
    public:
        FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
        name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score){}
  
}

// Constructor
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category,
const int price, const int lifeQuality_score, const int economy_score, const int environment_score) 
: name(name), settlementName(settlementName),
category(category), price(price)
,lifeQuality_score(lifeQuality_score), economy_score(economy_score),
environment_score(environment_score) {}

const string& Facility::getSettlementName() const {
    return settlementName;
}
int Facility::getTimeLeft() const {
    return timeLeft;
}
void Facility::setStatus(FacilityStatus status) {
    status = status;
}
const FacilityStatus& Facility::getStatus() const {
    return status;
}
// NOT SURE - how to treat the enum
void Facility::step() {
    if (getStatus() == UNDER_CONSTRUCTIONS) {
        timeLeft--;
        if (timeLeft == 0) setStatus(OPERATIONAL);
    }
}

// NOT SURE - how to implement methods like
// that (that has no details in the guide) 
const string Facility::toString() const {
    return "name: " + getName();
}
