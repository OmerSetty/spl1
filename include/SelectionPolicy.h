#pragma once
#include <vector>
#include "Facility.h"
using std::vector;

class SelectionPolicy {
    public:
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) = 0;
        virtual const string toString() const = 0;
        // virtual SelectionPolicy* clone() const = 0;
        // virtual ~SelectionPolicy() = default;
};

class NaiveSelection: public SelectionPolicy {
    public:
        NaiveSelection();
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        virtual const string toString() const override;
        // virtual NaiveSelection *clone() const override;
        // ~NaiveSelection() override = default;
    private:
        int lastSelectedIndex;
};

class BalancedSelection: public SelectionPolicy {
    public:
        BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        virtual const string toString() const override;
        // virtual BalancedSelection *clone() const override;
        // ~BalancedSelection() override = default;
    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;
};

class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        virtual const string toString() const override;
        // virtual EconomySelection *clone() const override;
        // ~EconomySelection() override = default;
    private:
        int lastSelectedIndex;
};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        virtual const string toString() const override;
        // virtual SustainabilitySelection *clone() const override;
        // ~SustainabilitySelection() override = default;
    private:
        int lastSelectedIndex;
};