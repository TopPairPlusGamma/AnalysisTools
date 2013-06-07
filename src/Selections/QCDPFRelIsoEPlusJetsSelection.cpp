/*
 * QCDPFRelIsoSelection.cpp
 *
 *  Created on: 12 Apr 2012
 *      Author: kreczko
 */

#include "../../interface/Selections/QCDPFRelIsoEPlusJetsSelection.h"
#include <iostream>

using namespace std;

namespace BAT {

QCDPFRelIsoEPlusJetsSelection::QCDPFRelIsoEPlusJetsSelection(unsigned int numberOfSelectionSteps) :
		TopPairEPlusJetsReferenceSelection(numberOfSelectionSteps) {

}

QCDPFRelIsoEPlusJetsSelection::~QCDPFRelIsoEPlusJetsSelection() {
}

bool QCDPFRelIsoEPlusJetsSelection::passesTriggerSelection(const EventPtr event) const {
	if (!useNonIsoTrigger_)
		return TopPairEPlusJetsReferenceSelection::passesTriggerSelection(event);
	else {
		unsigned int runNumber(event->runnumber());
		if (event->isRealData()) {
			if (runNumber >= 160404 && runNumber <= 163869)
				return event->HLT(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30);
			else if (runNumber > 163869 && runNumber <= 178380)
				return event->HLT(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30);
			else if (runNumber > 178380)
				return event->HLT(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_TriCentralPFJet30);
			else
				return false;
		} else {
			//Fall11 MC
			return event->HLT(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30);
		}
	}
}

bool QCDPFRelIsoEPlusJetsSelection::hasExactlyOneIsolatedLepton(const EventPtr event) const {
	const ElectronCollection allElectrons(event->Electrons());

	unsigned int nGoodElectrons(0), nGoodIsolatedElectrons(0);

	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		const ElectronPointer electron(allElectrons.at(index));
		if (isGoodElectron(electron)) {
			++nGoodElectrons;
			if (isIsolated(electron))
				++nGoodIsolatedElectrons;
		}
	}

	return nGoodElectrons > 0 && nGoodIsolatedElectrons < 2;
}

bool QCDPFRelIsoEPlusJetsSelection::passesConversionVeto(const EventPtr event) const {
	const LeptonPointer signalLepton = this->signalLepton(event);
	const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
	return signalElectron->passConversionVeto();
}

const ElectronPointer QCDPFRelIsoEPlusJetsSelection::MostIsolatedElectron(const ElectronCollection& electrons) const {
	double bestIsolation = 999999999;
	unsigned int bestIsolatedLepton = 990;

	for (unsigned int index = 0; index < electrons.size(); ++index) {
		double currentIsolation(electrons.at(index)->pfRelativeIsolation(0.3));

		if (currentIsolation < bestIsolation) {
			bestIsolation = currentIsolation;
			bestIsolatedLepton = index;
		}
	}
	ElectronPointer electron(new Electron());

	if (bestIsolatedLepton < electrons.size())
		electron = electrons.at(bestIsolatedLepton);

	return electron;
}

unsigned int QCDPFRelIsoEPlusJetsSelection::prescale(const EventPtr event) const {
	unsigned int runNumber(event->runnumber());
	unsigned int prescale(1);

	if (useNonIsoTrigger_) {
		if (event->isRealData()) {
			if (runNumber >= 160404 && runNumber <= 163869)
				prescale = event->HLTPrescale(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30);
			else if (runNumber > 163869 && runNumber <= 178380)
				prescale = event->HLTPrescale(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30);
			else if (runNumber > 178380)
				prescale = event->HLTPrescale(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_TriCentralPFJet30);
		} else
			prescale = event->HLTPrescale(HLTriggers::HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30);

	}
	return prescale;
}

const LeptonPointer QCDPFRelIsoEPlusJetsSelection::signalLepton(const EventPtr event) const {
//	if (!hasExactlyOneIsolatedLepton(event)) {
//		cerr << "An error occurred in QCD*Selection in event = " << event->eventnumber();
//		cerr << ", run = " << event->runnumber() << ", lumi = " << event->lumiblock() << "!" << endl;
//		cerr << "File = " << event->file() << endl;
//		cerr
//				<< "Access exception: No signal lepton could be found. Event doesn't pass 'hasExactlyOneIsolatedLepton' selection"
//				<< endl;
//		throw "Access exception: No signal lepton could be found. Event doesn't pass 'hasExactlyOneIsolatedLepton' selection";
//	}

	const ElectronCollection allElectrons(event->Electrons());
	ElectronCollection goodElectrons;
	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		const ElectronPointer electron(allElectrons.at(index));
		if (isGoodElectron(electron)) {
			goodElectrons.push_back(electron);
		}
	}

	return MostIsolatedElectron(goodElectrons);

}

bool QCDPFRelIsoEPlusJetsSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {

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

const PhotonCollection QCDPFRelIsoEPlusJetsSelection::signalPhotons(const EventPtr event) const {

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
