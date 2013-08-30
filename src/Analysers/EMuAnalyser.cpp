#include "../../interface/Analysers/EMuAnalyser.h"

namespace BAT {

void EMuAnalyser::analyse(const EventPtr event) {

	//This won't work but has to be here
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	ElectronCollection electrons = event->Electrons();
	weight_ = event->weight() * prescale_ * scale_;
	if (electrons.size() == 2) {
		ElectronPointer leadingElectron = electrons.front();
		ElectronPointer secondElectron = electrons.at(1);
		histMan_->H1D_BJetBinned("diElectronMass")->Fill(leadingElectron->invariantMass(secondElectron), weight_);
	}

	ElectronCollection isolatedElectrons;

	for (unsigned int index = 0; index < electrons.size(); ++index) {
		const ElectronPointer electron(electrons.at(index));
		if (electron->pfRelativeIsolation(0.3) < 0.1)
			isolatedElectrons.push_back(electron);
	}
	if (isolatedElectrons.size() == 2) {
		ElectronPointer leadingElectron = isolatedElectrons.front();
		ElectronPointer secondElectron = isolatedElectrons.at(1);
		histMan_->H1D_BJetBinned("diElectronMass_iso")->Fill(leadingElectron->invariantMass(secondElectron), weight_);
	}
}

void EMuAnalyser::analyse(const EventPtr event, const ElectronCollection electrons, const MuonCollection muons) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	weight_ = event->weight() * prescale_ * scale_;
	if (electrons.size() == 1 && muons.size() == 1) {
		ElectronPointer electron = electrons.front();
		MuonPointer muon = muons.front();
		//both
		histMan_->H1D_BJetBinned("diLepton_Mass")->Fill(electron->invariantMass(muon), weight_);
		histMan_->H1D_BJetBinned("diLepton_DeltaR")->Fill(electron->deltaR(muon), weight_);
		//lead
		histMan_->H1D_BJetBinned("LeadLepton_Pt")->Fill(electron->pt(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_Eta")->Fill(electron->eta(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_AbsEta")->Fill(abs(electron->eta()), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_Phi")->Fill(electron->phi(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_RelIso")->Fill(electron->pfRelativeIsolationRhoCorrected(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_HadOverEM")->Fill(electron->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_dB")->Fill(electron->d0_wrtBeamSpot(), weight_);

		//muon
		histMan_->H1D_BJetBinned("SecondLepton_Pt")->Fill(muon->pt(), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_Eta")->Fill(muon->eta(), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_AbsEta")->Fill(abs(muon->eta()), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_Phi")->Fill(muon->phi(), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_RelIso")->Fill(muon->pfRelativeIsolation(0.4, true), weight_);
	}
}

void EMuAnalyser::createHistograms() {
	//create folder/collection name for the histograms
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	// titles are in the format: histogram title; x-axis title; y-axis title
	histMan_->addH1D_BJetBinned("diLepton_Mass", "di-electron mass; m(ee) [GeV]; events;", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("diLepton_DeltaR", "di-electron mass; #Delta R; events;", 500, 0, 5);

	histMan_->addH1D_BJetBinned("LeadLepton_Pt", "lead electron p_{T} [GeV]; events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("LeadLepton_Eta", "lead electron #eta; events", 300, -3., 3. );
	histMan_->addH1D_BJetBinned("LeadLepton_AbsEta", "lead electron #eta; events", 300, 0., 3. );
	histMan_->addH1D_BJetBinned("LeadLepton_Phi", "lead electron #phi; events", 400, -4. , 4. );
	histMan_->addH1D_BJetBinned("LeadLepton_RelIso", "lead electron ReliIso; events", 500, 0. , 5. );

	histMan_->addH1D_BJetBinned("LeadLepton_HadOverEM", "Electron HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("LeadLepton_dB", "Electron dB(PV); dB/cm; Events/(0.001 cm)", 200, 0, 0.2);

	histMan_->addH1D_BJetBinned("SecondLepton_Pt", "lead electron p_{T} [GeV]; events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("SecondLepton_Eta", "lead electron #eta; events", 300, -3., 3. );
	histMan_->addH1D_BJetBinned("SecondLepton_AbsEta", "lead electron #eta; events", 300, 0., 3. );
	histMan_->addH1D_BJetBinned("SecondLepton_Phi", "lead electron #phi; events", 400, -4. , 4. );
	histMan_->addH1D_BJetBinned("SecondLepton_RelIso", "lead electron ReliIso; events", 500, 0. , 5. );
}

EMuAnalyser::EMuAnalyser(boost::shared_ptr<HistogramManager> histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder) {

}

EMuAnalyser::~EMuAnalyser() {
}

}
