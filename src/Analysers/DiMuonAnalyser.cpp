#include "../../interface/Analysers/DiMuonAnalyser.h"

namespace BAT {

void DiMuonAnalyser::analyse(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	MuonCollection muons = event->Muons();
	weight_ = event->weight() * prescale_ * scale_;
	if (muons.size() == 2) {
		MuonPointer leadingMuon = muons.front();
		MuonPointer secondMuon = muons.at(1);
		histMan_->H1D_BJetBinned("diMuonMass")->Fill(leadingMuon->invariantMass(secondMuon), weight_);
	}

	MuonCollection isolatedMuons;

	for (unsigned int index = 0; index < muons.size(); ++index) {
		const MuonPointer electron(muons.at(index));
		if (electron->pfRelativeIsolation(0.3) < 0.1)
			isolatedMuons.push_back(electron);
	}
	if (isolatedMuons.size() == 2) {
		MuonPointer leadingMuon = isolatedMuons.front();
		MuonPointer secondMuon = isolatedMuons.at(1);
		histMan_->H1D_BJetBinned("diMuonMass_iso")->Fill(leadingMuon->invariantMass(secondMuon), weight_);
	}
}

void DiMuonAnalyser::analyse(const EventPtr event, const MuonCollection muons) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	weight_ = event->weight() * prescale_ * scale_;
	if (muons.size() == 2) {
		MuonPointer leadingMuon = muons.front();
		MuonPointer secondMuon = muons.at(1);
		//both
		histMan_->H1D_BJetBinned("diLepton_Mass")->Fill(leadingMuon->invariantMass(secondMuon), weight_);
		histMan_->H1D_BJetBinned("diLepton_DeltaR")->Fill(leadingMuon->deltaR(secondMuon), weight_);
		//lead
		histMan_->H1D_BJetBinned("LeadLepton_Pt")->Fill(leadingMuon->pt(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_Eta")->Fill(leadingMuon->eta(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_AbsEta")->Fill(abs(leadingMuon->eta()), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_Phi")->Fill(leadingMuon->phi(), weight_);
		histMan_->H1D_BJetBinned("LeadLepton_RelIso")->Fill(leadingMuon->pfRelativeIsolation(0.4, true), weight_);

		//second
		histMan_->H1D_BJetBinned("SecondLepton_Pt")->Fill(secondMuon->pt(), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_Eta")->Fill(secondMuon->eta(), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_AbsEta")->Fill(abs(secondMuon->eta()), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_Phi")->Fill(secondMuon->phi(), weight_);
		histMan_->H1D_BJetBinned("SecondLepton_RelIso")->Fill(secondMuon->pfRelativeIsolation(0.4, true), weight_);


	}
}

void DiMuonAnalyser::createHistograms() {
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

	histMan_->addH1D_BJetBinned("SecondLepton_Pt", "lead electron p_{T} [GeV]; events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("SecondLepton_Eta", "lead electron #eta; events", 300, -3., 3. );
	histMan_->addH1D_BJetBinned("SecondLepton_AbsEta", "lead electron #eta; events", 300, 0., 3. );
	histMan_->addH1D_BJetBinned("SecondLepton_Phi", "lead electron #phi; events", 400, -4. , 4. );
	histMan_->addH1D_BJetBinned("SecondLepton_RelIso", "lead electron ReliIso; events", 500, 0. , 5. );


}

DiMuonAnalyser::DiMuonAnalyser(boost::shared_ptr<HistogramManager> histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder) {

}

DiMuonAnalyser::~DiMuonAnalyser() {
}

}
