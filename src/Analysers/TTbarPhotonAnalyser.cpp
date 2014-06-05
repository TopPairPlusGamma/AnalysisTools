/*
 * TTbarPhotonAnalyser.cpp
 *
 *  Created on: 10 Aug 2013
 *      Author: Phil
 */

#include "../../interface/Analysers/TTbarPhotonAnalyser.h"
#include "../../interface/BTagWeight.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"

namespace BAT {

void TTbarPhotonAnalyser::analyse(const EventPtr event) {
	muMuSignalAnalysis(event);
	eESignalAnalysis(event);
	eMuSignalAnalysis(event);
}

void TTbarPhotonAnalyser::muMuSignalAnalysis(const EventPtr event) {

	if (topMuMuPhotonSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::JustOneGoodPhotonPostSelection)) {
			const JetCollection jets(topMuMuPhotonSelection_->cleanedJets(event));
			const JetCollection bJets(topMuMuPhotonSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topMuMuPhotonSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topMuMuPhotonSelection_->signalPhotons(event);

			        //get dilepton collection
			        const ElectronCollection electrons = topMuMuPhotonSelection_->signalElectrons(event);
				const MuonCollection muons = topMuMuPhotonSelection_->signalMuons(event);

				for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/MuMu/Ref selection");

				//met
				metAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				metAnalyserMuMuPhotonSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				jetAnalyserMuMuPhotonSelection_->analyse(event);

				//DiMuon
				diMuonAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				diMuonAnalyserMuMuPhotonSelection_->analyse(event, muons);

			    	//photons
			    	photonAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
			    	photonAnalyserMuMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				
				if(event->getDataType() == DataType::TTGamma || event->getDataType() == DataType::TTJets){
					//signal photons
 			    		ttphotonAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
 			    		ttphotonAnalyserMuMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
					ttphotonAnalyserMuMuPhotonSelection_->analyse_signalPhotons(event, photons, jets, electrons, muons);
				}	
				
				//Vertices
				//vertexAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
				//vertexAnalyserMuMuPhotonSelection_->analyse(event);
				
				//abcdAnalyserMuMuPhotonSelection_->setScale(bjetWeight);
			    	//abcdAnalyserMuMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				

			    //n-EtAndEta photons
			    const PhotonCollection photonsMinusEtAndEta = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesEtAndEta");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");

			    //n-passesHOverE photons
			    const PhotonCollection photonsMinusHOverE = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesHOverE");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");

			    //n-passesShowerShape photons
			    const PhotonCollection photonsMinuspassesShowerShape = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesShowerShape");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");

			    //n-passesPFChargedIso photons
//			    const PhotonCollection photonsMinuspassesPFChargedIso = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
//			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");

			    //n-passesPFNeutralIso photons
			    const PhotonCollection photonsMinuspassesPFNeutralIso = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");

			    //n-passesPFPhotonIso photons
			    const PhotonCollection photonsMinuspassesPFPhotonIso = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
			    
			    //n-passesphoSCChIso photons
			    const PhotonCollection photonsMinuspassesphoSCChIso = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");

			    //n-passesphoSCNuIso photons
			    const PhotonCollection photonsMinuspassesphoSCNuIso = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");

			    //n-passesphoSCPhIso photons
			    const PhotonCollection photonsMinuspassesphoSCPhIso = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");			    
			    
			    //n-passesDeltaRgammaMuons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
			    
			    //n-passesDeltaRgammaJets photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaJets = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaJets");
			    photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaJets, jets, electrons, muons, "passesDeltaRgammaJets");

			    //n-passesDeltaRjetsMuons photons
                            const PhotonCollection photonsMinuspassesDeltaRjetsMuons = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRjetsMuons");
                            photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRjetsMuons, jets, electrons, muons, "passesDeltaRjetsMuons");


			}
	}
}


