/*
 * TopPairEMuReferenceSelection.cpp
 *
 *  Created on: 30 May 2013
 *      Author: N.Berry
 */

#include "../../interface/Selections/TopPairEMuReferenceSelection.h"
#include "../../interface/HighLevelTriggers.h"

using namespace std;

namespace BAT {

TopPairEMuReferenceSelection::TopPairEMuReferenceSelection(unsigned int numberOfSelectionSteps) : //
		BasicSelection(numberOfSelectionSteps) //
{

}

TopPairEMuReferenceSelection::~TopPairEMuReferenceSelection() {
}

bool TopPairEMuReferenceSelection::isGoodJet(const JetPointer jet) const {

	/**
	 * This function tests the jet ID and eta (and pt) range for jet
	 * The cut of 20 GeV is actually obsolete since we only store jets above that threshold.
	 * However, the jet id is only valid for jets above it.
	 */

	bool passesPtAndEta = jet->pt() > 20 && fabs(jet->eta()) < 2.5;
	bool passesJetID(false);
	JetAlgorithm::value algo = jet->getUsedAlgorithm();
	if (algo == JetAlgorithm::CA08PF || algo == JetAlgorithm::PF2PAT) { //PFJet
		bool passNOD = jet->NOD() > 1;
		bool passNHF = jet->NHF() < 0.99;
		bool passNEF = jet->NEF() < 0.99;
		bool passCHF = true;
		bool passNCH = true;
		bool passCEF = true;
		if (fabs(jet->eta()) < 2.4) {
			passCEF = jet->CEF() < 0.99;
			passCHF = jet->CHF() > 0;
			passNCH = jet->NCH() > 0;
		}
		passesJetID = passNOD && passCEF && passNHF && passNEF && passCHF && passNCH;

	} else { //assume CaloJet
		bool passesEMF = jet->emf() > 0.01;
		bool passesN90Hits = jet->n90Hits() > 1;
		bool passesFHPD = jet->fHPD() < 0.98;
		passesJetID = passesEMF && passesN90Hits && passesFHPD;
	}
	return passesPtAndEta && passesJetID;

}

const ElectronCollection TopPairEMuReferenceSelection::signalElectrons(const EventPtr event) const {

	const ElectronCollection allElectrons(event->Electrons());
	ElectronCollection goodIsolatedElectrons;
	
	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		const ElectronPointer electron(allElectrons.at(index));
		if (isGoodElectron(electron) && isIsolatedElectron(electron)) {
			goodIsolatedElectrons.push_back(electron);
		}
	}
	return goodIsolatedElectrons;
}

const MuonCollection TopPairEMuReferenceSelection::signalMuons(const EventPtr event) const {
	
	const MuonCollection allMuons(event->Muons());
	MuonCollection goodIsolatedMuons;
	
	for (unsigned int index = 0; index < allMuons.size(); ++index) {
		const MuonPointer muon(allMuons.at(index));
		if (isGoodMuon(muon) && isIsolatedMuon(muon)) {
			goodIsolatedMuons.push_back(muon);
		}
	}	
	return goodIsolatedMuons;

}


