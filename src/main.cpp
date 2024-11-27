// #include "Simulation.h"
#include <iostream>
// #include <Settlement.h>
#include <../include/Settlement.h>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    cout << "Hello World!5" << endl;
    const string s = "abc";
    Settlement set = Settlement(s, SettlementType::VILLAGE);
    cout << set.getName() << endl;    
    // if(argc!=2){
    //     cout << "usage: simulation <config_path>" << endl;
    //     return 0;g
    // }
    // string configurationFile = argv[1];
    // Simulation simulation(configurationFile);
    // simulation.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }
    return 0;
}