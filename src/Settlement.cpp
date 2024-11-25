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
Settlement::Settlement(const string &name, SettlementType type) : name(name), type(type) {}

const string& Settlement::getName() const {
    return name;
}

SettlementType Settlement::getType() const {
    return type;
}

// NOT SURE - how to implement methods like
// that (that has no details in the guide) 
const string Settlement::toString() const {
    return "name: " + getName();
}