bool TopPairEMuReferenceSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {

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

bool TopPairEMuReferenceSelection::isBJet(const JetPointer jet) const {
	return jet->isBJet(BtagAlgorithm::CombinedSecondaryVertex, BtagAlgorithm::MEDIUM);
}


bool TopPairEMuReferenceSelection::passesSelectionStep(const EventPtr event, unsigned int selectionStep) const {
	TTbarEMuReferenceSelection::Step step = TTbarEMuReferenceSelection::Step(selectionStep);
	switch (step) {
	case TTbarEMuReferenceSelection::EventCleaningAndTrigger:
		return passesEventCleaning(event) && passesTriggerSelection(event);
	case TTbarEMuReferenceSelection::DiLeptonSelection:
		return passesDiLeptonSelection(event);
	case TTbarEMuReferenceSelection::ZmassVeto:
		return passesZmassVeto(event);
	case TTbarEMuReferenceSelection::AtLeastOneGoodJets:
		return hasAtLeastNGoodJets(event, 1);
	case TTbarEMuReferenceSelection::AtLeastTwoGoodJets:
		return hasAtLeastNGoodJets(event, 2);
	case TTbarEMuReferenceSelection::MetCut:
		return passesMetCut(event);
	case TTbarEMuReferenceSelection::AtLeastOneBtag:
		return hasAtLeastOneGoodBJet(event);
	case TTbarEMuReferenceSelection::AtLeastTwoBtags:
		return hasAtLeastTwoGoodBJets(event);
	case TTbarEMuReferenceSelection::AtLeastOnePhoton:
		return hasAtLeastOneGoodPhoton(event);
	case TTbarEMuReferenceSelection::JustOneGoodPhoton:
		return hasJustOneGoodPhoton(event);
	default:
		break;
	}

	return false;
}

bool TopPairEMuReferenceSelection::passesEventCleaning(const EventPtr event) const {
	bool passesAllFilters(!event->isBeamScraping());
	passesAllFilters = passesAllFilters && event->passesHBHENoiseFilter();
	passesAllFilters = passesAllFilters && event->passesCSCTightBeamHaloFilter();
	passesAllFilters = passesAllFilters && event->passesHCALLaserFilter();
	passesAllFilters = passesAllFilters && event->passesTrackingFailureFilter();
	if (Globals::NTupleVersion >= 9)
		passesAllFilters = passesAllFilters && event->passesECALDeadCellTPFilter();
	if ((Globals::energyInTeV == 8) and (Globals::NTupleVersion >= 10)) { //2012 data only, v10 ntuples
		passesAllFilters = passesAllFilters && event->passesEEBadSCFilter();
		passesAllFilters = passesAllFilters && event->passesECALLaserCorrFilter();
		passesAllFilters = passesAllFilters && event->passesTrackingPOGFilters();
	}

	return passesAllFilters;
}

bool TopPairEMuReferenceSelection::passesTriggerSelection(const EventPtr event) const {

		return event->HLT(HLTriggers::HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL) || event->HLT(HLTriggers::HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL);
}

bool TopPairEMuReferenceSelection::isIsolatedMuon(const LeptonPointer lepton) const {
	const MuonPointer muon(boost::static_pointer_cast<Muon>(lepton));

	return muon->pfRelativeIsolation(0.4, true) < 0.2;

}

bool TopPairEMuReferenceSelection::isIsolatedElectron(const LeptonPointer lepton) const {
	const ElectronPointer electron(boost::static_pointer_cast<Electron>(lepton));
	return electron->pfRelativeIsolationRhoCorrected() < 0.15;
}

bool TopPairEMuReferenceSelection::passesDiLeptonSelection(const EventPtr event) const {
	
	const ElectronCollection electrons(signalElectrons(event));
	const MuonCollection muons(signalMuons(event));	
	ElectronCollection electronColl;
	MuonCollection muonColl;

	
	double ptMax = 0;
	int storeIndexA = -1;
	int storeIndexB = -1;
	if(electrons.size() >= 1 && muons.size() >= 1){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
					const MuonPointer muon(muons.at(indexB));
					if((electron->charge() == -muon->charge()) && ((electron->pt()+muon->pt())>ptMax)){
						ptMax = electron->pt()+muon->pt();
						storeIndexA = indexA;
						storeIndexB = indexB;
					}
				}

		if(storeIndexA != storeIndexB){
		
			electronColl.push_back(electrons.at(storeIndexA));
			muonColl.push_back(muons.at(storeIndexB));	
		}

		}
	}

	ElectronPointer electron = electronColl.front();
	MuonPointer muon = muonColl.front();
	
	double mass = 0;
	
		ParticlePointer dilepton;
		dilepton = ParticlePointer(new Particle(*electron + *muon));
		mass = dilepton->mass();
	

	return mass > 20;

}

