/*
 * TTbarDiLeptonAnalyser.cpp
 *
 *  Created on: 10 Aug 2013
 *      Author: Phil
 */
#include "../../interface/Analysers/TTbarDiLeptonAnalyser.h"
#include "../../interface/BTagWeight.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"

namespace BAT {

void TTbarDiLeptonAnalyser::analyse(const EventPtr event) {
	muMuSignalAnalysis(event);
	eESignalAnalysis(event);
	eMuSignalAnalysis(event);
}

void TTbarDiLeptonAnalyser::muMuSignalAnalysis(const EventPtr event) {

	if (topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::MetCut)) {
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
			histMan_->setCurrentJetBin(jets.size());
			histMan_->setCurrentBJetBin(numberOfBjets);

			const LeptonPointer signalLepton = topMuMuRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topMuMuRefSelection_->signalPhotons(event);

			    //get dilepton collection
				const ElectronCollection electrons = topMuMuRefSelection_->signalElectrons(event);
				const MuonCollection muons = topMuMuRefSelection_->signalMuons(event);

				for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/Ref selection");

				//met
				metAnalyserMuMuRefSelection_->setScale(bjetWeight);
				metAnalyserMuMuRefSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserMuMuRefSelection_->setScale(bjetWeight);
				jetAnalyserMuMuRefSelection_->analyse(event);

				//DiMuon
				diMuonAnalyserMuMuRefSelection_->setScale(bjetWeight);
				diMuonAnalyserMuMuRefSelection_->analyse(event, muons);

			    //photons
			    photonAnalyserMuMuRefSelection_->setScale(bjetWeight);
			    photonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserMuMuRefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserMuMuRefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}


void TTbarDiLeptonAnalyser::eESignalAnalysis(const EventPtr event) {

	if (topEERefSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::MetCut)) {

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
			histMan_->setCurrentJetBin(jets.size());
			histMan_->setCurrentBJetBin(numberOfBjets);

			//this is for HT in the MET analyser but needs changing
			const LeptonPointer signalLepton = topEERefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topEERefSelection_->signalPhotons(event);

			//get dilepton collection
			const ElectronCollection electrons = topEERefSelection_->signalElectrons(event);
			const MuonCollection muons = topEERefSelection_->signalMuons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/Ref selection");
				//MET
				metAnalyserEERefSelection_->setScale(bjetWeight);
				metAnalyserEERefSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEERefSelection_->setScale(bjetWeight);
				jetAnalyserEERefSelection_->analyse(event);

				//DiElectron
				diElectronAnalyserEERefSelection_->setScale(bjetWeight);
			    diElectronAnalyserEERefSelection_->analyse(event, electrons);

			    //photons
			    photonAnalyserEERefSelection_->setScale(bjetWeight);
			    photonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserEERefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserEERefSelection_->analyse(event, photons, jets, electrons, muons);
			    }

			}
	}
}

void TTbarDiLeptonAnalyser::eMuSignalAnalysis(const EventPtr event) {

	if (topEMuRefSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::AtLeastTwoGoodJets)) {

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

			histMan_->setCurrentJetBin(jets.size());
			histMan_->setCurrentBJetBin(numberOfBjets);
			const LeptonPointer signalLepton = topEMuRefSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			//get dilepton collection
			const ElectronCollection electrons = topEMuRefSelection_->signalElectrons(event);
			const MuonCollection muons = topEMuRefSelection_->signalMuons(event);
			const PhotonCollection photons = topEMuRefSelection_->signalPhotons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/Ref selection");

				//met
				metAnalyserEMuRefSelection_->setScale(bjetWeight);
				metAnalyserEMuRefSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEMuRefSelection_->setScale(bjetWeight);
				jetAnalyserEMuRefSelection_->analyse(event);

				//DiLepton
				eMuAnalyserEMuRefSelection_->setScale(bjetWeight);
			    eMuAnalyserEMuRefSelection_->analyse(event, electrons, muons);

			    //photon
			    photonAnalyserEMuRefSelection_->setScale(bjetWeight);
			    photonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);

			    if(event->getDataType() == DataType::TTJets){
			    ttphotonAnalyserEMuRefSelection_->setScale(bjetWeight);
			    ttphotonAnalyserEMuRefSelection_->analyse(event, photons, jets, electrons, muons);
			    }
			}
	}
}

TTbarDiLeptonAnalyser::TTbarDiLeptonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //
		topMuMuRefSelection_(new TopPairMuMuReferenceSelection()),
		topEERefSelection_(new TopPairEEReferenceSelection()),
		topEMuRefSelection_(new TopPairEMuReferenceSelection()),
		//signal regions MET
		metAnalyserMuMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/MET")), //
		metAnalyserEERefSelection_(new METAnalyser(histMan, histogramFolder + "/EE/Ref selection/MET")), //
		metAnalyserEMuRefSelection_(new METAnalyser(histMan, histogramFolder + "/EMu/Ref selection/MET")),//
		//signal regions MET
		jetAnalyserMuMuRefSelection_(new JetAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Jets")), //
		jetAnalyserEERefSelection_(new JetAnalyser(histMan, histogramFolder + "/EE/Ref selection/Jets")), //
		jetAnalyserEMuRefSelection_(new JetAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Jets")),//
		//signal regions di electron
		diElectronAnalyserEERefSelection_(new DiElectronAnalyser(histMan, histogramFolder + "/EE/Ref selection/DiLepton")), //
		diMuonAnalyserMuMuRefSelection_(new DiMuonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/DiLepton")), //
		eMuAnalyserEMuRefSelection_(new EMuAnalyser(histMan, histogramFolder + "/EMu/Ref selection/DiLepton")), //
		//signal regions Photons
		photonAnalyserMuMuRefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		photonAnalyserEERefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		photonAnalyserEMuRefSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")),//
		//tt photon analyser
		ttphotonAnalyserMuMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		ttphotonAnalyserEERefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		ttphotonAnalyserEMuRefSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")) //
		{

}

TTbarDiLeptonAnalyser::~TTbarDiLeptonAnalyser() {
}

void TTbarDiLeptonAnalyser::createHistograms() {

	//signal met
	metAnalyserMuMuRefSelection_->createHistograms();
	metAnalyserEERefSelection_->createHistograms();
	metAnalyserEMuRefSelection_->createHistograms();
	//signal jets
	jetAnalyserMuMuRefSelection_->createHistograms();
	jetAnalyserEERefSelection_->createHistograms();
	jetAnalyserEMuRefSelection_->createHistograms();
	//signal met di electron
	diElectronAnalyserEERefSelection_->createHistograms();
	diMuonAnalyserMuMuRefSelection_->createHistograms();
	eMuAnalyserEMuRefSelection_->createHistograms();
	//signal photons
	photonAnalyserEERefSelection_->createHistograms();
	photonAnalyserMuMuRefSelection_->createHistograms();
	photonAnalyserEMuRefSelection_->createHistograms();
	//for ttbar
	ttphotonAnalyserMuMuRefSelection_->createHistograms();
	ttphotonAnalyserEERefSelection_->createHistograms();
	ttphotonAnalyserEMuRefSelection_->createHistograms();
}

}
