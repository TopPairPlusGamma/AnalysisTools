
/*
 * TopPairMuMuReferenceSelection.cpp
 *
 *  Created on: 28 May 2013
 *      Author: N.Berry/P.Symonds
 */

#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/HighLevelTriggers.h"

using namespace std;

namespace BAT {

TopPairMuMuReferenceSelection::TopPairMuMuReferenceSelection(unsigned int numberOfSelectionSteps) : //
		BasicSelection(numberOfSelectionSteps) //
{

}

TopPairMuMuReferenceSelection::~TopPairMuMuReferenceSelection() {
}


bool TopPairMuMuReferenceSelection::isGoodJet(const JetPointer jet) const {

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

const LeptonPointer TopPairMuMuReferenceSelection::signalLepton(const EventPtr event) const {

	const MuonCollection allMuons(event->Muons());
	MuonCollection goodIsolatedMuons;
	for (unsigned int index = 0; index < allMuons.size(); ++index) {
		const MuonPointer muon(allMuons.at(index));
		if (isGoodMuon(muon) && isIsolated(muon)) {
			goodIsolatedMuons.push_back(muon);
		}
	}
	

	return goodIsolatedMuons.front();

}



bool TopPairMuMuReferenceSelection::isNminusOnePhoton(const PhotonPointer photon, const EventPtr event, TString cut) const {

	const MuonCollection muons(goodMuons(event));
	const JetCollection jets(event->Jets());

	bool passesEtAndEta = photon->et() > 25 && fabs(photon->eta()) < 1.4442 && !photon->isInCrack(); // 2.5
	bool passesSafeElectronVeto = photon->ConversionSafeElectronVeto();
	bool passesHOverE = photon->SingleTowerHoE() < 0.05; // same for EE and EB
	
	bool passesShowerShape = false;
//	bool passesPFChargedIso = false;
	bool passesPFNeutralIso = false;
	bool passesPFPhotonIso = false;
	bool passesphoSCChIso = false;

	bool backgroundShape = false;
//	backgroundShape = photon->sigmaIEtaIEta() > 0.012 && photon->sigmaIEtaIEta() < 0.029;
	
	if (photon->isInBarrelRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.012;
//		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.6;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 3.5 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.3 + 0.005 * photon->pt();
		passesphoSCChIso = photon->RhoCorrectedSCChIso(event->rho()) < 5;

		backgroundShape = photon->sigmaIEtaIEta() > 0.012 && photon->sigmaIEtaIEta() < 0.029;
		
	} else if (photon->isInEndCapRegion()) {
		passesShowerShape = photon->sigmaIEtaIEta() < 0.034;
//		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.3;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 2.9 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.5 + 0.005 * photon->pt();
		passesphoSCChIso = photon->RhoCorrectedSCChIso(event->rho()) < 20;

		backgroundShape = photon->sigmaIEtaIEta() > 0.012 && photon->sigmaIEtaIEta() < 0.029;
	}

	
	bool passesDeltaRgammaMuons = false;

	 for (unsigned int index = 0; index < muons.size(); ++index) {
	 			const MuonPointer muon(muons.at(index));
	 			passesDeltaRgammaMuons = photon->deltaR(muon) > 0.7;
				
				if(photon->deltaR(muon) < 0.7)
				break;
	}

	bool passesDeltaRgammaJets = false;
	
	for (unsigned int index = 0; index < jets.size(); ++index) { 
			const JetPointer jet(jets.at(index));
			passesDeltaRgammaJets = photon->deltaR(jet) > 0.7;
	}
	
	bool passesDeltaRjetsMuons = false;

	 for (unsigned int index = 0; index < muons.size(); ++index) {
	 		const MuonPointer muon(muons.at(index));
			for(unsigned int jindex = 0; jindex<jets.size(); ++jindex){
				const JetPointer jet(jets[jindex]);
	 			passesDeltaRjetsMuons = muon->deltaR(jet) > 0.5;

			}
	}

		if(cut == "passesEtAndEta")
			return passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso && passesphoSCChIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons;
		else if(cut == "passesHOverE")
			return passesEtAndEta && passesSafeElectronVeto && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso && passesphoSCChIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons;
		else if(cut == "passesShowerShape")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesPFNeutralIso && passesPFPhotonIso && passesphoSCChIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons;
		else if(cut == "passesPFNeutralIso")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFPhotonIso && passesphoSCChIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons;
		else if(cut == "passesPFPhotonIso")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesphoSCChIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons;
		else if(cut == "passesphoSCChIso")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesPFNeutralIso && passesPFPhotonIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons && backgroundShape;
		else if(cut == "passesDeltaRgammaMuons")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso &&
			passesphoSCChIso && passesDeltaRgammaJets && passesDeltaRjetsMuons;
		else if(cut == "passesDeltaRgammaJets")	
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso &&
			passesDeltaRgammaMuons && passesphoSCChIso && passesDeltaRjetsMuons;
		else if(cut == "passesDeltaRjetsMuons")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso &&
			passesDeltaRgammaMuons && passesDeltaRgammaJets && passesphoSCChIso;	
		else if(cut == "backgroundShape")
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesPFNeutralIso && passesPFPhotonIso && passesDeltaRgammaMuons &&
			passesDeltaRgammaJets && passesDeltaRjetsMuons && backgroundShape;
		else	
			return passesEtAndEta && passesSafeElectronVeto && passesHOverE && passesShowerShape && passesPFNeutralIso && passesPFPhotonIso &&
			passesphoSCChIso && passesDeltaRgammaMuons && passesDeltaRgammaJets && passesDeltaRjetsMuons;



}

bool TopPairMuMuReferenceSelection::isGoodPhoton(const PhotonPointer photon, const EventPtr event) const {

	const MuonCollection muons(goodMuons(event));
	const JetCollection jets(event->Jets());

	bool passesEtAndEta = photon->et() > 25 && fabs(photon->eta()) < 1.4442 && !photon->isInCrack();
	bool passesSafeElectronVeto = photon->ConversionSafeElectronVeto();
	bool passesHOverE = photon->SingleTowerHoE() < 0.05; // same for EE and EB
	
//	bool passesShowerShape = false;
//	bool passesPFChargedIso = false;
	bool passesPFNeutralIso = false;
	bool passesPFPhotonIso = false;
	bool passesphoSCChIso = false;
//	bool passesphoSCNuIso = false;
//	bool passesphoSCPhIso = false;
	
	if (photon->isInBarrelRegion()) {
//		passesShowerShape = photon->sigmaIEtaIEta() < 0.012;
//		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.6;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 7.5 + 0.04 * photon->pt(); //3.5
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 5 + 0.005 * photon->pt(); //1.3
		passesphoSCChIso = photon->RhoCorrectedSCChIso(event->rho()) < 20;
//		passesphoSCNuIso = photon->RhoCorrectedSCNuIso(event->rho()) < 3.5 + 0.04 * photon->pt();
//		passesphoSCPhIso = photon->RhoCorrectedSCPhIso(event->rho()) < 1.3 + 0.005 * photon->pt();
	} else if (photon->isInEndCapRegion()) {
//		passesShowerShape = photon->sigmaIEtaIEta() < 0.034;
//		passesPFChargedIso = photon->RhoCorrectedPFChargedHadronIso(event->rho()) < 2.3;
		passesPFNeutralIso = photon->RhoCorrectedPFNeutralHadronIso(event->rho()) < 2.9 + 0.04 * photon->pt();
		passesPFPhotonIso = photon->RhoCorrectedPFPhotonIso(event->rho()) < 1.5 + 0.005 * photon->pt();
		passesphoSCChIso = photon->RhoCorrectedSCChIso(event->rho()) < 20;
//		passesphoSCNuIso = photon->RhoCorrectedSCNuIso(event->rho()) < 2.9 + 0.04 * photon->pt();
//		passesphoSCPhIso = photon->RhoCorrectedSCPhIso(event->rho()) < 1.5 + 0.005 * photon->pt();
	}

	bool passesDeltaRgammaMuons = false;

	 	for (unsigned int index = 0; index < muons.size(); ++index) {
	 			const MuonPointer muon(muons.at(index));
	 			passesDeltaRgammaMuons = photon->deltaR(muon) > 0.3;
				
				if(photon->deltaR(muon) < 0.3)
				break;
	}

	bool passesDeltaRgammaJets = false;
	
	for (unsigned int index = 0; index < jets.size(); ++index) { 
			const JetPointer jet(jets.at(index));
			passesDeltaRgammaJets = photon->deltaR(jet) > 0.3;
	}
	
	bool passesDeltaRjetsMuons = false;

	 for (unsigned int index = 0; index < muons.size(); ++index) {
	 		const MuonPointer muon(muons.at(index));
			for(unsigned int jindex = 0; jindex<jets.size(); ++jindex){
				const JetPointer jet(jets[jindex]);
	 			passesDeltaRjetsMuons = muon->deltaR(jet) > 0.3;
			}	

	}
	
	return passesEtAndEta && passesSafeElectronVeto && passesHOverE /*&& passesShowerShape*/  && passesPFNeutralIso && passesPFPhotonIso && passesphoSCChIso &&
	passesDeltaRgammaJets && passesDeltaRgammaMuons && passesDeltaRjetsMuons; 
}

bool TopPairMuMuReferenceSelection::isBJet(const JetPointer jet) const {
	return jet->isBJet(BtagAlgorithm::CombinedSecondaryVertex, BtagAlgorithm::MEDIUM);
}

//adapted for dilepton channel
bool TopPairMuMuReferenceSelection::isGoodMuon(const MuonPointer muon) const {
	bool passesEtAndEta = muon->pt() > 20 && fabs(muon->eta()) < 2.4;
	bool passesID = (muon->isGlobal() || muon->isTracker()) && muon->isPFMuon();
    bool passesIsolation  = isIsolated(muon);

	return passesEtAndEta && passesID && passesIsolation;
}

bool TopPairMuMuReferenceSelection::passesSelectionStep(const EventPtr event, unsigned int selectionStep) const {
	TTbarMuMuReferenceSelection::Step step = TTbarMuMuReferenceSelection::Step(selectionStep);
	switch (step) {
	case TTbarMuMuReferenceSelection::EventCleaningAndTrigger:
		return passesEventCleaning(event) && passesTriggerSelection(event);
	case TTbarMuMuReferenceSelection::DiMuonSelection:
		return passesDiMuonSelection(event);
	case TTbarMuMuReferenceSelection::ZmassVeto:
		return passesZmassVeto(event);
	case TTbarMuMuReferenceSelection::AtLeastOneGoodJets:
		return hasAtLeastNGoodJets(event, 1);
	case TTbarMuMuReferenceSelection::AtLeastTwoGoodJets:
		return hasAtLeastNGoodJets(event, 2);
	case TTbarMuMuReferenceSelection::MetCut:
		return passesMetCut(event);
	case TTbarMuMuReferenceSelection::AtLeastOneBtag:
		return hasAtLeastOneGoodBJet(event);
//	case TTbarMuMuReferenceSelection::AtLeastTwoBtags:
//		return hasAtLeastTwoGoodBJets(event);
	case TTbarMuMuReferenceSelection::AtLeastOnePhotonPreSelection:
		return hasAtLeastOnePhotonPreSelection(event);
	case TTbarMuMuReferenceSelection::AtLeastOnePhotonPostSelection:
		return hasAtLeastOneGoodPhotonPostSelection(event);
	case TTbarMuMuReferenceSelection::JustOneGoodPhotonPostSelection:
		return hasJustOneGoodPhotonPostSelection(event);
	default:
		break;
	}

	return false;
}

bool TopPairMuMuReferenceSelection::passesEventCleaning(const EventPtr event) const {
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

bool TopPairMuMuReferenceSelection::passesTriggerSelection(const EventPtr event) const {

		return event->HLT(HLTriggers::HLT_Mu17_Mu8);
}

bool TopPairMuMuReferenceSelection::isIsolated(const LeptonPointer lepton) const {
	const MuonPointer muon(boost::static_pointer_cast<Muon>(lepton));

	return muon->pfRelativeIsolation(0.4, true) < 0.2;

}

bool TopPairMuMuReferenceSelection::passesDiMuonSelection(const EventPtr event) const {
	const MuonCollection muons(signalMuons(event));

	double mass = 0;

	if(muons.size()>1){
		const MuonPointer muon(muons.at(0));
		const MuonPointer muon2(muons.at(1));

		ParticlePointer dilepton;
		dilepton = ParticlePointer(new Particle(*muon + *muon2));
		mass = dilepton->mass();
	}

	return mass > 20;

}

bool TopPairMuMuReferenceSelection::passesZmassVeto(const EventPtr event) const {
	const MuonCollection muons(signalMuons(event));

	double mass = 0;

	if(muons.size()>1){
		const MuonPointer muon(muons.at(0));
		const MuonPointer muon2(muons.at(1));

		ParticlePointer dilepton;
		dilepton = ParticlePointer(new Particle(*muon + *muon2));
		mass = dilepton->mass();
	}

	return mass < 76 || mass > 106;

}

bool TopPairMuMuReferenceSelection::passesMetCut(const EventPtr event) const {

	const METPointer met(event->MET());

	return met->pt() > 40;

}

bool TopPairMuMuReferenceSelection::hasAtLeastNGoodJets(const EventPtr event, int Njets) const {
	const JetCollection goodJets(cleanedJets(event));
	int nJetsAbove30GeV(0);

	for (unsigned int index = 0; index < goodJets.size(); ++index) {

		const JetPointer jet(goodJets.at(index));
		if (goodJets.at(index)->pt() > 30.)
			++nJetsAbove30GeV;
	}
	return nJetsAbove30GeV >= Njets;
}

bool TopPairMuMuReferenceSelection::hasAtLeastOneGoodBJet(const EventPtr event) const {
	return cleanedBJets(event).size() > 0;
}

// bool TopPairMuMuReferenceSelection::hasAtLeastTwoGoodBJets(const EventPtr event) const {
// 	return cleanedBJets(event).size() > 1;
// }
	
bool TopPairMuMuReferenceSelection::hasAtLeastOnePhotonPreSelection(const EventPtr event) const {
	return AllPhotonsPreSelection(event).size() > 0;
}	
	
bool TopPairMuMuReferenceSelection::hasAtLeastOneGoodPhotonPostSelection(const EventPtr event) const {
	return signalPhotons(event).size() > 0;
}

bool TopPairMuMuReferenceSelection::hasJustOneGoodPhotonPostSelection(const EventPtr event) const {
	return signalPhotons(event).size() == 1;
}

const ElectronCollection TopPairMuMuReferenceSelection::goodElectrons(const EventPtr event) const {

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

const MuonCollection TopPairMuMuReferenceSelection::goodMuons(const EventPtr event) const {

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

const MuonCollection TopPairMuMuReferenceSelection::signalMuons(const EventPtr event) const {

	const MuonCollection muons(goodMuons(event));
	MuonCollection signalMuons;

	double ptMax = 0;
	int storeIndexA = -1;
	int storeIndexB = -1;
	if(muons.size() >= 2){
		for (unsigned int indexA = 0; indexA < muons.size(); ++indexA) {
		const MuonPointer muon(muons.at(indexA));
				for (unsigned int indexB = 0; indexB < muons.size(); ++indexB) {
				
					if(indexA == indexB)
						continue;
						
					const MuonPointer muon2(muons.at(indexB));
					
					//if((muon2->charge() == -muon->charge()) && ((muon->pt()+muon2->pt())>ptMax)){
						//ptMax = muon->pt()+muon2->pt();
						//storeIndexA = indexA;
						//storeIndexB = indexB;
					
					if((muon2->charge()*muon->charge() < 0) && ((muon->pt()+muon2->pt())>ptMax)){
						ptMax = muon->pt()+muon2->pt();
						storeIndexA = indexA;
						storeIndexB = indexB;
					}
				}

		}


    	if(storeIndexA != storeIndexB){
			signalMuons.push_back(muons.at(storeIndexA));
			signalMuons.push_back(muons.at(storeIndexB));
	}


	}
	
	

	
	return signalMuons;

}



const ElectronCollection TopPairMuMuReferenceSelection::signalElectrons(const EventPtr event) const {

	const ElectronCollection electrons(goodElectrons(event));
	ElectronCollection signalElectrons;

	double ptMax = 0;
	int storeIndexA = -1;
	int storeIndexB = -1;
	if(electrons.size() >= 2){
		for (unsigned int indexA = 0; indexA < electrons.size(); ++indexA) {
		const ElectronPointer electron(electrons.at(indexA));
				for (unsigned int indexB = 0; indexB < electrons.size(); ++indexB) {
				
					if(indexA == indexB)
						continue;
						
					const ElectronPointer electron2(electrons.at(indexB));
					
				//	if((electron2->charge() == -electron->charge()) && ((electron->pt()+electron2->pt())>ptMax)){
					//	ptMax = electron->pt()+electron2->pt();
					//	storeIndexA = indexA;
					//	storeIndexB = indexB;
						
					if((electron2->charge()*electron->charge() < 0) && ((electron->pt()+electron2->pt())>ptMax)){
						ptMax = electron->pt()+electron2->pt();
						storeIndexA = indexA;
						storeIndexB = indexB;
					}
			
				}

		}

		if(storeIndexA != storeIndexB){
			signalElectrons.push_back(electrons.at(storeIndexA));
			signalElectrons.push_back(electrons.at(storeIndexB));
		}

	}

	return signalElectrons;

}

const PhotonCollection TopPairMuMuReferenceSelection::signalPhotons(const EventPtr event) const {

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

const PhotonCollection TopPairMuMuReferenceSelection::nMinusOnePhotons(const EventPtr event, TString cut) const {

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

const PhotonCollection TopPairMuMuReferenceSelection::AllPhotonsPreSelection(const EventPtr event) const {
	
	const PhotonCollection allPhotons(event->Photons());
	PhotonCollection AllPhotonsPreSelection;
	for (unsigned int index = 0; index < allPhotons.size(); ++index) {
		const PhotonPointer photon(allPhotons.at(index));
		AllPhotonsPreSelection.push_back(photon);
	}
	
	return AllPhotonsPreSelection; 
}

const JetCollection TopPairMuMuReferenceSelection::cleanedJets(const EventPtr event) const {
	const JetCollection jets(event->Jets());
	JetCollection cleanedJets;

	//if no signal lepton is found, can't clean jets, return them all!
	if (!passesDiMuonSelection(event))
		return jets;

	const MuonCollection muons(signalMuons(event));
	const PhotonCollection photons(signalPhotons(event));

	double minDR = 999999999.;
	double minDR_pho = 999999999.;

	for (unsigned int index = 0; index < jets.size(); ++index) {
		const JetPointer jet(jets.at(index));
		for (unsigned int lep = 0; lep < muons.size(); lep++){
			const MuonPointer lepton(muons.at(lep));
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

const JetCollection TopPairMuMuReferenceSelection::cleanedBJets(const EventPtr event) const {
	const JetCollection jets(cleanedJets(event));
	JetCollection cleanedBJets;

	for (unsigned int index = 0; index < jets.size(); ++index) {
		const JetPointer jet(jets.at(index));
		if (isBJet(jet))
			cleanedBJets.push_back(jet);
	}

	return cleanedBJets;

}

bool TopPairMuMuReferenceSelection::isLooseMuon(const MuonPointer muon) const {
	bool passesPt = muon->pt() > 10;
	bool passesEta = fabs(muon->eta()) < 2.5;
	bool isPFMuon = muon->isPFMuon();
	bool isGlobalOrTracker = muon->isGlobal() || muon->isTracker();
	bool isLooselyIsolated = muon->pfRelativeIsolation(0.4, true) < 0.2;

	return isPFMuon && passesPt && passesEta && isGlobalOrTracker && isLooselyIsolated;
}

bool TopPairMuMuReferenceSelection::isLooseElectron(const ElectronPointer electron) const {

	bool passesEtAndEta = electron->et() > 20. && fabs(electron->eta()) < 2.5;
	bool passesID(electron->passesElectronID(ElectronID::MVAIDTrigger));
	bool passesIso = electron->pfRelativeIsolationRhoCorrected() < 0.15;
	return passesEtAndEta && passesIso && passesID;
}

bool TopPairMuMuReferenceSelection::isGoodElectron(const ElectronPointer electron) const {
	bool passesEtAndEta = electron->et() > 30 && fabs(electron->eta()) < 2.5 && !electron->isInCrack();
	bool passesD0 = fabs(electron->d0()) < 0.02; //cm
	bool passesHOverE = electron->HadOverEm() < 0.05; // same for EE and EB
	bool passesID(electron->passesElectronID(ElectronID::MVAIDTrigger));
	return passesEtAndEta && passesD0 &&
			passesHOverE && passesID;
}
} /* namespace BAT */