bool TopPairEMuReferenceSelection::passesZmassVeto(const EventPtr event) const {

	const ElectronCollection electrons(signalElectrons(event));
	const MuonCollection muons(signalMuons(event));
	ElectronCollection electronColl;
	MuonCollection muonColl;

	
	double ptMax = 0;
	int storeIndexA = -1;
	int storeIndexB = -1;
	if(electrons.size() >= 1 && muons.size() >= 1){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
					const MuonPointer muon(muons.at(indexB));
					if((electron->charge() == -muon->charge()) && ((electron->pt()+muon->pt())>ptMax)){
						ptMax = electron->pt()+muon->pt();
						storeIndexA = indexA;
						storeIndexB = indexB;
					}
				}

		if(storeIndexA != storeIndexB){
		
			electronColl.push_back(electrons.at(storeIndexA));
			muonColl.push_back(muons.at(storeIndexB));	
		}

		}
	}
	
	ElectronPointer electron = electronColl.front();
	MuonPointer muon = muonColl.front();
	
	double mass = 0;

 	ParticlePointer dilepton;
 	dilepton = ParticlePointer(new Particle(*electron + *muon));
 	mass = dilepton->mass();
	

	return mass < 76 || mass > 106;

}

bool TopPairEMuReferenceSelection::passesMetCut(const EventPtr event) const {

	const METPointer met(event->MET());

	return met->pt() > 40;

}

bool TopPairEMuReferenceSelection::hasAtLeastNGoodJets(const EventPtr event, int Njets) const {
	const JetCollection goodJets(cleanedJets(event));
	int nJetsAbove30GeV(0);

	for (unsigned int index = 0; index < goodJets.size(); ++index) {

		const JetPointer jet(goodJets.at(index));
		if (goodJets.at(index)->pt() > 30.)
			++nJetsAbove30GeV;
	}
	return nJetsAbove30GeV >= Njets;
}

bool TopPairEMuReferenceSelection::hasAtLeastOneGoodBJet(const EventPtr event) const {
	return cleanedBJets(event).size() > 0;
}

bool TopPairEMuReferenceSelection::hasAtLeastTwoGoodBJets(const EventPtr event) const {
	return cleanedBJets(event).size() > 1;
}

bool TopPairEMuReferenceSelection::hasAtLeastOneGoodPhoton(const EventPtr event) const {
	return signalPhotons(event).size() > 0;
}

bool TopPairEMuReferenceSelection::hasJustOneGoodPhoton(const EventPtr event) const {
	return signalPhotons(event).size() == 1;
}
const LeptonPointer TopPairEMuReferenceSelection::signalLepton(const EventPtr event) const {

	const ElectronCollection allElectrons(event->Electrons());
	ElectronCollection goodIsolatedElectrons;
	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		const ElectronPointer electron(allElectrons.at(index));
		if (isGoodElectron(electron)) {
			goodIsolatedElectrons.push_back(electron);
		}
	}

	return goodIsolatedElectrons.front();

}

/* const ElectronCollection TopPairEMuReferenceSelection::goodElectrons(const EventPtr event) const {

	const ElectronCollection allElectrons(event->Electrons());
	ElectronCollection goodIsolatedElectrons;
	for (unsigned int index = 0; index < allElectrons.size(); ++index) {
		const ElectronPointer electron(allElectrons.at(index));
		if (isGoodElectron(electron)) {
			goodIsolatedElectrons.push_back(electron);
		}
	}
	return goodIsolatedElectrons;
}
const MuonCollection TopPairEMuReferenceSelection::goodMuons(const EventPtr event) const {

	const MuonCollection allMuons(event->Muons());
	MuonCollection goodIsolatedMuons;
	for (unsigned int index = 0; index < allMuons.size(); ++index) {
		const MuonPointer muon(allMuons.at(index));
		if (isGoodMuon(muon)) {
			goodIsolatedMuons.push_back(muon);
		}
	}

	return goodIsolatedMuons;

}
 */
/* void signalLeptons(const EventPtr event) {

	
 	const ElectronCollection electrons(signalElectrons(event));
 	const MuonCollection muons(signalMuons(event));

	
	ElectronCollection electronColl;
	MuonCollection muonColl;

	double ptMax = 0;
	int storeIndexA = -1;
	int storeIndexB = -1;
	if(electrons.size() >= 1 && muons.size() >= 1){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
					const MuonPointer muon(muons.at(indexB));
					if((electron->charge() == -muon->charge()) && ((electron->pt()+muon->pt())>ptMax)){
						ptMax = electron->pt()+muon->pt();
						storeIndexA = indexA;
						storeIndexB = indexB;
					}
				}

		if(storeIndexA != storeIndexB){
		
			electronColl.push_back(electrons.at(storeIndexA));
			muonColl.push_back(muons.at(storeIndexB));	
		}

		}
	}
	
	ElectronPointer electron = electronColl.front();
	MuonPointer muon = muonColl.front();

} */

