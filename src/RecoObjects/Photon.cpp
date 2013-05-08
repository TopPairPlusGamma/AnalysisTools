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

namespace BAT {

const double initialBigValue = 123456789;

Photon::Photon() :
		Particle(), 
		usedAlgorithm_(PhotonAlgorithm::Default),
		EcalIso(initialBigValue),
		HcalIso(initialBigValue),
		TrackIso(initialBigValue),
		superCluster_Eta(initialBigValue), 
		sigma_IEtaIEta(initialBigValue),
		superCluster_Phi(initialBigValue),
		superCluster_Energy(initialBigValue),
		superCluster_SeedEnergy(initialBigValue),
		Ecal_3x3_Cluster(initialBigValue),
		Ecal_5x5_Cluster(initialBigValue),
		hadOverEm(initialBigValue),
		trackVeto(initialBigValue){

}

Photon::Photon(double energy, double px, double py, double pz) :
		Particle(energy, px, py, pz),
		usedAlgorithm_(PhotonAlgorithm::Default),
		EcalIso(initialBigValue),
		HcalIso(initialBigValue),
		TrackIso(initialBigValue),
		superCluster_Eta(initialBigValue), 
		sigma_IEtaIEta(initialBigValue),
		superCluster_Phi(initialBigValue),
		superCluster_Energy(initialBigValue),
		superCluster_SeedEnergy(initialBigValue),
		Ecal_3x3_Cluster(initialBigValue),
		Ecal_5x5_Cluster(initialBigValue),
		hadOverEm(initialBigValue),
		trackVeto(initialBigValue){
		
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

double Photon::ecalIsolation() const {
	return EcalIso;
}

double Photon::hcalIsolation() const {
	return HcalIso;
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

bool Photon::isInBarrelRegion() const {
	return fabs(superClusterEta()) < 1.4442;
}

bool Photon::isInCrack() const {
	return !isInBarrelRegion() && !isInEndCapRegion();
}

bool Photon::isInEndCapRegion() const {
	return fabs(superClusterEta()) > 1.5660;
}

}
