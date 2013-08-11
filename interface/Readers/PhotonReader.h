/*
 * PhotonReader.h
 *
 *  Created on: April 17, 2013
 *      Author: N.Berry
 */

#ifndef PHOTONREADER_H_
#define PHOTONREADER_H_
#include "VariableReader.h"
#include "../RecoObjects/Photon.h"

namespace BAT {

class PhotonReader {
public:
	PhotonReader();
	PhotonReader(TChainPointer input, PhotonAlgorithm::value algo = PhotonAlgorithm::Default);
	virtual ~PhotonReader();
	const PhotonCollection& getPhotons();
	void initialise();
private:
	VariableReader<MultiDoublePointer> energyReader;
	VariableReader<MultiDoublePointer> pxReader;
	VariableReader<MultiDoublePointer> pyReader;
	VariableReader<MultiDoublePointer> pzReader;
	VariableReader<MultiDoublePointer> ecalIsolationReader;
	VariableReader<MultiDoublePointer> hcalIsolationReader;
	VariableReader<MultiDoublePointer> hcalIsolation2012Reader;
	VariableReader<MultiDoublePointer> trackerIsolationReader;
	VariableReader<MultiDoublePointer> superClusterEtaReader;
	VariableReader<MultiDoublePointer> sigmaIEtaIEtaReader;
	VariableReader<MultiDoublePointer> superClusterPhiReader;
	VariableReader<MultiDoublePointer> superClusterEnergyReader;
	VariableReader<MultiDoublePointer> superClusterSeedEnergyReader;
	VariableReader<MultiDoublePointer> Ecal3x3ClusterReader;
	VariableReader<MultiDoublePointer> Ecal5x5ClusterReader;
	VariableReader<MultiDoublePointer> HadOverEmReader;
	VariableReader<MultiDoublePointer> trackVetoReader;
	VariableReader<MultiDoublePointer> ConversionSafeElectronVetoReader;
	VariableReader<MultiDoublePointer> SingleTowerHoEReader;
	VariableReader<MultiDoublePointer> PFChargedHadronIsoReader;
	VariableReader<MultiDoublePointer> PFNeutralHadronIsoReader;
	VariableReader<MultiDoublePointer> PFPhotonIsoReader;
	
	PhotonAlgorithm::value algorithm;
	
	PhotonCollection photons;
	void readPhotons();
};

}

#endif /* PHOTONREADER_H_ */
