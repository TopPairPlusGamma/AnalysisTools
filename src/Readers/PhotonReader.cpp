/*
 * PhotonReader.cpp
 *
 *  Created on: April 17, 2013
 *      Author: N.Berry
 */

#include "../../interface/Readers/PhotonReader.h"
#include "../../interface/GlobalVariables.h"
#include <iostream>

using namespace std;

namespace BAT {

PhotonReader::PhotonReader() : 
		energyReader(), //
		pxReader(), //
		pyReader(), //
		pzReader(), //
		ecalIsolationReader(), //
		hcalIsolationReader(), //
		hcalIsolation2012Reader(),
		trackerIsolationReader(), //
		superClusterEtaReader(), //
		sigmaIEtaIEtaReader(), //
		superClusterPhiReader(), //
		superClusterEnergyReader(), //
		superClusterSeedEnergyReader(),//
		Ecal3x3ClusterReader(), //
		Ecal5x5ClusterReader(), //
		HadOverEmReader(), //
		trackVetoReader(), //
		ConversionSafeElectronVetoReader(),
		SingleTowerHoEReader(),
		PFChargedHadronIsoReader(),
		PFNeutralHadronIsoReader(),
		PFPhotonIsoReader(),
		phoSCChIsoReader(),
		phoSCNuIsoReader(),
		phoSCPhIsoReader(),
		phoRandConeChIsoReader(),
		phoRandConeNuIsoReader(),
		phoRandConePhIsoReader(),
		algorithm(PhotonAlgorithm::Default), //
		photons() {
}

PhotonReader::PhotonReader(TChainPointer input, PhotonAlgorithm::value algo) :
 		energyReader(input, PhotonAlgorithm::prefixes.at(algo) + ".Energy"), //
 		pxReader(input, PhotonAlgorithm::prefixes.at(algo) + ".Px"), //
 		pyReader(input, PhotonAlgorithm::prefixes.at(algo) + ".Py"), //
 	        pzReader(input, PhotonAlgorithm::prefixes.at(algo) + ".Pz"), //
		ecalIsolationReader(input, PhotonAlgorithm::prefixes.at(algo) + ".EcalIso"), //
		hcalIsolationReader(input, PhotonAlgorithm::prefixes.at(algo) + ".HcalIso"), //
		hcalIsolation2012Reader(input, PhotonAlgorithm::prefixes.at(algo) + ".HcalIso2012"),
		trackerIsolationReader(input, PhotonAlgorithm::prefixes.at(algo) + ".TrkIso"), //
		superClusterEtaReader(input, PhotonAlgorithm::prefixes.at(algo) + ".SCeta"), //
		sigmaIEtaIEtaReader(input, PhotonAlgorithm::prefixes.at(algo) + ".SigmaIEtaIEta"), //
		superClusterPhiReader(input, PhotonAlgorithm::prefixes.at(algo) + ".SCphi"), //
		superClusterEnergyReader(input, PhotonAlgorithm::prefixes.at(algo) + ".SCenergy"), //
		superClusterSeedEnergyReader(input, PhotonAlgorithm::prefixes.at(algo) + ".SCseedEnergy"), //
		Ecal3x3ClusterReader(input, PhotonAlgorithm::prefixes.at(algo) + ".E3x3"), //
		Ecal5x5ClusterReader(input, PhotonAlgorithm::prefixes.at(algo) + ".E5x5"), //
		HadOverEmReader(input, PhotonAlgorithm::prefixes.at(algo) + ".HoE"),
		trackVetoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".TrkVeto"),
		ConversionSafeElectronVetoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".ConvSafeEle"),
		SingleTowerHoEReader(input, PhotonAlgorithm::prefixes.at(algo) + ".HtowoE"),
		PFChargedHadronIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".PfChargedIso03"),
		PFNeutralHadronIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".PfNeutralIso03"),
		PFPhotonIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".PfPhotonIso03"),
		phoSCChIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".phoSCChIso"),
		phoSCNuIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".phoSCNuIso"),
		phoSCPhIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".phoSCPhIso"),
		phoRandConeChIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".phoRandConeChIso"),
		phoRandConeNuIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".phoRandConeNuIso"),
		phoRandConePhIsoReader(input, PhotonAlgorithm::prefixes.at(algo) + ".phoRandConePhIso"),
		algorithm(algo), photons() {
}


