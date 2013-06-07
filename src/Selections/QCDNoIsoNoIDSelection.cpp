/*
 * QCDNoIsoNoIDSelection.cpp
 *
 *  Created on: 14 Jun 2012
 *      Author: kreczko
 */

#include "../../interface/Selections/QCDNoIsoNoIDSelection.h"

namespace BAT {

QCDNoIsoNoIDSelection::QCDNoIsoNoIDSelection(unsigned int numberOfSelectionSteps) :
	QCDAntiIDEPlusJetsSelection(numberOfSelectionSteps), //
			QCDPFRelIsoEPlusJetsSelection(numberOfSelectionSteps) {

}

QCDNoIsoNoIDSelection::~QCDNoIsoNoIDSelection() {
}

bool QCDNoIsoNoIDSelection::isGoodElectron(const ElectronPointer electron) const {
	return QCDPFRelIsoEPlusJetsSelection::isGoodElectron(electron) || QCDAntiIDEPlusJetsSelection::isGoodElectron(
			electron);
}

bool QCDNoIsoNoIDSelection::hasExactlyOneIsolatedLepton(const EventPtr event) const {
	return QCDPFRelIsoEPlusJetsSelection::hasExactlyOneIsolatedLepton(event);
}

const LeptonPointer QCDNoIsoNoIDSelection::signalLepton(const EventPtr event) const {
	return QCDPFRelIsoEPlusJetsSelection::signalLepton(event);
}

bool QCDNoIsoNoIDSelection::isIsolated(const LeptonPointer lepton) const {
	return QCDPFRelIsoEPlusJetsSelection::isIsolated(lepton);
}

bool QCDNoIsoNoIDSelection::passesSelectionUpToStep(const EventPtr event, unsigned int step) const {
	return QCDPFRelIsoEPlusJetsSelection::passesSelectionUpToStep(event, step);
}

bool QCDNoIsoNoIDSelection::passesSelectionStep(const EventPtr event, unsigned int selectionStep) const{
	return QCDPFRelIsoEPlusJetsSelection::passesSelectionStep(event, selectionStep);
}

unsigned int QCDNoIsoNoIDSelection::prescale(const EventPtr event) const {
	return QCDPFRelIsoEPlusJetsSelection::prescale(event);
}
const JetCollection QCDNoIsoNoIDSelection::cleanedJets(const EventPtr event) const {
	return QCDPFRelIsoEPlusJetsSelection::cleanedJets(event);
}
const JetCollection QCDNoIsoNoIDSelection::cleanedBJets(const EventPtr event) const {
	return QCDPFRelIsoEPlusJetsSelection::cleanedBJets(event);
}

bool QCDNoIsoNoIDSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {

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

const PhotonCollection QCDNoIsoNoIDSelection::signalPhotons(const EventPtr event) const {

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
