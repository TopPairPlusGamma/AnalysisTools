/*
 * Analysis.cpp
 *
 *  Created on: 12 Jul 2010
 *      Author: kreczko
 */

#include "Analysis.h"
#include "TROOT.h"
#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>
#include "../interface/EventCounter.h"
#include <cmath>
#include <math.h>
#include "../interface/Printers/EventTablePrinter.h"
#include "../interface/ReconstructionModules/ChiSquaredBasedTopPairReconstruction.h"
#include "../interface/LumiReWeighting.h"
#include "../interface/GlobalVariables.h"
#include "../interface/BTagWeight.h"

using namespace reweight;
using namespace BAT;
using namespace std;

void Analysis::analyse() {
	createHistograms();
	cout << "detected samples:" << endl;
	for (unsigned int sample = 0; sample < DataType::NUMBER_OF_DATA_TYPES; ++sample) {
		if (eventReader->getSeenDatatypes()[sample])
			cout << DataType::names[sample] << endl;
	}
	while (eventReader->hasNextEvent()) {
		initiateEvent();
		printNumberOfProccessedEventsEvery(Globals::printEveryXEvents);
		inspectEvents();

		const JetCollection jets(currentEvent->Jets());
		unsigned int numberOfJets(jets.size());
		unsigned int numberOfBJets(0);
		for (unsigned int index = 0; index < numberOfJets; ++index) {
			const JetPointer jet(currentEvent->Jets().at(index));
			if (jet->isBJet(BtagAlgorithm::CombinedSecondaryVertex, BtagAlgorithm::MEDIUM))
				++numberOfBJets;
		}
		histMan->setCurrentBJetBin(numberOfBJets);
		histMan->setCurrentJetBin(numberOfJets);

		vector<double> bjetWeights;
		if (currentEvent->isRealData()) {
			for (unsigned int index = 0; index <= numberOfBJets; ++index) {
				if (index == numberOfBJets)
					bjetWeights.push_back(1.);
				else
					bjetWeights.push_back(0);
			}
		} else
			bjetWeights = BjetWeights(jets, numberOfBJets);

		eventcountAnalyser->analyse(currentEvent);
		ttbardileptonAnalyser->analyse(currentEvent);
		ttbarphotonAnalyser->analyse(currentEvent);

	}
}

void Analysis::printNumberOfProccessedEventsEvery(unsigned long printEvery) {
	unsigned long eventIndex = eventReader->getNumberOfProccessedEvents();
	if (eventIndex % printEvery == 0 || eventIndex == 1) {
		cout << "Analysing event no " << eventIndex << ", sample: " << DataType::names[currentEvent->getDataType()]
				<< endl;
		cout << "File: " << eventReader->getCurrentFile() << endl;
	}

}

void Analysis::initiateEvent() {
	currentEvent = eventReader->getNextEvent();
	weight = 1.;

	if (!currentEvent->isRealData()) {
		weight = weights->getWeight(currentEvent->getDataType());
		//TODO: fix this dirty little thing
		pileUpWeight = weights->reweightPileUp(currentEvent->getTrueNumberOfVertices().at(1));
		weight *= pileUpWeight;
		if (Globals::pdfWeightNumber != 0) {
			try {
				weight *= currentEvent->PDFWeights().at(Globals::pdfWeightNumber) / currentEvent->PDFWeights().at(0);
			} catch (exception& e) {
				cout << "PDF weight assigning exception: " << e.what() << endl;
			}
		}
	}
	
	
	//top pt weight
  	if(Globals::applyTopPtReweighting == true && (currentEvent->getDataType() == DataType::TTJets || currentEvent->getDataType() == DataType::TTGamma)){

 	   double topPtweight = 1.;
  	   topPtweight = weights->reweightTopPt(currentEvent);

 	   weight *= topPtweight; //topptreweight/number of events and then divide by this to correct for top pt reweight
 	}


	currentEvent->setEventWeight(weight);
	currentEvent->setPileUpWeight(pileUpWeight);

	histMan->setCurrentDataType(currentEvent->getDataType());
	histMan->setCurrentJetBin(currentEvent->Jets().size());
	histMan->setCurrentBJetBin(0);
}

void Analysis::inspectEvents() {
	std::vector<InterestingEvent> eventsToInspect;

	for (unsigned int index = 0; index < eventsToInspect.size(); ++index) {
		if ((currentEvent->runnumber() == eventsToInspect.at(index).candidate->runnumber()
				&& currentEvent->eventnumber() == eventsToInspect.at(index).candidate->eventnumber())) {
			cout << "file: " << eventReader->getCurrentFile() << endl;
			currentEvent->inspect();
		}
	}

}