void PhotonReader::initialise() {
		energyReader.initialise();
		pxReader.initialise();
		pyReader.initialise();
		pzReader.initialise();
		ecalIsolationReader.initialise();
		hcalIsolationReader.initialise();
		hcalIsolation2012Reader.initialise();
		trackerIsolationReader.initialise();
		superClusterEtaReader.initialise();
		sigmaIEtaIEtaReader.initialise();
		superClusterPhiReader.initialise();
		superClusterEnergyReader.initialise();
		superClusterSeedEnergyReader.initialise();
		Ecal3x3ClusterReader.initialise();
		Ecal5x5ClusterReader.initialise();
		HadOverEmReader.initialise();
		trackVetoReader.initialise();
		ConversionSafeElectronVetoReader.initialise();
		SingleTowerHoEReader.initialise();
		PFChargedHadronIsoReader.initialise();
		PFNeutralHadronIsoReader.initialise();
		PFPhotonIsoReader.initialise();
		phoSCChIsoReader.initialise();
		phoSCNuIsoReader.initialise();
		phoSCPhIsoReader.initialise();
		phoRandConeChIsoReader.initialise();
		phoRandConeNuIsoReader.initialise();
		phoRandConePhIsoReader.initialise();
}		

const PhotonCollection& PhotonReader::getPhotons() {
		if (photons.empty() == false)
			photons.clear();
		readPhotons();
		return photons;
}		

void PhotonReader::readPhotons() {


	for (unsigned int index = 0; index < energyReader.size(); index++) {
		double energy = energyReader.getVariableAt(index);
		double px = pxReader.getVariableAt(index);
		double py = pyReader.getVariableAt(index);
		double pz = pzReader.getVariableAt(index);
		PhotonPointer photon(new Photon(energy, px, py, pz));
		photon->setUsedAlgorithm(algorithm);
		photon->setEcalIsolation(ecalIsolationReader.getVariableAt(index));
		photon->setHcalIsolation(hcalIsolationReader.getVariableAt(index));
		photon->setHcalIsolation2012(hcalIsolation2012Reader.getVariableAt(index));
		photon->setTrackerIsolation(trackerIsolationReader.getVariableAt(index));
		photon->setSuperClusterEta(superClusterEtaReader.getVariableAt(index));
		photon->setSigmaIEtaIEta(sigmaIEtaIEtaReader.getVariableAt(index));
		photon->setSuperClusterPhi(superClusterPhiReader.getVariableAt(index));
		photon->setSuperClusterEnergy(superClusterEnergyReader.getVariableAt(index));
		photon->setSuperClusterSeedEnergy(superClusterSeedEnergyReader.getVariableAt(index));
		photon->setEcal3x3Cluster(Ecal3x3ClusterReader.getVariableAt(index));
		photon->setEcal5x5Cluster(Ecal5x5ClusterReader.getVariableAt(index));
		photon->setHadOverEm(HadOverEmReader.getVariableAt(index));
		photon->setTrackVeto(trackVetoReader.getVariableAt(index));
		photon->setConversionSafeElectronVeto(ConversionSafeElectronVetoReader.getVariableAt(index));
		photon->setSingleTowerHoE(SingleTowerHoEReader.getVariableAt(index));
		photon->setPFChargedHadronIso(PFChargedHadronIsoReader.getVariableAt(index));
		photon->setPFNeutralHadronIso(PFNeutralHadronIsoReader.getVariableAt(index));
		photon->setPFPhotonIso(PFPhotonIsoReader.getVariableAt(index));
		photon->setphoSCChIso(phoSCChIsoReader.getVariableAt(index));
		photon->setphoSCNuIso(phoSCNuIsoReader.getVariableAt(index));
		photon->setphoSCPhIso(phoSCPhIsoReader.getVariableAt(index));
		photon->setphoRandConeChIso(phoRandConeChIsoReader.getVariableAt(index));
		photon->setphoRandConeNuIso(phoRandConeNuIsoReader.getVariableAt(index));
		photon->setphoRandConePhIso(phoRandConePhIsoReader.getVariableAt(index));
		photons.push_back(photon);
		}
}

PhotonReader::~PhotonReader() {
}

}

		