void TTbarPhotonAnalyser::eESignalAnalysis(const EventPtr event) {

	if (topEEPhotonSelection_->passesSelectionUpToStep(event, TTbarEEReferenceSelection::JustOneGoodPhotonPostSelection)) {

			const JetCollection jets(topEEPhotonSelection_->cleanedJets(event));
			const JetCollection bJets(topEEPhotonSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topEEPhotonSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));
			const PhotonCollection photons = topEEPhotonSelection_->signalPhotons(event);

			//get dilepton collection
			const ElectronCollection electrons = topEEPhotonSelection_->signalElectrons(event);
			const MuonCollection muons = topEEPhotonSelection_->signalMuons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EE/Ref selection");
				//MET
				metAnalyserEEPhotonSelection_->setScale(bjetWeight);
				metAnalyserEEPhotonSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEEPhotonSelection_->setScale(bjetWeight);
				jetAnalyserEEPhotonSelection_->analyse(event);

				//DiElectron
				diElectronAnalyserEEPhotonSelection_->setScale(bjetWeight);
			    	diElectronAnalyserEEPhotonSelection_->analyse(event, electrons);

			    	//photons
			    	photonAnalyserEEPhotonSelection_->setScale(bjetWeight);
			    	photonAnalyserEEPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				
				if(event->getDataType() == DataType::TTGamma || event->getDataType() == DataType::TTJets){
					//signal photons
			    		ttphotonAnalyserEEPhotonSelection_->setScale(bjetWeight);
			    		ttphotonAnalyserEEPhotonSelection_->analyse(event, photons, jets, electrons, muons);
					ttphotonAnalyserEEPhotonSelection_->analyse_signalPhotons(event, photons, jets, electrons, muons);
				}	
				
				//Vertices
				//vertexAnalyserEEPhotonSelection_->setScale(bjetWeight);
				//vertexAnalyserEEPhotonSelection_->analyse(event);
				
				//abcdAnalyserEEPhotonSelection_->setScale(bjetWeight);
			    	//abcdAnalyserEEPhotonSelection_->analyse(event, photons, jets, electrons, muons);

						    //n-EtAndEta photons
			    const PhotonCollection photonsMinusEtAndEta = topEEPhotonSelection_->nMinusOnePhotons(event, "passesEtAndEta");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");

			    //n-passesHOverE photons
			    const PhotonCollection photonsMinusHOverE = topEEPhotonSelection_->nMinusOnePhotons(event, "passesHOverE");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");

			    //n-passesShowerShape photons
			    const PhotonCollection photonsMinuspassesShowerShape = topEEPhotonSelection_->nMinusOnePhotons(event, "passesShowerShape");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");

			    //n-passesPFChargedIso photons
//			    const PhotonCollection photonsMinuspassesPFChargedIso = topEEPhotonSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
//			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");

			    //n-passesPFNeutralIso photons
			    const PhotonCollection photonsMinuspassesPFNeutralIso = topEEPhotonSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");

			    //n-passesPFPhotonIso photons
			    const PhotonCollection photonsMinuspassesPFPhotonIso = topEEPhotonSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
			    
			    //n-passesphoSCChIso photons
			    const PhotonCollection photonsMinuspassesphoSCChIso = topEEPhotonSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");

			    //n-passesphoSCNuIso photons
			    const PhotonCollection photonsMinuspassesphoSCNuIso = topEEPhotonSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");

			    //n-passesphoSCPhIso photons
			    const PhotonCollection photonsMinuspassesphoSCPhIso = topEEPhotonSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
			    
			    //n-passesDeltaRgammaMuons photons
//			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topEEPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
//			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
			    
			    //n-passesDeltaRgammaElectrons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topEEPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
			    photonAnalyserEEPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");

                            //n-passesDeltaRgammaJets photons
                            const PhotonCollection photonsMinuspassesDeltaRgammaJets = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaJets");
                            photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaJets, jets, electrons, muons, "passesDeltaRgammaJets");

                            //n-passesDeltaRjetsMuons photons
                            const PhotonCollection photonsMinuspassesDeltaRjetsElectrons = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRjetsElectrons");
                            photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRjetsElectrons, jets, electrons, muons, "passesDeltaRjetsElectrons");
			}
	}
}