const PhotonCollection TopPairEMuReferenceSelection::signalPhotons(const EventPtr event) const {

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

const JetCollection TopPairEMuReferenceSelection::cleanedJets(const EventPtr event) const {
	const JetCollection jets(event->Jets());
	JetCollection cleanedJets;

	//if no signal lepton is found, can't clean jets, return them all!
	if (!passesDiLeptonSelection(event))
		return jets;

	const ElectronCollection electrons(signalElectrons(event));
	const MuonCollection muons(signalMuons(event));
	ElectronCollection electronColl;
	MuonCollection muonColl;
	
	double ptMax = 0;
	int storeIndexA = -1;
	int storeIndexB = -1;
	if(electrons.size() >= 1 && muons.size() >= 1){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
					const MuonPointer muon(muons.at(indexB));
					if((electron->charge() == -muon->charge()) && ((electron->pt()+muon->pt())>ptMax)){
						ptMax = electron->pt()+muon->pt();
						storeIndexA = indexA;
						storeIndexB = indexB;
					}
				}

		if(storeIndexA != storeIndexB){
		
			electronColl.push_back(electrons.at(storeIndexA));
			muonColl.push_back(muons.at(storeIndexB));	
		}

		}
	}

	ElectronPointer electron = electronColl.front();
	MuonPointer muon = muonColl.front();
	
	for (unsigned int index = 0; index < jets.size(); ++index) {
		const JetPointer jet(jets.at(index));
		if (!jet->isWithinDeltaR(0.3, electron) && !jet->isWithinDeltaR(0.3, muon) && isGoodJet(jet))
			cleanedJets.push_back(jet);
	}

	return cleanedJets;
}

const JetCollection TopPairEMuReferenceSelection::cleanedBJets(const EventPtr event) const {
	const JetCollection jets(cleanedJets(event));
	JetCollection cleanedBJets;

	for (unsigned int index = 0; index < jets.size(); ++index) {
		const JetPointer jet(jets.at(index));
		if (isBJet(jet))
			cleanedBJets.push_back(jet);
	}

	return cleanedBJets;

}

bool TopPairEMuReferenceSelection::isLooseMuon(const MuonPointer muon) const {
	bool passesPt = muon->pt() > 10;
	bool passesEta = fabs(muon->eta()) < 2.5;
	bool isPFMuon = muon->isPFMuon();
	bool isGlobalOrTracker = muon->isGlobal() || muon->isTracker();
	bool isLooselyIsolated = muon->pfRelativeIsolation(0.4, true) < 0.2;

	return isPFMuon && passesPt && passesEta && isGlobalOrTracker && isLooselyIsolated;
}

bool TopPairEMuReferenceSelection::isLooseElectron(const ElectronPointer electron) const {

	bool passesEtAndEta = electron->et() > 20. && fabs(electron->eta()) < 2.5;
	bool passesID(electron->passesElectronID(ElectronID::MVAIDTrigger));
	bool passesIso = electron->pfRelativeIsolationRhoCorrected() < 0.15;
	return passesEtAndEta && passesIso && passesID;
}

bool TopPairEMuReferenceSelection::isGoodElectron(const ElectronPointer electron) const {
	bool passesEtAndEta = electron->et() > 20 && fabs(electron->eta()) < 2.5 && !electron->isInCrack();
	bool passesD0 = fabs(electron->d0()) < 0.04; //cm
	bool passesID(electron->passesElectronID(ElectronID::MVAIDTrigger));
	bool passesIsolation  = isIsolatedElectron(electron);
	return passesEtAndEta && passesD0 && passesID && passesIsolation;
}

bool TopPairEMuReferenceSelection::isGoodMuon(const MuonPointer muon) const {
	bool passesEtAndEta = muon->pt() > 20 && fabs(muon->eta()) < 2.4;
	bool passesID = (muon->isGlobal() || muon->isTracker()) && muon->isPFMuon();
    	bool passesIsolation  = isIsolatedMuon(muon);

	return passesEtAndEta && passesID && passesIsolation;
}


} /* namespace BAT */
