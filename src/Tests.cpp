// // All the tests for the classes


// // Settlement
// const string s = "abc";
// Settlement settlement = Settlement(s, SettlementType::VILLAGE);
// cout << settlement.getName() << endl;

// // FacilityType
//                                                                         // 1, 1, 2         
// FacilityType facilityT = FacilityType("setty", FacilityCategory::ECONOMY, 20, 3, 7, 5);//4,8,7=3
// FacilityType facilityT2 = FacilityType("setty2", FacilityCategory::ENVIRONMENT, 20, 6, 4, 6);//7,5,8=3
// FacilityType facilityT3 = FacilityType("setty3", FacilityCategory::ENVIRONMENT, 20, 2, 3, 0);//3,4,2=2
// FacilityType facilityT4 = FacilityType("setty4", FacilityCategory::ECONOMY, 20, 5, 5, 4);//3,4,6=3
// FacilityType facilityT5 = FacilityType("setty5", FacilityCategory::LIFE_QUALITY, 20, 4, 7, 3);//5,8,5=3
// FacilityType facilityT6 = FacilityType("setty6", FacilityCategory::ECONOMY, 20, 4, 4, 4);//5,5,6=1

// // Facility
// Facility facility = Facility("abc", settlement.getName(),
//     FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
// Facility facility2 = Facility("def", settlement.getName(),
//     FacilityCategory::LIFE_QUALITY, 10, 3, 5, 2);
// cout << facility.toString() << endl;

// // SelectionPolicy
// vector<FacilityType> facilitiesOptions = { facilityT, facilityT2, facilityT3,
//         facilityT4, facilityT5, facilityT6 };
// BalancedSelection bs = BalancedSelection(1, 1, 2);
// cout << bs.selectFacility(facilitiesOptions).getName() << endl;
// cout << bs.selectFacility(facilitiesOptions).getName() << endl;
// cout << bs.selectFacility(facilitiesOptions).getName() << endl;
// cout << bs.selectFacility(facilitiesOptions).getName() << endl;

// // Plan
// Plan* p1 = Plan(100, settlement, new NaiveSelection(), facilitiesOptions);
// cout << (*p1).toString() << endl;
// cout << (*p1).getEconomyScore() << endl;
// cout << "step 1:" << endl;
// (*p1).step();
// cout << "step 2:" << endl;
// (*p1).step();
// (*p1).setSelectionPolicy(new SustainabilitySelection());
// cout << "step 3:" << endl;
// (*p1).step();
// cout << "step 4:" << endl;
// (*p1).step();
// cout << "step 5:" << endl;
// (*p1).step();
// cout << "step 6:" << endl;
// (*p1).step();


// plans = other.plans;
        // for (size_t i = 0; i < plans.size(); i++) {
        //     Plan& p = plans[i];
        //     delete &p;
        //     p.deleteSelectionPolicy();

        //     for (size_t j = 0; j < p.getFacilities().size(); j++) {
        //         delete p.getFacilities()[j];
        //     }
        //     p.clearFacilities();

        //     for (size_t j = 0; j < p.getUnderConstructionFacilities().size(); j++) {
        //         delete p.getUnderConstructionFacilities()[j];
        //     }
        //     p.clearUnderConstruction();
        // }