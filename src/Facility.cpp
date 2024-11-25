#include <iostream>
#include <algorithm>
#pragma once
#include <string>
#include <vector>
#include "Settlement.h"

using std::string;
using std::vector;
using namespace std;

// Constructor
Facility::Facility(const string &name, SettlementType type) : name(name), type(type) {}

const string& Facility::getName() const {
    return name;
}

SettlementType Facility::getType() const {
    return type;
}

// NOT SURE - how to implement methods like
// that (that has no details in the guide) 
const string Facility::toString() const {
    return "name: " + getName();
}
