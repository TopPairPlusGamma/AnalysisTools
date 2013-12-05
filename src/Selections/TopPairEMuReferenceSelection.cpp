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

const ElectronCollection TopPairEMuReferenceSelection::goodElectrons(const EventPtr event) const {

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


bool TopPairEMuReferenceSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {
	
	bool passesEtAndEta = photon->et() > 25 && fabs(photon->eta()) < 2.5 && !photon->isInCrack();
	bool passesSafeElectronVeto = photon->ConversionSafeElectronVeto();
	bool passesHOverE = photon->SingleTowerHoE() < 0.05; // same for EE and EB
	
	bool passesShowerShape = false;
	bool passesPFChargedIso = false;
	bool passesPFNeutralIso = false;
	bool passesPFPhotonIso = false;
	
	if (photon->isInBarrelRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.012;
		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.6;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 3.5 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.3 + 0.005 * photon->pt();
	} else if (photon->isInEndCapRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.034;
		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.3;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 2.9 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.5 + 0.005 * photon->pt();
	}
	
	const ElectronCollection electrons(goodElectrons(event));
	const MuonCollection muons(goodMuons(event));

	   bool passesDeltaRgammaMuons = false;

	 	for (unsigned int index = 0; index < muons.size(); ++index) {
	 			const MuonPointer muon(muons.at(index));
	 			passesDeltaRgammaMuons = photon->deltaR(muon) > 0.5;
				
				if(photon->deltaR(muon) < 0.5)
				break;
	 	}

	 	bool passesDeltaRgammaElectrons = false;

	 	 	for (unsigned int index = 0; index < electrons.size(); ++index) {
	 	 		const ElectronPointer electron(electrons.at(index));
	 	 		passesDeltaRgammaElectrons = photon->deltaR(electron) > 0.5;
					
				if(photon->deltaR(electron) < 0.5)
				break;	
	  	}


	return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape  && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;
}

bool TopPairEMuReferenceSelection::isNminusOnePhoton(const PhotonPointer photon, const EventPtr event, TString cut) const {

	const ElectronCollection electrons(goodElectrons(event));
	const MuonCollection muons(goodMuons(event));
	const JetCollection jets(event->Jets());

	bool passesEtAndEta = photon->et() > 25 && fabs(photon->eta()) < 2.5 && !photon->isInCrack();
	bool passesSafeElectronVeto = photon->ConversionSafeElectronVeto();
	bool passesHOverE = photon->SingleTowerHoE() < 0.05; // same for EE and EB
	
	bool passesShowerShape = false;
	bool passesPFChargedIso = false;
	bool passesPFNeutralIso = false;
	bool passesPFPhotonIso = false;
	
	if (photon->isInBarrelRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.012;
		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.6;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 3.5 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.3 + 0.005 * photon->pt();
	} else if (photon->isInEndCapRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.034;
		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.3;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 2.9 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.5 + 0.005 * photon->pt();
	}

	  bool passesDeltaRgammaMuons = false;

	 	for (unsigned int index = 0; index < muons.size(); ++index) {
	 			const MuonPointer muon(muons.at(index));
	 			passesDeltaRgammaMuons = photon->deltaR(muon) > 0.5;
				
				if(photon->deltaR(muon) < 0.5)
				break;
	 	}

	 	bool passesDeltaRgammaElectrons = false;

	 	 	for (unsigned int index = 0; index < electrons.size(); ++index) {
	 	 		const ElectronPointer electron(electrons.at(index));
	 	 		passesDeltaRgammaElectrons = photon->deltaR(electron) > 0.5;
					
				if(photon->deltaR(electron) < 0.5)
				break;
	  	}

	//
	// 	bool passesDeltaRgammaJets = false;
	//
	// 	for (unsigned int index = 0; index < jets.size(); ++index) {
	// 			const JetPointer jet(jets.at(index));
	// 			passesDeltaRgammaJets = photon->deltaR(jet) > 0.7;
	// 	}

		if(cut == "passesEtAndEta")
			return passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons; // && passesDeltaRgammaMuons && passesDeltaRgammaJets;
		else if(cut == "passesHOverE")
			return passesEtAndEta && passesSafeElectronVeto && passesShowerShape && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;
		else if(cut == "passesShowerShape")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;
		else if(cut == "passesPFChargedIso")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;
		else if(cut == "passesPFNeutralIso")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFChargedIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;
		else if(cut == "passesPFPhotonIso")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFChargedIso && passesPFNeutralIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;
		else if(cut == "passesDeltaRgammaElectrons")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons;
		else if(cut == "passesDeltaRgammaMuons")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaElectrons;
		else
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFChargedIso && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons && passesDeltaRgammaElectrons;



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
	case TTbarEMuReferenceSelection::AtLeastOneGoodJets:
		return hasAtLeastNGoodJets(event, 1);
	case TTbarEMuReferenceSelection::AtLeastTwoGoodJets:
		return hasAtLeastNGoodJets(event, 2);
	case TTbarEMuReferenceSelection::AtLeastOneBtag:
		return hasAtLeastOneGoodBJet(event);
	case TTbarEMuReferenceSelection::AtLeastOnePhotonPreSelection:
		return hasAtLeastOnePhotonPreSelection(event);
	case TTbarEMuReferenceSelection::AtLeastOnePhotonPostSelection:
		return hasAtLeastOneGoodPhotonPostSelection(event);
	case TTbarEMuReferenceSelection::JustOneGoodPhotonPostSelection:
		return hasJustOneGoodPhotonPostSelection(event);
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

const MuonCollection TopPairEMuReferenceSelection::signalMuons(const EventPtr event) const {

	const MuonCollection muons(goodMuons(event));
	const ElectronCollection electrons(goodElectrons(event));

	//save these
	MuonCollection signalMuons;


	double ptMax = 0;
	int storeIndexB = -1;

//  cout << "loop for max pt, muons: " << muons.size() << "electrons: " << electrons.size() << endl;
	if(electrons.size() >= 1 && muons.size() >= 1){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
					const MuonPointer muon(muons.at(indexB));
					if((electron->charge()*muon->charge() < 0) && ((electron->pt()+muon->pt())>ptMax)){
						ptMax = electron->pt()+muon->pt();
						storeIndexB = indexB;
					}
				}
	}
	
	if(storeIndexB != -1)
    		signalMuons.push_back(muons.at(storeIndexB));

	}

	return signalMuons;

}

