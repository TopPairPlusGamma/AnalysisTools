/*
 * MuonAnalyser2.cpp
 *
 *  Created on: 8 Jul 2013
 *      Author: N.Berry
 */
#include "../../interface/Analysers/MuonAnalyser2.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
namespace BAT {

void MuonAnalyser2::analyse(const EventPtr event) {
	analyseAllMuons(event);
//	analyseSignalMuons(event);
}

void MuonAnalyser2::analyseAllMuons(const EventPtr event) {

	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::AtLeastOnePhoton)) {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/Muons/AllMuons");
	weight_ = event->weight() * prescale_ * scale_;
	const MuonCollection muons = event->Muons();
	const JetCollection jets = event->Jets();

	histMan_->H1D_BJetBinned("Number_Of_Muons")->Fill(muons.size(), weight_);
	
	for (unsigned int index = 0; index < muons.size(); ++index) {
		const MuonPointer muon(muons.at(index));

		histMan_->H1D_BJetBinned("Muon_Pt")->Fill(muon->pt(), weight_);
		histMan_->H1D_BJetBinned("Muon_Eta")->Fill(muon->eta(), weight_);
		histMan_->H1D_BJetBinned("Muon_AbsEta")->Fill(fabs(muon->eta()), weight_);
		histMan_->H1D_BJetBinned("Muon_Phi")->Fill(muon->phi(), weight_);
		histMan_->H1D_BJetBinned("Muon_pfIsolation_03")->Fill(muon->pfRelativeIsolation(0.3, true), weight_);
		histMan_->H1D_BJetBinned("Muon_pfIsolation_04")->Fill(muon->pfRelativeIsolation(0.4, true), weight_);
		histMan_->H1D_BJetBinned("Muon_pfIsolation_05")->Fill(muon->pfRelativeIsolation(0.5, true), weight_);
		histMan_->H1D_BJetBinned("Muon_dB")->Fill(muon->d0(), weight_);
		
		for (unsigned int index = 0; index < jets.size(); ++index) { 
			const JetPointer jet(jets.at(index));
			histMan_->H1D_BJetBinned("Muon_deltaR_jets")->Fill(muon->deltaR(jet), weight_);
		}
	}
}
}

// void MuonAnalyser2::analyseSignalMuons(const EventPtr event) {
// 
// 	const MuonCollection signalMuons = topMuMuRefSelection_->signalLeptons(event);
// 	
// 	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::AtLeastOnePhoton)) {
// 	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/Muons/SignalMuons");
// 	weight_ = event->weight() * prescale_ * scale_;
// 	const JetCollection jets = event->Jets();
// 	
// 	histMan_->H1D_BJetBinned("Number_Of_Muons")->Fill(signalMuons.size(), weight_);
// 	
// 	for (unsigned int index = 0; index < signalMuons.size(); ++index) {
// 		const MuonCollection muon(signalMuons.at(index));
// 		histMan_->H1D_BJetBinned("Muon_Pt")->Fill(muon->pt(), weight_);
// 		histMan_->H1D_BJetBinned("Muon_Eta")->Fill(muon->eta(), weight_);
// 		histMan_->H1D_BJetBinned("Muon_AbsEta")->Fill(fabs(muon->eta()), weight_);
// 		histMan_->H1D_BJetBinned("Muon_Phi")->Fill(muon->phi(), weight_);
// 		histMan_->H1D_BJetBinned("Muon_pfIsolation_03")->Fill(muon->pfRelativeIsolation(0.3, true), weight_);
// 		histMan_->H1D_BJetBinned("Muon_pfIsolation_04")->Fill(muon->pfRelativeIsolation(0.4, true), weight_);
// 		histMan_->H1D_BJetBinned("Muon_pfIsolation_05")->Fill(muon->pfRelativeIsolation(0.5, true), weight_);
// 		histMan_->H1D_BJetBinned("Muon_dB")->Fill(muon->d0(), weight_);
// 		
// 		for (unsigned int index = 0; index < jets.size(); ++index) { 
// 			const JetPointer jet(jets.at(index));
// 			histMan_->H1D_BJetBinned("Muon_deltaR_jets")->Fill(muon->deltaR(jet), weight_);
// 		}
// 		
// 	}
// }
// }

MuonAnalyser2::MuonAnalyser2(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //
		topMuMuRefSelection_(new TopPairMuMuReferenceSelection()),
		ttbarPlusMETAnalysisSetup_(false) {

}

MuonAnalyser2::~MuonAnalyser2() {
}

void MuonAnalyser2::createHistograms() {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/Muons");
	
			histMan_->addH1D_BJetBinned("Number_Of_Muons", "Number of muons;N(#mu);Events ", 6, -0.5, 5.5);
			histMan_->addH1D_BJetBinned("Muon_Pt", "Muon p_{T};p_{T}(#mu)/GeV;Events/2GeV ", 500, 0, 1000);
			histMan_->addH1D_BJetBinned("Muon_Eta", "Muon #eta; #eta(#mu); Events/(0.02)", 300, -3, 3);
			histMan_->addH1D_BJetBinned("Muon_AbsEta", "Muon |#eta|; |#eta(#mu)|; Events/(0.01)", 300, 0, 3);
			histMan_->addH1D_BJetBinned("Muon_Phi", "Muon #phi; #phi(#mu); Events/(0.02)", 400, -4, 4);
			histMan_->addH1D_BJetBinned("Muon_pfIsolation_03",
					"Muon relative pf isolation (DR=0.3); PF relative isolation; Events/(0.01)", 500, 0, 5);
			histMan_->addH1D_BJetBinned("Muon_pfIsolation_04",
					"Muon relative pf isolation (DR=0.4); PF relative isolation; Events/(0.01)", 500, 0, 5);
			histMan_->addH1D_BJetBinned("Muon_pfIsolation_05",
					"Muon relative pf isolation (DR=0.5); PF relative isolation; Events/(0.01)", 500, 0, 5);
			histMan_->addH1D_BJetBinned("Muon_dB", "Muon dB(PV); dB/cm; Events/(0.001)", 200, 0, 0.2);


}

void MuonAnalyser2::useTTbarPlusMETSetup(bool use) {
	ttbarPlusMETAnalysisSetup_ = use;
}

}
