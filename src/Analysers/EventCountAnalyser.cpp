/*
 * EventCountAnalyser.cpp
 *
 *  Created on: 24 Mar 2011
 *      Author: kreczko
 */

#include "../../interface/Analysers/EventCountAnalyser.h"
#include "../../interface/BTagWeight.h"

namespace BAT {

void EventCountAnalyser::analyse(const EventPtr event) {

	//	individualCuts(event);
	
	topMuMuReferenceSelection(event);
	topMuMuReferenceSelectionUnweighted(event);
	
	topEEReferenceSelection(event);
	topEEReferenceSelectionUnweighted(event);
	
	topEMuReferenceSelection(event);
	topEMuReferenceSelectionUnweighted(event);

}

void EventCountAnalyser::individualCuts(const EventPtr event) {

	if(topMuMuRefSelection_->passesSelectionUpToStep(event, 1)) {
				cout << "run: " << event->runnumber() << " lumi: " << event->lumiblock() << " evt: " << event->eventnumber() << endl;
/*				if(event->isBeamScraping() || !event->passesHBHENoiseFilter() || !event->passesCSCTightBeamHaloFilter() || !event->passesHCALLaserFilter()
						|| !event->passesECALDeadCellFilter() || !event->passesTrackingFailureFilter() || !event->passesEEBadSCFilter()){

							if(event->isBeamScraping())
								cout << "fail beam scrap" << endl;
							if(!event->passesHBHENoiseFilter())
								cout << "fail HBHE noise filter" << endl;
							if(!event->passesCSCTightBeamHaloFilter())
								cout << "fail CSCTightBeamHaloFilter" << endl;
							if(!event->passesHCALLaserFilter())
								cout << "fail HCALLaserFilter" << endl;
							if(!event->passesECALDeadCellTPFilter())
								cout << "fail ECALDeadCellTPFilter" << endl;
							if(!event->passesTrackingFailureFilter())
								cout << "fail TrackingFailureFilter" << endl;
							if(!event->passesEEBadSCFilter())
								cout << "fail EEBadSCFilter()" << endl;
							if(!event->passesECALLaserCorrFilter())
								cout << "fail ECALLaserCorrFilter()" << endl;
							if(!event->passesTrackingPOGFilters())
								cout << "fail TrackingPOGFilters()" << endl;
				}*/
	}

}


void EventCountAnalyser::topMuMuReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

// 	if (topMuMuRefSelection_->passesSelectionUpToStep(event, 1)) {
// 	const LeptonPointer signalLepton = topMuMuRefSelection_->signalLepton(event);
// 	const MuonPointer signalMuon(boost::static_pointer_cast<Muon>(signalLepton));
// 	double efficiencyCorrection = event->isRealData() ? 1. : signalMuon->getEfficiencyCorrection(false);
// 	 	scale_ = efficiencyCorrection;
// 	}else{
// 		scale_ =1;
// 	}

 	//use bjet weights in histograms for muons
 	const JetCollection jets(topMuMuRefSelection_->cleanedJets(event));
 	const JetCollection bJets(topMuMuRefSelection_->cleanedBJets(event));
 	unsigned int numberOfBjets(bJets.size());
 	vector<double> bjetWeights;

 	if (event->isRealData()) {
 		for (unsigned int index = 0; index <= numberOfBjets; ++index) {
 			if (index == numberOfBjets)
 				bjetWeights.push_back(1.);
 			else
 				bjetWeights.push_back(0);
 		}
 	} else
 		bjetWeights = BjetWeights(jets, numberOfBjets);

 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_ *weight_ge1b;