void TTbarPhotonAnalyser::eMuSignalAnalysis(const EventPtr event) {

	if (topEMuPhotonSelection_->passesSelectionUpToStep(event, TTbarEMuReferenceSelection::JustOneGoodPhotonPostSelection)) {

			const JetCollection jets(topEMuPhotonSelection_->cleanedJets(event));
			const JetCollection bJets(topEMuPhotonSelection_->cleanedBJets(event));
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
			const LeptonPointer signalLepton = topEMuPhotonSelection_->signalLepton(event);
			const ElectronPointer signalElectron(boost::static_pointer_cast<Electron>(signalLepton));

			//get dilepton collection
			const ElectronCollection electrons = topEMuPhotonSelection_->signalElectrons(event);
			const MuonCollection muons = topEMuPhotonSelection_->signalMuons(event);
			const PhotonCollection photons = topEMuPhotonSelection_->signalPhotons(event);

			for (unsigned int weightIndex = 0; weightIndex < bjetWeights.size(); ++weightIndex) {

				double bjetWeight = bjetWeights.at(weightIndex);
				histMan_->setCurrentBJetBin(weightIndex);
				histMan_->setCurrentHistogramFolder(histogramFolder_ + "/EMu/Ref selection");

				//met
				metAnalyserEMuPhotonSelection_->setScale(bjetWeight);
				metAnalyserEMuPhotonSelection_->analyse(event, signalLepton);

				//jets
				jetAnalyserEMuPhotonSelection_->setScale(bjetWeight);
				jetAnalyserEMuPhotonSelection_->analyse(event);

				//DiLepton
				eMuAnalyserEMuPhotonSelection_->setScale(bjetWeight);
			    	eMuAnalyserEMuPhotonSelection_->analyse(event, electrons, muons);

				//Vertices
				//vertexAnalyserEMuPhotonSelection_->setScale(bjetWeight);
				//vertexAnalyserEMuPhotonSelection_->analyse(event);
				
				//abcdAnalyserEMuPhotonSelection_->setScale(bjetWeight);
			    	//abcdAnalyserEMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
				
			    //photon
			    photonAnalyserEMuPhotonSelection_->setScale(bjetWeight);
			    photonAnalyserEMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
			    
			    if(event->getDataType() == DataType::TTGamma || event->getDataType() == DataType::TTJets){
			    	//signal photon
			    	ttphotonAnalyserEMuPhotonSelection_->setScale(bjetWeight);
			    	ttphotonAnalyserEMuPhotonSelection_->analyse(event, photons, jets, electrons, muons);
			    	ttphotonAnalyserEMuPhotonSelection_->analyse_signalPhotons(event, photons, jets, electrons, muons);
			    }	
			    
			    
			    
			    			    //n-EtAndEta photons
			    const PhotonCollection photonsMinusEtAndEta = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesEtAndEta");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinusEtAndEta, jets, electrons, muons, "passesEtAndEta");


			    //n-passesHOverE photons
			    const PhotonCollection photonsMinusHOverE = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesHOverE");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinusHOverE, jets, electrons, muons, "passesHOverE");

			    //n-passesShowerShape photons
			    const PhotonCollection photonsMinuspassesShowerShape = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesShowerShape");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesShowerShape, jets, electrons, muons, "passesShowerShape");

			    //n-passesPFChargedIso photons
//			    const PhotonCollection photonsMinuspassesPFChargedIso = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesPFChargedIso");
//			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFChargedIso, jets, electrons, muons, "passesPFChargedIso");

			    //n-passesPFNeutralIso photons
			    const PhotonCollection photonsMinuspassesPFNeutralIso = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesPFNeutralIso");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFNeutralIso, jets, electrons, muons, "passesPFNeutralIso");

			    //n-passesPFPhotonIso photons
			    const PhotonCollection photonsMinuspassesPFPhotonIso = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesPFPhotonIso");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesPFPhotonIso, jets, electrons, muons, "passesPFPhotonIso");
			    
			    //n-passesphoSCChIso photons
			    const PhotonCollection photonsMinuspassesphoSCChIso = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesphoSCChIso");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCChIso, jets, electrons, muons, "passesphoSCChIso");

			    //n-passesphoSCNuIso photons
			    const PhotonCollection photonsMinuspassesphoSCNuIso = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesphoSCNuIso");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCNuIso, jets, electrons, muons, "passesphoSCNuIso");

			    //n-passesphoSCPhIso photons
			    const PhotonCollection photonsMinuspassesphoSCPhIso = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesphoSCPhIso");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesphoSCPhIso, jets, electrons, muons, "passesphoSCPhIso");
		    
			    //n-passesDeltaRgammaMuons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaMuons = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaMuons");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaMuons, jets, electrons, muons, "passesDeltaRgammaMuons");
			    
			    //n-passesDeltaRgammaElectrons photons
			    const PhotonCollection photonsMinuspassesDeltaRgammaElectrons = topEMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaElectrons");
			    photonAnalyserEMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaElectrons, jets, electrons, muons, "passesDeltaRgammaElectrons");

                            //n-passesDeltaRgammaJets photons
                            const PhotonCollection photonsMinuspassesDeltaRgammaJets = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRgammaJets");
                            photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRgammaJets, jets, electrons, muons, "passesDeltaRgammaJets");

                            //n-passesDeltaRjetsMuons photons
                            const PhotonCollection photonsMinuspassesDeltaRjetsMuons = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRjetsMuons");
                            photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRjetsMuons, jets, electrons, muons, "passesDeltaRjetsMuons");

                            //n-passesDeltaRjetsElectrons photons
                            const PhotonCollection photonsMinuspassesDeltaRjetsElectrons = topMuMuPhotonSelection_->nMinusOnePhotons(event, "passesDeltaRjetsElectrons");
                            photonAnalyserMuMuPhotonSelection_->analyse_NminusOnePhotons(event, photonsMinuspassesDeltaRjetsElectrons, jets, electrons, muons, "passesDeltaRjetsElectrons");
			}
	}
}

