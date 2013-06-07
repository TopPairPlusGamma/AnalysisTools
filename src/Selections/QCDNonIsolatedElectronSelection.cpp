/*
 * QCDNonIsolatedElectronSelection.cpp
 *
 *  Created on: 12 Apr 2012
 *      Author: kreczko
 */

#include "../../interface/Selections/QCDNonIsolatedElectronSelection.h"

namespace BAT {

QCDNonIsolatedElectronSelection::QCDNonIsolatedElectronSelection(unsigned int numberOfSelectionSteps) :
		QCDPFRelIsoEPlusJetsSelection(numberOfSelectionSteps) {

}

QCDNonIsolatedElectronSelection::~QCDNonIsolatedElectronSelection() {
}

bool QCDNonIsolatedElectronSelection::hasExactlyOneIsolatedLepton(const EventPtr event) const {
	const ElectronCollection allElectrons(event->Electrons());
//
	unsigned int nGoodElectrons(0), nGoodNonIsolatedElectrons(0), nGoodIsolatedElectrons(0);

	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		const ElectronPointer electron(allElectrons.at(index));
		if (isGoodElectron(electron)) {
			++nGoodElectrons;
			if (electron->pfRelativeIsolation(0.3) < 0.2)
				++nGoodIsolatedElectrons;

			if (electron->pfRelativeIsolation(0.3) > 0.2)
				++nGoodNonIsolatedElectrons;
		}
	}
	//no electrons below 0.2 in PFRelIso and at least one electron with PFIso > 0.2
	return nGoodNonIsolatedElectrons > 0 && nGoodIsolatedElectrons == 0;
}

bool QCDNonIsolatedElectronSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {

	bool passesEtAndEta = photon->et() > 20 && fabs(photon->eta()) < 2.5 && !photon->isInCrack();
	bool passesTrackVeto = photon->TrackVeto() == false;
	bool passesHOverE = photon->SingleTowerHoE() < 0.05; // same for EE and EB
	bool passesShowerShape = false;
	bool passesTrackIso = false;
	bool passesEcalIso = false;
	bool passesHcalIso = false;
	bool passesPFChargedIso = false;
	bool passesPFNeutralIso = false;
	bool passesPFPhotonIso = false;
	
	if (photon->isInBarrelRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.011;
		passesTrackIso = photon->trackerIsolation() < 2.0 + 0.001 * (photon->et()) + 0.0167 * event->rho();
		passesEcalIso = photon->ecalIsolation() < 4.2 + 0.006 * (photon->et()) + 0.0183 * event->rho();
		passesHcalIso = photon->hcalIsolation() < 2.2 + 0.0025 * (photon->et()) + 0.062 * event->rho();  
		passesPFChargedIso = photon->PFChargedHadronIso() < 0.7;
		passesPFNeutralIso = photon->PFNeutralHadronIso() < 0.4 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->PFPhotonIso() < 0.5 + 0.005 * photon->pt(); 
	} else if (photon->isInEndCapRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.031;
		passesTrackIso = photon->trackerIsolation() < 2.0 + 0.001 * (photon->et()) + 0.032 * event->rho();
		passesEcalIso = photon->ecalIsolation() < 4.2 + 0.006 * (photon->et()) + 0.090 * event->rho();
		passesHcalIso = photon->hcalIsolation() < 2.2 + 0.0025 * (photon->et()) + 0.180 * event->rho();
		passesPFChargedIso = photon->PFChargedHadronIso() < 0.5; 
		passesPFNeutralIso = photon->PFNeutralHadronIso() < 1.5 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->PFPhotonIso() < 1.0 + 0.005 * photon->pt(); 
	} 
	
	return passesEtAndEta && passesTrackVeto && passesHOverE && passesShowerShape && passesTrackIso && passesEcalIso && passesHcalIso &&
	passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso;
}

const PhotonCollection QCDNonIsolatedElectronSelection::signalPhotons(const EventPtr event) const {

	const PhotonCollection allPhotons(event->Photons());
	PhotonCollection goodIsolatedPhotons;
	for (unsigned int index = 0; index < allPhotons.size(); ++index) {
		const PhotonPointer photon(allPhotons.at(index));
		if (isGoodPhoton(photon, event)){
			goodIsolatedPhotons.push_back(photon);
		}
	}

	return goodIsolatedPhotons;

} 

} /* namespace BAT */