	histMan_->H1D("TTbarMuMuRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarMuMuRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topMuMuRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topMuMuRefSelection_->passesSelectionUpToStep(event, step);
		
		if (passesStepUpTo)
			histMan_->H1D("TTbarMuMuRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarMuMuRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topMuMuReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarMuMuRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarMuMuRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topMuMuRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topMuMuRefSelection_->passesSelectionUpToStep(event, step);
		if (passesStepUpTo)
			histMan_->H1D("TTbarMuMuRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarMuMuRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

void EventCountAnalyser::topEEReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

 	//use bjet weights in histograms for muons
 	const JetCollection jets(topEERefSelection_->cleanedJets(event));
 	const JetCollection bJets(topEERefSelection_->cleanedBJets(event));
 			unsigned int numberOfBjets(bJets.size());
 	vector<double> bjetWeights;
 	if (event->isRealData()) {
 		for (unsigned int index = 0; index <= numberOfBjets; ++index) {
 			if (index == numberOfBjets)
 				bjetWeights.push_back(1.);
 			else
 				bjetWeights.push_back(0);
 		}
 	} else
 		bjetWeights = BjetWeights(jets, numberOfBjets);

 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_;

	histMan_->H1D("TTbarEERefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarEERefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {

		bool passesStep = topEERefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEERefSelection_->passesSelectionUpToStep(event, step);

		
		
		if (passesStepUpTo)
			histMan_->H1D("TTbarEERefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEERefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topEEReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarEERefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarEERefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEERefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEERefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEERefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEERefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}

 void EventCountAnalyser::topEMuReferenceSelection(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

 	//use bjet weights in histograms for muons
 	const JetCollection jets(topEMuRefSelection_->cleanedJets(event));
 	const JetCollection bJets(topEMuRefSelection_->cleanedBJets(event));
 			unsigned int numberOfBjets(bJets.size());
 	vector<double> bjetWeights;
 	if (event->isRealData()) {
 		for (unsigned int index = 0; index <= numberOfBjets; ++index) {
 			if (index == numberOfBjets)
 				bjetWeights.push_back(1.);
 			else
 				bjetWeights.push_back(0);
 		}
 	} else
 		bjetWeights = BjetWeights(jets, numberOfBjets);


 	double weight_ge1b = 0.;
 	if(numberOfBjets>0){
 	for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {
 		double b_weight = bjetWeights.at(weightIndex);

 	if(weightIndex>0)
 		weight_ge1b += b_weight;
 	}
 	}else{
 		weight_ge1b = 1.;
 	}

	weight_ = event->weight() * prescale_ * scale_;

	histMan_->H1D("TTbarEMuRefSelection")->Fill(-1, weight_);
	histMan_->H1D("TTbarEMuRefSelection_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEMuRefSelection_->passesSelectionStep(event, step);
		bool passesStepUpTo = topEMuRefSelection_->passesSelectionUpToStep(event, step);
		if (passesStepUpTo)
			histMan_->H1D("TTbarEMuRefSelection")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEMuRefSelection_singleCuts")->Fill(step, weight_);
	}

}

void EventCountAnalyser::topEMuReferenceSelectionUnweighted(const EventPtr event) {
	histMan_->setCurrentHistogramFolder(histogramFolder_);
	weight_ = 1.;
	histMan_->H1D("TTbarEMuRefSelectionUnweighted")->Fill(-1, weight_);
	histMan_->H1D("TTbarEMuRefSelectionUnweighted_singleCuts")->Fill(-1, weight_);

	for (unsigned int step = 0; step < TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++step) {
		bool passesStep = topEMuRefSelection_->passesSelectionStep(event, step);

		bool passesStepUpTo = topEMuRefSelection_->passesSelectionUpToStep(event, step);

		if (passesStepUpTo)
			histMan_->H1D("TTbarEMuRefSelectionUnweighted")->Fill(step, weight_);
		if (passesStep)
			histMan_->H1D("TTbarEMuRefSelectionUnweighted_singleCuts")->Fill(step, weight_);
	}
}


void EventCountAnalyser::createHistograms() {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	const boost::array<string, 1> refSelections_dimuon = { {"TTbarMuMu"} };
	for (unsigned int index = 0; index < refSelections_dimuon.size(); ++index) {
		string selection = refSelections_dimuon.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
	const boost::array<string, 1> refSelections_dielectron = { {"TTbarEE"} };
	for (unsigned int index = 0; index < refSelections_dielectron.size(); ++index) {
		string selection = refSelections_dielectron.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEEReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
 	const boost::array<string, 1> refSelections_dilepton = { {"TTbarEMu"} };
	for (unsigned int index = 0; index < refSelections_dilepton.size(); ++index) {
		string selection = refSelections_dilepton.at(index) + "RefSelection";
		histMan_->addH1D(selection, selection, TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "_singleCuts", selection + " (single cuts",
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted", selection, TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
		histMan_->addH1D(selection + "Unweighted_singleCuts", selection + " (single cuts",
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS + 1, -1.5,
				TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS - 0.5);
	}
}

void EventCountAnalyser::setHistogramLabels() {
	histMan_->setCurrentHistogramFolder(histogramFolder_);

	for (unsigned int index = 0; index < TTbarMuMuReferenceSelection::NUMBER_OF_SELECTION_STEPS; ++index) {
		unsigned int bin(index + 1);
		string binLabel = TTbarMuMuReferenceSelection::StringSteps[index];

		histMan_->H1D("TTbarMuMuRefSelection")->GetXaxis()->SetBinLabel(bin, binLabel.c_str());
		histMan_->H1D("TTbarMuMuRefSelection_singleCuts")->GetXaxis()->SetBinLabel(bin, binLabel.c_str());

	}
}

EventCountAnalyser::EventCountAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //

		//dilepton signal selections
		topMuMuRefSelection_(new TopPairMuMuReferenceSelection()), //
		topEERefSelection_(new TopPairEEReferenceSelection()), //
		topEMuRefSelection_(new TopPairEMuReferenceSelection()){ //
		
}

EventCountAnalyser::~EventCountAnalyser() {
}

} /* namespace BAT */
