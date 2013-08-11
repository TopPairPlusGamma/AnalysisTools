/*
 * DiElectronAnalyser.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: lkreczko
 */

#include "../../interface/Analysers/DiElectronAnalyser.h"

namespace BAT {

void DiElectronAnalyser::analyse(const EventPtr event) {
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

void DiElectronAnalyser::analyse(const EventPtr event, const ElectronCollection electrons) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	weight_ = event->weight() * prescale_ * scale_;
	if (electrons.size() == 2) {
		ElectronPointer leadingElectron = electrons.front();
		ElectronPointer secondElectron = electrons.at(1);
		//both
		histMan_->H1D_BJetBinned("diElectron_Mass")->Fill(leadingElectron->invariantMass(secondElectron), weight_);
		histMan_->H1D_BJetBinned("diElectron_DeltaR")->Fill(leadingElectron->deltaR(secondElectron), weight_);
		//lead
		histMan_->H1D_BJetBinned("LeadElectron_Pt")->Fill(leadingElectron->pt(), weight_);
		histMan_->H1D_BJetBinned("LeadElectron_Eta")->Fill(leadingElectron->eta(), weight_);
		histMan_->H1D_BJetBinned("LeadElectron_AbsEta")->Fill(abs(leadingElectron->eta()), weight_);
		histMan_->H1D_BJetBinned("LeadElectron_Phi")->Fill(leadingElectron->phi(), weight_);
		histMan_->H1D_BJetBinned("LeadElectron_RelIso")->Fill(leadingElectron->pfRelativeIsolationRhoCorrected(), weight_);
		histMan_->H1D_BJetBinned("LeadElectron_HadOverEM")->Fill(leadingElectron->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("LeadElectron_dB")->Fill(leadingElectron->d0_wrtBeamSpot(), weight_);
		//second
		histMan_->H1D_BJetBinned("SecondElectron_Pt")->Fill(secondElectron->pt(), weight_);
		histMan_->H1D_BJetBinned("SecondElectron_Eta")->Fill(secondElectron->eta(), weight_);
		histMan_->H1D_BJetBinned("SecondElectron_AbsEta")->Fill(abs(secondElectron->eta()), weight_);
		histMan_->H1D_BJetBinned("SecondElectron_Phi")->Fill(secondElectron->phi(), weight_);
		histMan_->H1D_BJetBinned("SecondElectron_RelIso")->Fill(secondElectron->pfRelativeIsolationRhoCorrected(), weight_);
		histMan_->H1D_BJetBinned("SecondElectron_HadOverEM")->Fill(secondElectron->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("SecondElectron_dB")->Fill(secondElectron->d0_wrtBeamSpot(), weight_);

	}
}

void DiElectronAnalyser::createHistograms() {
	//create folder/collection name for the histograms
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	// titles are in the format: histogram title; x-axis title; y-axis title
	histMan_->addH1D_BJetBinned("diElectron_Mass", "di-electron mass; m(ee) [GeV]; events;", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("diElectron_DeltaR", "di-electron mass; #Delta R; events;", 500, 0, 5);

	histMan_->addH1D_BJetBinned("LeadElectron_Pt", "lead electron p_{T} [GeV]; events", 300, 0, 1000);
	histMan_->addH1D_BJetBinned("LeadElectron_Eta", "lead electron #eta; events", 300, -3., 3. );
	histMan_->addH1D_BJetBinned("LeadElectron_AbsEta", "lead electron #eta; events", 300, 0., 3. );
	histMan_->addH1D_BJetBinned("LeadElectron_Phi", "lead electron #phi; events", 400, -4. , 4. );
	histMan_->addH1D_BJetBinned("LeadElectron_RelIso", "lead electron ReliIso; events", 500, 0. , 5. );

	histMan_->addH1D_BJetBinned("LeadElectron_HadOverEM", "Electron HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("LeadElectron_dB", "Electron dB(PV); dB/cm; Events/(0.001 cm)", 200, 0, 0.2);

	histMan_->addH1D_BJetBinned("SecondElectron_Pt", "lead electron p_{T} [GeV]; events", 300, 0, 1000);
	histMan_->addH1D_BJetBinned("SecondElectron_Eta", "lead electron #eta; events", 300, -3., 3. );
	histMan_->addH1D_BJetBinned("SecondElectron_AbsEta", "lead electron #eta; events", 300, 0., 3. );
	histMan_->addH1D_BJetBinned("SecondElectron_Phi", "lead electron #phi; events", 400, -4. , 4. );
	histMan_->addH1D_BJetBinned("SecondElectron_RelIso", "lead electron ReliIso; events", 500, 0. , 5. );

	histMan_->addH1D_BJetBinned("SecondElectron_HadOverEM", "Electron HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("SecondElectron_dB", "Electron dB(PV); dB/cm; Events/(0.001 cm)", 200, 0, 0.2);


}

DiElectronAnalyser::DiElectronAnalyser(boost::shared_ptr<HistogramManager> histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder) {

}

DiElectronAnalyser::~DiElectronAnalyser() {
}

}
