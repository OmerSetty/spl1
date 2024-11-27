// #include "Simulation.h"
#include <iostream>
// #include <Settlement.h>
#include <../include/Settlement.h>
#include <../include/Facility.h>
#include <../include/SelectionPolicy.h>
#include <climits>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    cout << "Hello World!5" << endl;
    

    const string s = "abc";
    Settlement settlement = Settlement(s, SettlementType::VILLAGE);
    cout << settlement.getName() << endl;

    FacilityType facilityT = FacilityType("setty", FacilityCategory::ECONOMY, 20, 3, 4, 5);
    FacilityType facilityT2 = FacilityType("setty2", FacilityCategory::ENVIRONMENT, 20, 3, 4, 5);
    FacilityType facilityT3 = FacilityType("setty3", FacilityCategory::ENVIRONMENT, 20, 3, 4, 5);
    FacilityType facilityT4 = FacilityType("setty4", FacilityCategory::ECONOMY, 20, 3, 4, 5);
    FacilityType facilityT5 = FacilityType("setty5", FacilityCategory::LIFE_QUALITY, 20, 3, 4, 5);
    FacilityType facilityT6 = FacilityType("setty6", FacilityCategory::ECONOMY, 20, 3, 4, 5);

    Facility facility = Facility("abc", settlement.getName(),
        FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
    Facility facility2 = Facility("def", settlement.getName(),
        FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
    cout << facility.toString() << endl;
    
    vector<FacilityType> facilitiesOptions = { facilityT, facilityT2, facilityT3,
        facilityT4, facilityT5, facilityT6 };
    // NaiveSelection ns = NaiveSelection();
    SustainabilitySelection ss = SustainabilitySelection();
    cout << ss.selectFacility(facilitiesOptions).getName() << endl;
    cout << ss.selectFacility(facilitiesOptions).getName() << endl;
    // cout << ss.selectFacility(facilitiesOptions).getName() << endl;
    cout << INT_MAX << endl;

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