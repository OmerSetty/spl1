#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Action.h"
enum class SettlementType;
enum class FacilityCategory;

// Base Action Methods
BaseAction:: BaseAction() {

}
ActionStatus BaseAction:: getStatus() const {

}

void BaseAction:: complete() {

}

void BaseAction:: error(string errorMsg) {

}

const string& BaseAction:: getErrorMsg() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SimulateStep methods

SimulateStep:: SimulateStep(const int numOfSteps) {

}

void SimulateStep:: act(Simulation &simulation) {

}

const string SimulateStep:: SimulateStep:: toString() const {

}

SimulateStep* SimulateStep:: clone() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddPlan methods

AddPlan:: AddPlan(const string &settlementName, const string &selectionPolicy) {

}
void AddPlan:: act(Simulation &simulation) {

}

const string AddPlan:: toString() const {

}

AddPlan* AddPlan:: clone() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddSettlement methods

AddSettlement:: AddSettlement(const string &settlementName,SettlementType settlementType) {

}

void AddSettlement:: act(Simulation &simulation) {

}

AddSettlement* AddSettlement:: clone() const {

}
const string AddSettlement:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AddFacility methods

AddFacility:: AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore) {

}

void AddFacility:: act(Simulation &simulation) {

}

AddFacility* AddFacility:: clone() const {

}

const string AddFacility:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PrintPlanStatus methods

PrintPlanStatus:: PrintPlanStatus(int planId) {

}

void PrintPlanStatus:: act(Simulation &simulation) {

}
PrintPlanStatus* PrintPlanStatus:: clone() const {

}

const string PrintPlanStatus:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ChangePlanPolicy methods

ChangePlanPolicy:: ChangePlanPolicy(const int planId, const string &newPolicy) {

}

void ChangePlanPolicy:: act(Simulation &simulation) {

}

ChangePlanPolicy* ChangePlanPolicy:: clone() const {

}

const string ChangePlanPolicy:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PrintActionsLog methods

PrintActionsLog:: PrintActionsLog() {

}

void PrintActionsLog:: act(Simulation &simulation) {

}

PrintActionsLog* PrintActionsLog:: clone() const {

}

const string PrintActionsLog:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Close methods

Close:: Close() {

}

void Close:: act(Simulation &simulation) {

}

Close* Close:: clone() const {

}

const string Close:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BackupSimulation methods

BackupSimulation:: BackupSimulation() {

}

void BackupSimulation:: act(Simulation &simulation) {

}

BackupSimulation* BackupSimulation:: clone() const {

}

const string BackupSimulation:: toString() const {

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RestoreSimulation methods

RestoreSimulation:: RestoreSimulation() {

}

void RestoreSimulation:: act(Simulation &simulation) {

}

RestoreSimulation* RestoreSimulation:: clone() const {

}

const string RestoreSimulation:: toString() const {

}