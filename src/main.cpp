// #include "Simulation.h"
#include <iostream>
// #include <Settlement.h>
#include <../include/Settlement.h>
#include <../include/Facility.h>
#include <../include/SelectionPolicy.h>
#include <../include/Plan.h>
#include <climits>

using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    cout << "Hello World!5" << endl;
    

    const string s = "abc";
    Settlement settlement = Settlement(s, SettlementType::VILLAGE);
    cout << settlement.getName() << endl;
                                                                              // 1, 1, 2         
    FacilityType facilityT = FacilityType("setty", FacilityCategory::ECONOMY, 20, 3, 7, 5);//4,8,7=3
    FacilityType facilityT2 = FacilityType("setty2", FacilityCategory::ENVIRONMENT, 20, 6, 4, 6);//7,5,8=3
    FacilityType facilityT3 = FacilityType("setty3", FacilityCategory::ENVIRONMENT, 20, 2, 3, 0);//3,4,2=2
    FacilityType facilityT4 = FacilityType("setty4", FacilityCategory::ECONOMY, 20, 5, 5, 4);//3,4,6=3
    FacilityType facilityT5 = FacilityType("setty5", FacilityCategory::LIFE_QUALITY, 20, 4, 7, 3);//5,8,5=3
    FacilityType facilityT6 = FacilityType("setty6", FacilityCategory::ECONOMY, 20, 4, 4, 4);//5,5,6=1

    Facility facility = Facility("abc", settlement.getName(),
        FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
    Facility facility2 = Facility("def", settlement.getName(),
        FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
    cout << facility.toString() << endl;
    
    vector<FacilityType> facilitiesOptions = { facilityT, facilityT2, facilityT3,
        facilityT4, facilityT5, facilityT6 };
    // NaiveSelection ns = NaiveSelection();
    BalancedSelection bs = BalancedSelection(1, 1, 2);
    cout << bs.selectFacility(facilitiesOptions).getName() << endl;
    cout << bs.selectFacility(facilitiesOptions).getName() << endl;
    cout << bs.selectFacility(facilitiesOptions).getName() << endl;
    cout << bs.selectFacility(facilitiesOptions).getName() << endl;

    vector<Facility*> underConstruction = { new Facility(facilityT, s), new Facility(facilityT2, s), new Facility(facilityT3, s) };
    Plan* p1 = new Plan(100, settlement, new NaiveSelection(), facilitiesOptions);


    // cout << ss.selectFacility(facilitiesOptions).getName() << endl;

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