const ElectronCollection TopPairEMuReferenceSelection::signalElectrons(const EventPtr event) const {

	const MuonCollection muons(goodMuons(event));
	const ElectronCollection electrons(goodElectrons(event));
	ElectronCollection signalElectrons;


	double ptMax = 0;
	int storeIndexA = -1;

//	    cout << "loop for max pt, muons: " << muons.size() << "electrons: " << electrons.size() << endl;
	if(electrons.size() >= 1 && muons.size() >= 1){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
					const MuonPointer muon(muons.at(indexB));
					if((electron->charge()*muon->charge() < 0) && ((electron->pt()+muon->pt())>ptMax)){
						ptMax = electron->pt()+muon->pt();
						storeIndexA = indexA;
					}
				}
	}
	
	if(storeIndexA != -1)
    		signalElectrons.push_back(electrons.at(storeIndexA));

	}

	return signalElectrons;

}


bool TopPairEMuReferenceSelection::passesDiLeptonSelection(const EventPtr event) const {
	
	const ElectronCollection electrons(signalElectrons(event));
	const MuonCollection muons(signalMuons(event));	


	double mass = 0;
	
	if(electrons.size() > 0 && muons.size() > 0){
	    ElectronPointer electron = electrons.front();
	    MuonPointer muon = muons.front();
	
		ParticlePointer dilepton;
		dilepton = ParticlePointer(new Particle(*electron + *muon));
		mass = dilepton->mass();
	}

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

// bool TopPairEMuReferenceSelection::hasAtLeastTwoGoodBJets(const EventPtr event) const {
// 	return cleanedBJets(event).size() > 1;
// }

bool TopPairEMuReferenceSelection::hasAtLeastOnePhotonPreSelection(const EventPtr event) const {
	return AllPhotonsPreSelection(event).size() > 0;
}

bool TopPairEMuReferenceSelection::hasAtLeastOneGoodPhotonPostSelection(const EventPtr event) const {
	return signalPhotons(event).size() > 0;
}

bool TopPairEMuReferenceSelection::hasJustOneGoodPhotonPostSelection(const EventPtr event) const {
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

const PhotonCollection TopPairEMuReferenceSelection::nMinusOnePhotons(const EventPtr event, TString cut) const {

	const PhotonCollection allPhotons(event->Photons());
	PhotonCollection nMinusOnePhotons;
	for (unsigned int index = 0; index < allPhotons.size(); ++index) {
		const PhotonPointer photon(allPhotons.at(index));
		if (isNminusOnePhoton(photon, event, cut)){
			nMinusOnePhotons.push_back(photon);
		}
	}

	return nMinusOnePhotons;

}

const PhotonCollection TopPairEMuReferenceSelection::AllPhotonsPreSelection(const EventPtr event) const {
	
	const PhotonCollection allPhotons(event->Photons());
	PhotonCollection AllPhotonsPreSelection;
	for (unsigned int index = 0; index < allPhotons.size(); ++index) {
		const PhotonPointer photon(allPhotons.at(index));
		AllPhotonsPreSelection.push_back(photon);
	}
	
	return AllPhotonsPreSelection; 
}

const JetCollection TopPairEMuReferenceSelection::cleanedJets(const EventPtr event) const {
	const JetCollection jets(event->Jets());
	JetCollection cleanedJets;

	//if no signal lepton is found, can't clean jets, return them all!
	if (!passesDiLeptonSelection(event))
		return jets;

	const PhotonCollection photons(signalPhotons(event));
	const ElectronCollection electrons(signalElectrons(event));
	const MuonCollection muons(signalMuons(event));


	double minDR = 999999999.;
	double minDR_pho = 999999999.;

	for (unsigned int index = 0; index < jets.size(); ++index) {
		const JetPointer jet(jets.at(index));
		for (unsigned int lep = 0; lep < electrons.size(); lep++){
			const LeptonPointer lepton(electrons.at(lep));
			if(jet->deltaR(lepton) < minDR)
				minDR = jet->deltaR(lepton);
		}
		for (unsigned int lep = 0; lep < muons.size(); lep++){
			const LeptonPointer lepton(muons.at(lep));
			if(jet->deltaR(lepton) < minDR)
				minDR = jet->deltaR(lepton);
		}
		for (unsigned int pho = 0; pho < photons.size(); pho++){
					const PhotonPointer photon(photons.at(pho));
					if(jet->deltaR(photon) < minDR_pho)
						minDR_pho = jet->deltaR(photon);
		}

		if (minDR > 0.5 && minDR_pho > 0.3 && isGoodJet(jet))
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
	bool passesEtAndEta = electron->et() > 20 && fabs(electron->eta()) < 2.5;
	bool passesD0 = fabs(electron->d0()) < 0.04; //cm
	bool passesID(electron->passesElectronID(ElectronID::MVAIDTrigger));
	bool passesIsolation  = isIsolatedElectron(electron);
	bool passesConvVeto = electron->passConversionVeto();
	return passesEtAndEta && passesD0 && passesID && passesIsolation && passesConvVeto;
}

bool TopPairEMuReferenceSelection::isGoodMuon(const MuonPointer muon) const {
	bool passesEtAndEta = muon->pt() > 20 && fabs(muon->eta()) < 2.4;
	bool passesID = (muon->isGlobal() || muon->isTracker()) && muon->isPFMuon();
    bool passesIsolation  = isIsolatedMuon(muon);

	return passesEtAndEta && passesID && passesIsolation;
}


} /* namespace BAT */