void Analysis::printInterestingEvents() {
	cout << "Interesting events:" << endl;
	for (unsigned int index = 0; index < interestingEvents.size(); ++index) {
		interestingEvents.at(index).print();
	}
}

void Analysis::printSummary() {
	cout << "total number of processed events: " << eventReader->getNumberOfProccessedEvents() << endl;
	cout << "number of events without electrons: " << brokenEvents.size() << endl;
	cout << "number of events with too high pileup: " << weights->getNumberOfEventsWithTooHighPileUp() << endl;
}

void Analysis::createHistograms() {
	histMan->prepareForSeenDataTypes(eventReader->getSeenDatatypes());
	unsigned int numberOfHistograms(0), lastNumberOfHistograms(0);

	eventcountAnalyser->createHistograms();
	numberOfHistograms = histMan->size();
	cout << "Number of histograms added by eventcountAnalyser: " << numberOfHistograms - lastNumberOfHistograms << endl;
	lastNumberOfHistograms = numberOfHistograms;

	ttbardileptonAnalyser->createHistograms();
        numberOfHistograms = histMan->size();
        cout << "Number of histograms added by ttbardileptonAnalyser: " << numberOfHistograms - lastNumberOfHistograms << endl;
        lastNumberOfHistograms = numberOfHistograms;

    ttbarphotonAnalyser->createHistograms();
        numberOfHistograms = histMan->size();
        cout << "Number of histograms added by ttbarphotonAnalyser: " << numberOfHistograms - lastNumberOfHistograms << endl;
        lastNumberOfHistograms = numberOfHistograms;

	cout << "Total number of histograms: " << histMan->size() << endl;

}

Analysis::Analysis(std::string datasetInfoFile) : //
		eventReader(new NTupleEventReader()), //
		currentEvent(), //
		histMan(new BAT::HistogramManager()), //

		interestingEvents(), //
		brokenEvents(), //
		eventCheck(), //
		weights(new EventWeightProvider(datasetInfoFile)), //
		weight(0), //
		pileUpWeight(1), //

		bjetAnalyser(new BJetAnalyser(histMan)), //
		diElectronAnalyser(new DiElectronAnalyser(histMan)), //
		electronAnalyser(new ElectronAnalyser(histMan)), //
		eventcountAnalyser(new EventCountAnalyser(histMan)), //
//		hitfitAnalyser(new HitFitAnalyser(histMan)), //
		jetAnalyser(new JetAnalyser(histMan)), //
		mcAnalyser(new MCAnalyser(histMan)), //
		metAnalyser(new METAnalyser(histMan)), //
//  	muonAnalyser(new MuonAnalyser(histMan)), //
		mvAnalyser(new MVAnalyser(histMan)), //
		neutrinoRecoAnalyser(new NeutrinoReconstructionAnalyser(histMan)), //
		vertexAnalyser(new VertexAnalyser(histMan)),
		photonAnalyser(new PhotonAnalyser(histMan)),
		ttbardileptonAnalyser(new TTbarDiLeptonAnalyser(histMan)),
		ttbarphotonAnalyser(new TTbarPhotonAnalyser(histMan)){


	histMan->enableDebugMode(true);
}

Analysis::~Analysis() {

}

void Analysis::finishAnalysis() {
	printSummary();
	histMan->writeToDisk();
}

void Analysis::addInputFile(const char* fileName) {
	eventReader->addInputFile(fileName);
}

void Analysis::setMaximalNumberOfEvents(long maxEvents) {
	if (maxEvents > 0) {
		eventReader->setMaximumNumberOfEvents(maxEvents);
	}
}

void Analysis::checkForDuplicatedEvents() {
	map<unsigned long, std::vector<unsigned long> >::const_iterator iter;
	std::vector<pair<unsigned long, unsigned long> > duplicateEvents;

	for (iter = eventCheck.begin(); iter != eventCheck.end(); ++iter) {
		std::vector<unsigned long> events = (*iter).second;
		std::sort(events.begin(), events.end());
		for (unsigned long ev = 0; ev < events.size() - 1; ++ev) {
			if (events.at(ev) == events.at(ev + 1)) {
				duplicateEvents.push_back(make_pair((*iter).first, events.at(ev)));
			}
		}
	}

	if (duplicateEvents.size() > 0) {
		cout << "found duplicate events" << endl;
		for (unsigned long ev = 0; ev < duplicateEvents.size() - 1; ++ev) {
			cout << "run: " << duplicateEvents.at(ev).first << " event: " << duplicateEvents.at(ev).second << endl;
		}
	}
}

unsigned long Analysis::getNumberOfProccessedEvents() const {
	return eventReader->getNumberOfProccessedEvents();
}

