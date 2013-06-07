/*
 * QCDAntiIDEPlusJetsSelection.cpp
 *
 *  Created on: 28 May 2012
 *      Author: kreczko
 */

#include "../../interface/Selections/QCDAntiIDEPlusJetsSelection.h"

namespace BAT {

QCDAntiIDEPlusJetsSelection::QCDAntiIDEPlusJetsSelection(unsigned int numberOfSelectionSteps) :
		TopPairEPlusJetsReferenceSelection(numberOfSelectionSteps), useMVAID_(true) {

}

bool QCDAntiIDEPlusJetsSelection::isGoodElectron(const ElectronPointer electron) const {
	bool passesEtAndEta = electron->et() > 30. && fabs(electron->eta()) < 2.5 && !electron->isInCrack();
	bool passesD0 = fabs(electron->d0()) < 0.02; //cm

	bool passesAntiID = useMVAID_ ? passesMVAAntiID(electron) : passesWP80AntiID(electron);

	return passesEtAndEta && passesD0 && passesAntiID;
}

bool QCDAntiIDEPlusJetsSelection::isIsolated(const LeptonPointer lepton) const {
	return lepton->pfRelativeIsolation(0.3) < 0.2;
}

QCDAntiIDEPlusJetsSelection::~QCDAntiIDEPlusJetsSelection() {
}

void QCDAntiIDEPlusJetsSelection::useMVAID(bool use) {
	useMVAID_ = use;
}

bool QCDAntiIDEPlusJetsSelection::passesWP80AntiID(const ElectronPointer electron) const {
	bool passSigmaIetaIeta(false);
	bool passDphiIn(false);
	bool passDetaIn(false);
	bool passHoverE(false);

	if (electron->isInBarrelRegion()) {
		passSigmaIetaIeta = electron->sigmaIEtaIEta() < 0.01;
		passDphiIn = fabs(electron->dPhiIn()) < 0.06;
		passDetaIn = fabs(electron->dEtaIn()) < 0.004;
		passHoverE = electron->HadOverEm() < 0.12;
	}
	if (electron->isInEndCapRegion()) {
		passSigmaIetaIeta = electron->sigmaIEtaIEta() < 0.03;
		passDphiIn = fabs(electron->dPhiIn()) < 0.03;
		passDetaIn = fabs(electron->dEtaIn()) < 0.007;
		passHoverE = electron->HadOverEm() < 0.1;
	}

	bool failsTwoOfFourWP80Conditions((passSigmaIetaIeta + passDphiIn + passDetaIn + passHoverE) <= 2);
	return failsTwoOfFourWP80Conditions;
}
bool QCDAntiIDEPlusJetsSelection::passesMVAAntiID(const ElectronPointer electron) const {
	return electron->mvaTrigV0() < 0.0;
}

bool QCDAntiIDEPlusJetsSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {

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

const PhotonCollection QCDAntiIDEPlusJetsSelection::signalPhotons(const EventPtr event) const {

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
