/*
 * PhotonAnalyser.cpp
 *
 *  Created on: 26 April 2013
 *      Author: N.Berry
*/
#include "../../interface/Analysers/PhotonAnalyser.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"
#include "../../interface/Selections/BasicSelection.h"

namespace BAT {

void PhotonAnalyser::analyse(const EventPtr event, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons){

	//all photons
	analyse(event);
	//signal photons
	analyse_signalPhotons(event, signalPhotons, cleanJets, signalElectrons, signalMuons);

}

void PhotonAnalyser::analyse(const EventPtr event){

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/AllPhotons");

	//const ElectronCollection electrons = topEERefSelection_->goodElectrons(event);
	//const MuonCollection muons = topMuMuRefSelection_->goodMuons(event);

	weight_ = event->weight() * prescale_ * scale_;
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
	const PhotonCollection photons = event->Photons();
	const MuonCollection muons = event->Muons();

	histMan_->H1D_BJetBinned("Number_Of_Photons")->Fill(photons.size(), weight_);

	for (unsigned int index = 0; index < photons.size(); ++index) {
		const PhotonPointer photon(photons.at(index));
		histMan_->H1D_BJetBinned("Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("Photon_Phi")->Fill(photon->phi(), weight_);
		histMan_->H1D_BJetBinned("Photon_ET")->Fill(photon->et(), weight_);
		
		if (photon->isInEndCapRegion()){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_endcap")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->RhoCorrectedPFChargedHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->RhoCorrectedPFNeutralHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->RhoCorrectedPFPhotonIso(event->rho()), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->RhoCorrectedPFChargedHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->RhoCorrectedPFNeutralHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->RhoCorrectedPFPhotonIso(event->rho()), weight_);
		}
			
		histMan_->H1D_BJetBinned("Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("Photon_EcalIso")->Fill(photon->ecalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso")->Fill(photon->hcalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso2012")->Fill(photon->hcalIsolation2012(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrckIso")->Fill(photon->trackerIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCeta")->Fill(photon->superClusterEta(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCphi")->Fill(photon->superClusterPhi(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCenergy")->Fill(photon->superClusterEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCSeedEnergy")->Fill(photon->superClusterSeedEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_E3x3")->Fill(photon->Ecal3x3Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_E5x5")->Fill(photon->Ecal5x5Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrkVeto")->Fill(photon->TrackVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_ConvSEVeto")->Fill(photon->ConversionSafeElectronVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_HtowoE")->Fill(photon->SingleTowerHoE(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso")->Fill(photon->PFChargedHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso")->Fill(photon->PFNeutralHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFPhotonIso")->Fill(photon->PFPhotonIso(), weight_);
		
		for (unsigned int index = 0; index < jets.size(); ++index) { 
			const JetPointer jet(jets.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_jets")->Fill(photon->deltaR(jet), weight_);
		}
		
		for (unsigned int index = 0; index < electrons.size(); ++index) { 
			const ElectronPointer electron(electrons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_electrons")->Fill(photon->deltaR(electron), weight_);
		}
	
		for (unsigned int index = 0; index < muons.size(); ++index) { 
			const MuonPointer muon(muons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_muons")->Fill(photon->deltaR(muon), weight_);
		}
	}

}

void PhotonAnalyser::analyse_signalPhotons(const EventPtr event, PhotonCollection signalPhotons, JetCollection jets, ElectronCollection electrons, MuonCollection muons){

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/SignalPhotons");

	//const ElectronCollection electrons = topMuMuRefSelection_->goodElectrons(event);
	//const MuonCollection muons = topMuMuRefSelection_->goodMuons(event);

	weight_ = event->weight() * prescale_ * scale_;
//	const JetCollection jets = event->Jets();
//	const ElectronCollection electrons = event->Electrons();
//	const MuonCollection muons = event->Muons();

	histMan_->H1D_BJetBinned("Number_Of_Photons")->Fill(signalPhotons.size(), weight_);

	for (unsigned int index = 0; index < signalPhotons.size(); ++index) {
		const PhotonPointer photon(signalPhotons.at(index));
		histMan_->H1D_BJetBinned("Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("Photon_Phi")->Fill(photon->phi(), weight_);
		histMan_->H1D_BJetBinned("Photon_ET")->Fill(photon->et(), weight_);
		
		if (photon->isInEndCapRegion()){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_endcap")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->RhoCorrectedPFChargedHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->RhoCorrectedPFNeutralHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->RhoCorrectedPFPhotonIso(event->rho()), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->RhoCorrectedPFChargedHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->RhoCorrectedPFNeutralHadronIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->RhoCorrectedPFPhotonIso(event->rho()), weight_);
		}
			
		histMan_->H1D_BJetBinned("Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("Photon_EcalIso")->Fill(photon->ecalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso")->Fill(photon->hcalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso2012")->Fill(photon->hcalIsolation2012(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrckIso")->Fill(photon->trackerIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCeta")->Fill(photon->superClusterEta(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCphi")->Fill(photon->superClusterPhi(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCenergy")->Fill(photon->superClusterEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCSeedEnergy")->Fill(photon->superClusterSeedEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_E3x3")->Fill(photon->Ecal3x3Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_E5x5")->Fill(photon->Ecal5x5Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrkVeto")->Fill(photon->TrackVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_ConvSEVeto")->Fill(photon->ConversionSafeElectronVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_HtowoE")->Fill(photon->SingleTowerHoE(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso")->Fill(photon->PFChargedHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso")->Fill(photon->PFNeutralHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFPhotonIso")->Fill(photon->PFPhotonIso(), weight_);
		
		for (unsigned int index = 0; index < jets.size(); ++index) { 
			const JetPointer jet(jets.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_jets")->Fill(photon->deltaR(jet), weight_);
		}
		
		for (unsigned int index = 0; index < electrons.size(); ++index) { 
			const ElectronPointer electron(electrons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_electrons")->Fill(photon->deltaR(electron), weight_);
		}
		
		for (unsigned int index = 0; index < muons.size(); ++index) { 
			const MuonPointer muon(muons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_muons")->Fill(photon->deltaR(muon), weight_);
		}
	}
}


void PhotonAnalyser::analyse_NminusOnePhotons(const EventPtr event, PhotonCollection nMinusOnePhotons, JetCollection jets, ElectronCollection electrons, MuonCollection muons, TString cut){

	string folder = histogramFolder_ + "/NminusOnePhotons";
	histMan_->setCurrentHistogramFolder(folder);

	//const ElectronCollection electrons = topMuMuRefSelection_->goodElectrons(event);
	//const MuonCollection muons = topMuMuRefSelection_->goodMuons(event);

	weight_ = event->weight() * prescale_ * scale_;
//	const JetCollection jets = event->Jets();
//	const ElectronCollection electrons = event->Electrons();
//	const MuonCollection muons = event->Muons();

// need to change to rhgo corrected?
	for (unsigned int index = 0; index < nMinusOnePhotons.size(); ++index) {
		const PhotonPointer photon(nMinusOnePhotons.at(index));

		if(cut =="passesEtAndEta"){
		histMan_->H1D_BJetBinned("Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("Photon_ET")->Fill(photon->et(), weight_);
		}

		if(cut =="passesHOverE"){
		histMan_->H1D_BJetBinned("Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("Photon_HtowoE")->Fill(photon->SingleTowerHoE(), weight_);
		}

		if (photon->isInEndCapRegion() && cut =="passesShowerShape"){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_endcap")->Fill(photon->sigmaIEtaIEta(), weight_);
		}
		
		if (photon->isInBarrelRegion() && cut =="passesShowerShape"){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
		}

		if (photon->isInEndCapRegion() && cut =="passesPFChargedIso"){
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->RhoCorrectedPFChargedHadronIso(event->rho()), weight_);
		}
		if (photon->isInBarrelRegion() && cut =="passesPFChargedIso"){
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->RhoCorrectedPFChargedHadronIso(event->rho()), weight_);
		}

		if (photon->isInEndCapRegion() && cut =="passesPFNeutralIso"){
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->RhoCorrectedPFNeutralHadronIso(event->rho()), weight_);
		}
		if (photon->isInBarrelRegion() && cut =="passesPFNeutralIso"){
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->RhoCorrectedPFNeutralHadronIso(event->rho()), weight_);
	    }


		if (photon->isInEndCapRegion() && cut =="passesPFPhotonIso"){
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->RhoCorrectedPFPhotonIso(event->rho()), weight_);
		}
		if (photon->isInBarrelRegion() && cut =="passesPFPhotonIso"){
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->RhoCorrectedPFPhotonIso(event->rho()), weight_);
		}


		if(cut =="passesDeltaRgammaMuons"){
					for (unsigned int index = 0; index < muons.size(); ++index) {
						const MuonPointer muon(muons.at(index));
						histMan_->H1D_BJetBinned("Photon_deltaR_muons")->Fill(photon->deltaR(muon), weight_);
					}
		}

		if(cut =="passesDeltaRgammaElectrons"){
				for (unsigned int index = 0; index < electrons.size(); ++index) {
					const ElectronPointer electron(electrons.at(index));
					histMan_->H1D_BJetBinned("Photon_deltaR_electrons")->Fill(photon->deltaR(electron), weight_);
				}
		}


	}
}


PhotonAnalyser::PhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
                BasicAnalyser(histMan, histogramFolder) { //
}


PhotonAnalyser::~PhotonAnalyser(){
}

void PhotonAnalyser::createHistograms() {

	histMan_->setCurrentHistogramFolder(histogramFolder_+"/AllPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 0.5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 0.5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/SignalPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);

	
	string folder = histogramFolder_ + "/NminusOnePhotons";
	histMan_->setCurrentHistogramFolder(folder);

	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
//	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);

	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);

//	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);

//	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);

	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);

	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);

	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);

	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);

}

}

