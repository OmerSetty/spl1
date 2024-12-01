#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Simulation.h"
#include "Auxiliary.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using std::string;
using std::vector;
using namespace std;

class BaseAction;
class SelectionPolicy;
class Auxiliary;

Simulation::Simulation(const string &configFilePath) : isRunning(false) {
    cout << "in simulation constructor" << endl;
    std::ifstream file(configFilePath);
    string currentLine;
    while (std::getline(file, currentLine)) {
        // cout << currentLine << endl;
        vector<string> parsedArgs = Auxiliary::parseArguments(currentLine);
        for (string arg : parsedArgs) {
            cout << arg << endl;
        }
        
        // cout << parsedArgs << endl;
    }
}
