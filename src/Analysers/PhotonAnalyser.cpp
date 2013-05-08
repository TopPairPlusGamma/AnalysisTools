/*
 * PhotonAnalyser.cpp
 *
 *  Created on: 26 April 2013
 *      Author: N.Berry
 */
#include "../../interface/Analysers/PhotonAnalyser.h"
#include "../../interface/GlobalVariables.h"

namespace BAT {

void PhotonAnalyser::analyse(const EventPtr event){
	
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = event->weight() * prescale_ * scale_;
	const PhotonCollection photons = event->Photons();

	histMan_->H1D_BJetBinned("Number_Of_Photons")->Fill(photons.size(), weight_);

	for (unsigned int index = 0; index < photons.size(); ++index) {
		const PhotonPointer photon(photons.at(index));
		histMan_->H1D_BJetBinned("All_Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("All_Photon_Phi")->Fill(photon->phi(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_ET")->Fill(photon->et(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_sigma_ietaieta")->Fill(photon->sigmaIEtaIEta(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_EcalIso")->Fill(photon->ecalIsolation(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_HcalIso")->Fill(photon->hcalIsolation(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_TrckIso")->Fill(photon->trackerIsolation(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_SCeta")->Fill(photon->superClusterEta(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_SCphi")->Fill(photon->superClusterPhi(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_SCenergy")->Fill(photon->superClusterEnergy(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_SCSeedEnergy")->Fill(photon->superClusterSeedEnergy(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_E3x3")->Fill(photon->Ecal3x3Cluster(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_E5x5")->Fill(photon->Ecal5x5Cluster(), weight_);
		histMan_->H1D_BJetBinned("All_Photon_TrkVeto")->Fill(photon->TrackVeto(), weight_);
	}

}

void PhotonAnalyser::analysePhoton(const PhotonPointer photon, double weight) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = weight * prescale_ * scale_;
	
	histMan_->H1D_BJetBinned("photon_eta")->Fill(photon->eta(), weight_);
	histMan_->H1D_BJetBinned("photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
	
	if (!ttbarPlusMETAnalysisSetup_) {
	histMan_->H1D_BJetBinned("photon_pT")->Fill(photon->pt(), weight_);
	histMan_->H1D_BJetBinned("photon_phi")->Fill(photon->phi(), weight_);
	histMan_->H1D_BJetBinned("photon_ET")->Fill(photon->et(), weight_);
	histMan_->H1D_BJetBinned("photon_sigma_ietaieta")->Fill(photon->sigmaIEtaIEta(), weight_);
	histMan_->H1D_BJetBinned("photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
	histMan_->H1D_BJetBinned("photon_EcalIso")->Fill(photon->ecalIsolation(), weight_);
	histMan_->H1D_BJetBinned("photon_HcalIso")->Fill(photon->hcalIsolation(), weight_);
	histMan_->H1D_BJetBinned("photon_TrckIso")->Fill(photon->trackerIsolation(), weight_);
	histMan_->H1D_BJetBinned("photon_SCeta")->Fill(photon->superClusterEta(), weight_);
	histMan_->H1D_BJetBinned("photon_SCphi")->Fill(photon->superClusterPhi(), weight_);
	histMan_->H1D_BJetBinned("photon_SCenergy")->Fill(photon->superClusterEnergy(), weight_);
	histMan_->H1D_BJetBinned("photon_SCseedenergy")->Fill(photon->superClusterSeedEnergy(), weight_);
	histMan_->H1D_BJetBinned("photon_E3x3")->Fill(photon->Ecal3x3Cluster(), weight_);
	histMan_->H1D_BJetBinned("photon_E5x5")->Fill(photon->Ecal5x5Cluster(), weight_);
	histMan_->H1D_BJetBinned("photon_TrkVeto")->Fill(photon->TrackVeto(), weight_);
	}
}

PhotonAnalyser::PhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
                BasicAnalyser(histMan, histogramFolder), //
                ttbarPlusMETAnalysisSetup_(false) {

}


PhotonAnalyser::~PhotonAnalyser(){
}

void PhotonAnalyser::createHistograms() {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	
	if (!ttbarPlusMETAnalysisSetup_) {
		//analyse all photons
	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("All_Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("All_Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("All_Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("All_Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 400, 0, 40);
	histMan_->addH1D_BJetBinned("All_Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("All_Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("All_Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("All_Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("All_Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("All_Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("All_Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	} else{
	histMan_->addH1D_BJetBinned("photon_pT", "Photon p_{T}; p_{T} (GeV); Events/(1 GeV)", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("photon_eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("photon_EcalIso", "Photon ECal Isolation", 500, 0, 5);
	histMan_->addH1D_BJetBinned("photon_HcalIso", "Photon HCal Isolation", 500, 0, 5);
	histMan_->addH1D_BJetBinned("photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 400, 0, 40);
	histMan_->addH1D_BJetBinned("photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	}

}

void PhotonAnalyser::useTTbarPlusMETSetup(bool use) {
	ttbarPlusMETAnalysisSetup_ = use;
}

}