TTbarPhotonAnalyser::TTbarPhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
		BasicAnalyser(histMan, histogramFolder), //
		topMuMuPhotonSelection_(new TopPairMuMuReferenceSelection()),
		topEEPhotonSelection_(new TopPairEEReferenceSelection()),
		topEMuPhotonSelection_(new TopPairEMuReferenceSelection()),
		//signal regions MET
		metAnalyserMuMuPhotonSelection_(new METAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/MET")), //
		metAnalyserEEPhotonSelection_(new METAnalyser(histMan, histogramFolder + "/EE/Ref selection/MET")), //
		metAnalyserEMuPhotonSelection_(new METAnalyser(histMan, histogramFolder + "/EMu/Ref selection/MET")),//
		//signal regions MET
		jetAnalyserMuMuPhotonSelection_(new JetAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Jets")), //
		jetAnalyserEEPhotonSelection_(new JetAnalyser(histMan, histogramFolder + "/EE/Ref selection/Jets")), //
		jetAnalyserEMuPhotonSelection_(new JetAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Jets")),//
		//signal regions di electron
		diElectronAnalyserEEPhotonSelection_(new DiElectronAnalyser(histMan, histogramFolder + "/EE/Ref selection/DiLepton")), //
		diMuonAnalyserMuMuPhotonSelection_(new DiMuonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/DiLepton")), //
		eMuAnalyserEMuPhotonSelection_(new EMuAnalyser(histMan, histogramFolder + "/EMu/Ref selection/DiLepton")), //
		//signal regions Photons
		photonAnalyserMuMuPhotonSelection_(new PhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		photonAnalyserEEPhotonSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		photonAnalyserEMuPhotonSelection_(new PhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")),//
		//vertices
		//vertexAnalyserMuMuPhotonSelection_(new VertexAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Vertex")), //
		//vertexAnalyserEEPhotonSelection_(new VertexAnalyser(histMan, histogramFolder + "/EE/Ref selection/Vertex")), //
		//vertexAnalyserEMuPhotonSelection_(new VertexAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Vertex")),//
		//tt photon analyser
		ttphotonAnalyserMuMuPhotonSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		ttphotonAnalyserEEPhotonSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		ttphotonAnalyserEMuPhotonSelection_(new SignalPhotonAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons")) //
		//ABCD
		//abcdAnalyserMuMuPhotonSelection_(new ABCDAnalyser(histMan, histogramFolder + "/MuMu/Ref selection/Photons")), //
		//abcdAnalyserEEPhotonSelection_(new ABCDAnalyser(histMan, histogramFolder + "/EE/Ref selection/Photons")), //
		//abcdAnalyserEMuPhotonSelection_(new ABCDAnalyser(histMan, histogramFolder + "/EMu/Ref selection/Photons"))//
		{	

}

TTbarPhotonAnalyser::~TTbarPhotonAnalyser() {
}

void TTbarPhotonAnalyser::createHistograms() {

	//signal met
	metAnalyserMuMuPhotonSelection_->createHistograms();
	metAnalyserEEPhotonSelection_->createHistograms();
	metAnalyserEMuPhotonSelection_->createHistograms();
	//signal jets
	jetAnalyserMuMuPhotonSelection_->createHistograms();
	jetAnalyserEEPhotonSelection_->createHistograms();
	jetAnalyserEMuPhotonSelection_->createHistograms();
	//signal met di electron
	diElectronAnalyserEEPhotonSelection_->createHistograms();
	diMuonAnalyserMuMuPhotonSelection_->createHistograms();
	eMuAnalyserEMuPhotonSelection_->createHistograms();
	//signal photons
	photonAnalyserEEPhotonSelection_->createHistograms();
	photonAnalyserMuMuPhotonSelection_->createHistograms();
	photonAnalyserEMuPhotonSelection_->createHistograms();
	//vertices
//	vertexAnalyserMuMuPhotonSelection_->createHistograms();
//	vertexAnalyserEEPhotonSelection_->createHistograms();
//	vertexAnalyserEMuPhotonSelection_->createHistograms();
	//for ttbar
	ttphotonAnalyserMuMuPhotonSelection_->createHistograms();
	ttphotonAnalyserEEPhotonSelection_->createHistograms();
	ttphotonAnalyserEMuPhotonSelection_->createHistograms();
	//ABCD
	//abcdAnalyserEEPhotonSelection_->createHistograms();
	//abcdAnalyserMuMuPhotonSelection_->createHistograms();
	//abcdAnalyserEMuPhotonSelection_->createHistograms();

}

}
