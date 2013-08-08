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

namespace BAT {

void PhotonAnalyser::analyse(const EventPtr event){

	analyseMuMu(event);
	analyseMuMu_signalphotons(event);
	analyseEE(event);
	analyseEE_signalphotons(event);
	//analyseEMu(event);
	//analyseEMu_signalphotons(event);

}

void PhotonAnalyser::analyseMuMu(const EventPtr event){

//	const PhotonCollection signalPhotons = topMuMuRefSelection_->signalPhotons(event);

	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::JustOneGoodPhoton)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/AllPhotons");
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
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
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
}

void PhotonAnalyser::analyseMuMu_signalphotons(const EventPtr event){

	const PhotonCollection signalPhotons = topMuMuRefSelection_->signalPhotons(event);
	
	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::JustOneGoodPhoton)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/SignalPhotons");
	weight_ = event->weight() * prescale_ * scale_;
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
	const MuonCollection muons = event->Muons();

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
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
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
}

void PhotonAnalyser::analyseEE(const EventPtr event){
	
//	const PhotonCollection signalPhotons = topEERefSelection_->signalPhotons(event);
	
	if (topEERefSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::AtLeastOnePhoton)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/AllPhotons");
	weight_ = event->weight() * prescale_ * scale_;
	const PhotonCollection photons = event->Photons();
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
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
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
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
}

void PhotonAnalyser::analyseEE_signalphotons(const EventPtr event){

	const PhotonCollection signalPhotons = topEERefSelection_->signalPhotons(event);
	
	if (topEERefSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::JustOneGoodPhoton)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/SignalPhotons");
	weight_ = event->weight() * prescale_ * scale_;
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
	const MuonCollection muons = event->Muons();

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
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
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
}
void PhotonAnalyser::analyseEMu(const EventPtr event){

 	//const PhotonCollection signalPhotons = topEMuRefSelection_->signalPhotons(event);

 	cout << "in photon main: " << TTbarEMuReferenceSelection::JustOneGoodPhoton  << endl;
	


	if (topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::JustOneGoodPhoton)) {

		cout << "in photon sel" << endl;
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "EMu/AllPhotons");
	weight_ = event->weight() * prescale_ * scale_;
	const PhotonCollection photons = event->Photons();
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
	const MuonCollection muons = event->Muons();

	histMan_->H1D_BJetBinned("Number_Of_Photons")->Fill(photons.size(), weight_);
	cout << "photon main" << endl;
	for (unsigned int index = 0; index < photons.size(); ++index) {
		const PhotonPointer photon(photons.at(index));
		histMan_->H1D_BJetBinned("Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("Photon_Phi")->Fill(photon->phi(), weight_);
		histMan_->H1D_BJetBinned("Photon_ET")->Fill(photon->et(), weight_);
		
		cout << "photon bar /end" << endl;

		if (photon->isInEndCapRegion()){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_endcap")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
		}
			
		cout << "photon stuff" << endl;

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
		
		cout << "delta rs" << endl;

		for (unsigned int index = 0; index < jets.size(); ++index) { 
			const JetPointer jet(jets.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR")->Fill(photon->deltaR(jet), weight_);
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
} 

void PhotonAnalyser::analyseEMu_signalphotons(const EventPtr event){

	const PhotonCollection signalPhotons = topEMuRefSelection_->signalPhotons(event);
	
	if (topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::JustOneGoodPhoton)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/SignalPhotons");
	weight_ = event->weight() * prescale_ * scale_;
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
	const MuonCollection muons = event->Muons();

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
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
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
}

/* void PhotonAnalyser::analysePhoton(const EventPtr event) {
	if (topMuMuRefSelection_->passesSelectionUpToStep(event, 5)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = event->weight() * prescale_ * scale_;
	const PhotonCollection signalPhotons = topMuMuRefSelection_->signalPhotons(event);
	const JetCollection jets = event->Jets();
	
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
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
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
			histMan_->H1D_BJetBinned("Photon_deltaR")->Fill(photon->deltaR(jet), weight_);
		}
	}
    }
} */

PhotonAnalyser::PhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
                BasicAnalyser(histMan, histogramFolder), //
                topMuMuRefSelection_(new TopPairMuMuReferenceSelection()),
		topEERefSelection_(new TopPairEEReferenceSelection()),
		topEMuRefSelection_(new TopPairEMuReferenceSelection()),
		ttbarPlusMETAnalysisSetup_(false) {

}


PhotonAnalyser::~PhotonAnalyser(){
}

void PhotonAnalyser::createHistograms() {

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/AllPhotons");
	
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 400);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
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
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 25, 0, 5);	
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 30, 0, 1.2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 33, 0, 0.33);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/SignalPhotons");
	
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 400);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
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
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 30, 0, 1.2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 33, 0, 0.33);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/AllPhotons");
	
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 400);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
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
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 30, 0, 1.2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 33, 0, 0.33);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/SignalPhotons");
	
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 400);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
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
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 30, 0, 1.2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 33, 0, 0.33);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);


	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/AllPhotons");
	
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 400);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
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
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 30, 0, 1.2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 33, 0, 0.33);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);

	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/SignalPhotons");
	
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 400);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 100, 0, 0.1);
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
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 25, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 30, 0, 1.2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 33, 0, 0.33);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 130, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 100, 0, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 42, 0, 42);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 130, 0, 130);

}

void PhotonAnalyser::useTTbarPlusMETSetup(bool use) {
	ttbarPlusMETAnalysisSetup_ = use;
}

}
