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
		algorithm(algo), photons() {
}


void PhotonReader::initialise() {
		energyReader.initialise();
		pxReader.initialise();
		pyReader.initialise();
		pzReader.initialise();
		ecalIsolationReader.initialise();
		hcalIsolationReader.initialise();
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
		photons.push_back(photon);
		}
}

PhotonReader::~PhotonReader() {
}

}

		
