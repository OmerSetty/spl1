// #include "Simulation.h"
#include <iostream>
// #include <Settlement.h>
#include <../include/Settlement.h>
#include <../include/Facility.h>
#include <../include/SelectionPolicy.h>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    cout << "Hello World!5" << endl;
    

    const string s = "abc";
    Settlement settlement = Settlement(s, SettlementType::VILLAGE);
    cout << settlement.getName() << endl;

    FacilityType facilityT = FacilityType("setty", FacilityCategory::ECONOMY, 20, 3, 4, 5);

    Facility facility = Facility("abc", settlement.getName(),
        FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
    Facility facility2 = Facility("def", settlement.getName(),
        FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
    cout << facility.toString() << endl;

    NaiveSelection ns = NaiveSelection();
    cout << ns.toString() << endl;
    vector<FacilityType> facilitiesOptions = { facilityT };
    // facilitiesOptions.push_back(facility);
    ns.selectFacility(facilitiesOptions);
    cout << ns.toString() << endl;
    // facilitiesOptions.push_back(facility2);
    // ns.selectFacility(facilitiesOptions);
    // cout << ns.toString() << endl;

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