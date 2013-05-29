/*
 * Photon.cpp
 *
 *  Created on: 22 April 2013
 *      Author: Nik Berry
 */

#include "../../interface/RecoObjects/Photon.h"
#include "../../interface/GlobalVariables.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

namespace BAT {

const double initialBigValue = 123456789;

Photon::Photon() :
		Particle(), 
		usedAlgorithm_(PhotonAlgorithm::Default),
		EcalIso(initialBigValue),
		HcalIso(initialBigValue),
		HcalIso2012(initialBigValue),
		TrackIso(initialBigValue),
		superCluster_Eta(initialBigValue), 
		sigma_IEtaIEta(initialBigValue),
		superCluster_Phi(initialBigValue),
		superCluster_Energy(initialBigValue),
		superCluster_SeedEnergy(initialBigValue),
		Ecal_3x3_Cluster(initialBigValue),
		Ecal_5x5_Cluster(initialBigValue),
		hadOverEm(initialBigValue),
		trackVeto(initialBigValue),
		Conversion_Safe_Electron_Veto(initialBigValue),
		singleTowerHoE(initialBigValue),
		pfChargedHadronIso(initialBigValue),
		pfNeutralHadronIso(initialBigValue),
		pfPhotonIso(initialBigValue),
		rhocorrectedpfChargedIso(initialBigValue),
		rhocorrectedpfNeutralIso(initialBigValue),
		rhocorrectedpfPhotonIso(initialBigValue){

}

Photon::Photon(double energy, double px, double py, double pz) :
		Particle(energy, px, py, pz),
		usedAlgorithm_(PhotonAlgorithm::Default),
		EcalIso(initialBigValue),
		HcalIso(initialBigValue),
		HcalIso2012(initialBigValue),
		TrackIso(initialBigValue),
		superCluster_Eta(initialBigValue), 
		sigma_IEtaIEta(initialBigValue),
		superCluster_Phi(initialBigValue),
		superCluster_Energy(initialBigValue),
		superCluster_SeedEnergy(initialBigValue),
		Ecal_3x3_Cluster(initialBigValue),
		Ecal_5x5_Cluster(initialBigValue),
		hadOverEm(initialBigValue),
		trackVeto(initialBigValue),
		Conversion_Safe_Electron_Veto(initialBigValue),
		singleTowerHoE(initialBigValue),
		pfChargedHadronIso(initialBigValue),
		pfNeutralHadronIso(initialBigValue),
		pfPhotonIso(initialBigValue),
		rhocorrectedpfChargedIso(initialBigValue),
		rhocorrectedpfNeutralIso(initialBigValue),
		rhocorrectedpfPhotonIso(initialBigValue){
		
}

Photon::~Photon() {
}

void Photon::setUsedAlgorithm(PhotonAlgorithm::value algorithm) {
	usedAlgorithm_ = algorithm;
}

void Photon::setEcalIsolation(double EIso){
	EcalIso = EIso;
}

void Photon::setHcalIsolation(double HIso){
	HcalIso = HIso;
}

void Photon::setHcalIsolation2012(double HIso2012){
	HcalIso2012 = HIso2012;
}

void Photon::setTrackerIsolation(double TrckIso){
	TrackIso = TrckIso;
}	
	
void Photon::setSuperClusterEta(double eta) {
	superCluster_Eta = eta;
}

void Photon::setSigmaIEtaIEta(double sigma) {
	sigma_IEtaIEta = sigma;
}

void Photon::setSuperClusterPhi(double phi){
	superCluster_Phi = phi;
}

void Photon::setSuperClusterEnergy(double SCenergy){
	superCluster_Energy = SCenergy;
}

void Photon::setSuperClusterSeedEnergy(double SCseedE){
	superCluster_SeedEnergy = SCseedE;
}

void Photon::setEcal3x3Cluster(double E3x3){
	Ecal_3x3_Cluster = E3x3;
}

void Photon::setEcal5x5Cluster(double E5x5){
	Ecal_5x5_Cluster = E5x5;
}

void Photon::setHadOverEm(double HoverE) {
	hadOverEm = HoverE;
}

void Photon::setTrackVeto(double TrkVeto) {
	trackVeto = TrkVeto;
}

void Photon::setConversionSafeElectronVeto(double ConvSEVeto) {
	Conversion_Safe_Electron_Veto = ConvSEVeto;
}

void Photon::setSingleTowerHoE(double HtowoE) {
	singleTowerHoE = HtowoE;
}

void Photon::setPFChargedHadronIso(double PfChargedIso03) {
	pfChargedHadronIso = PfChargedIso03;
}

void Photon::setPFNeutralHadronIso(double PfNeutralIso03) {
	pfNeutralHadronIso = PfNeutralIso03;
}

void Photon::setPFPhotonIso(double PfPhotonIso03) {
	pfPhotonIso = PfPhotonIso03;
}

void Photon::setRhoCorrectedPFChargedHadronIso(double RhoCorrPfChargedIso03) {
	rhocorrectedpfChargedIso = RhoCorrPfChargedIso03;
}

void Photon::setRhoCorrectedPFNeutralHadronIso(double RhoCorrPfNeutralIso03) {
	rhocorrectedpfNeutralIso = RhoCorrPfNeutralIso03;
}

void Photon::setRhoCorrectedPFPhotonIso(double RhoCorrPfPhotonIso03) {
	rhocorrectedpfPhotonIso = RhoCorrPfPhotonIso03;
}

double Photon::ecalIsolation() const {
	return EcalIso;
}

double Photon::hcalIsolation() const {
	return HcalIso;
}

double Photon::hcalIsolation2012() const {
	return HcalIso2012;
}

double Photon::trackerIsolation() const {
	return TrackIso;
}

double Photon::superClusterEta() const {
	return superCluster_Eta;
}

double Photon::sigmaIEtaIEta() const {
	return sigma_IEtaIEta;
}

double Photon::superClusterPhi() const {
	return superCluster_Phi;
}

double Photon::superClusterEnergy() const {
	return superCluster_Energy;
}

double Photon::superClusterSeedEnergy() const {
	return superCluster_SeedEnergy;
}

double Photon::Ecal3x3Cluster() const {
	return Ecal_3x3_Cluster;
}

double Photon::Ecal5x5Cluster() const {
	return Ecal_5x5_Cluster;
}

double Photon::HadOverEm() const {
	return hadOverEm;
}

double Photon::TrackVeto() const {
	return trackVeto;
}

double Photon::ConversionSafeElectronVeto() const {
	return Conversion_Safe_Electron_Veto;
}

double Photon::SingleTowerHoE() const {
	return singleTowerHoE;
}

double Photon::PFChargedHadronIso() const {
	return pfChargedHadronIso;
}

double Photon::PFNeutralHadronIso() const {
	return pfNeutralHadronIso;
}

double Photon::PFPhotonIso() const {
	return pfPhotonIso;
}

bool Photon::isInBarrelRegion() const {
	return fabs(superClusterEta()) < 1.4442;
}

bool Photon::isInCrack() const {
	return !isInBarrelRegion() && !isInEndCapRegion();
}

bool Photon::isInEndCapRegion() const {
	return fabs(superClusterEta()) > 1.5660;
}

string Photon::toString() const {
	stringstream out;
	out << Particle::toString();
	out << "Photon information" << "\n";
	return out.str();
}

double Photon::RhoCorrectedPFChargedHadronIso(double rho) const {
	double effectiveArea = 0;
	double eta = fabs(this->eta());
	if (eta < 1.)
		effectiveArea = 0.12;
	if (eta > 1. && eta < 1.479)
		effectiveArea = 0.01;
	if (eta > 1.479 && eta < 2.0)
		effectiveArea = 0.014;
	if (eta > 2.0 && eta < 2.2)
		effectiveArea = 0.012;
	if (eta > 2.2 && eta < 2.3)
		effectiveArea = 0.016;
	if (eta > 2.3 && eta < 2.4)
		effectiveArea = 0.020;
	if (eta > 2.4)
		effectiveArea = 0.012;

	double rhocorrectedpfChargedIso =	max(PFChargedHadronIso() - rho * effectiveArea, 0.);
	return rhocorrectedpfChargedIso;
}

double Photon::RhoCorrectedPFNeutralHadronIso(double rho) const {
	double effectiveArea = 0;
	double eta = fabs(this->eta());
	if (eta < 1.)
		effectiveArea = 0.030;
	if (eta > 1. && eta < 1.479)
		effectiveArea = 0.057;
	if (eta > 1.479 && eta < 2.0)
		effectiveArea = 0.039;
	if (eta > 2.0 && eta < 2.2)
		effectiveArea = 0.015;
	if (eta > 2.2 && eta < 2.3)
		effectiveArea = 0.024;
	if (eta > 2.3 && eta < 2.4)
		effectiveArea = 0.039;
	if (eta > 2.4)
		effectiveArea = 0.072;

	double rhocorrectedpfNeutralIso =	max(PFNeutralHadronIso() - rho * effectiveArea, 0.);
	return rhocorrectedpfNeutralIso;
}

double Photon::RhoCorrectedPFPhotonIso(double rho) const {
	double effectiveArea = 0;
	double eta = fabs(this->eta());
	if (eta < 1.)
		effectiveArea = 0.148;
	if (eta > 1. && eta < 1.479)
		effectiveArea = 0.13;
	if (eta > 1.479 && eta < 2.0)
		effectiveArea = 0.112;
	if (eta > 2.0 && eta < 2.2)
		effectiveArea = 0.216;
	if (eta > 2.2 && eta < 2.3)
		effectiveArea = 0.262;
	if (eta > 2.3 && eta < 2.4)
		effectiveArea = 0.26;
	if (eta > 2.4)
		effectiveArea = 0.266;

	double rhocorrectedpfPhotonIso =	max(PFPhotonIso() - rho * effectiveArea, 0.);
	return rhocorrectedpfPhotonIso;
}

}
