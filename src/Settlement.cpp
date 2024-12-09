#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Settlement.h"

using std::string;
using std::vector;
using namespace std;

// Constructor
Settlement::Settlement(const string &newName, SettlementType newType) : 
                        name(newName), type(newType) {}

const string& Settlement::getName() const {
    return name;
}

SettlementType Settlement::getType() const {
    return type;
}

const string Settlement::toString() const {
    return "name: " + getName();
}
