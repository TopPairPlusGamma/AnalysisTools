/*
 * ABCDAnalyser.h
 *
 *  Created on: 29th April 2014
 *      Author: N. Berry
 */

#ifndef ABCDANALYSER_H_
#define ABCDANALYSER_H_
#include "BasicAnalyser.h"
#include "../Selections/TopPairMuMuReferenceSelection.h"
#include "../Selections/TopPairEEReferenceSelection.h"
#include "../Selections/TopPairEMuReferenceSelection.h"
#include "../Selections/BasicSelection.h"
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace BAT {

//create class ABCDAnalyser which inherits from BasicAnalyser
class ABCDAnalyser : public BasicAnalyser {

//constructor; takes as arguments: the histogram manager and histogram folder previously created.
public:
	ABCDAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "ABCDAnalysis");
	virtual ~ABCDAnalyser();
	//analyse function: takes as arguments: constant event pointer to a particular event and reads its content. Carried out once for each event.
	void analyse(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons);
	void analyse(const EventPtr);
	void analyse_signalPhotons(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons);
//	void analyse_NminusOnePhotons(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons, TString cut);
	void createHistograms();
//	void createHistograms(TString cut);

private:
	//signal selections
	SelectionPointer topMuMuRefSelection_;
        SelectionPointer topEERefSelection_;
        SelectionPointer topEMuRefSelection_;
};

typedef boost::scoped_ptr<ABCDAnalyser> ABCDAnalyserLocalPtr;
typedef boost::shared_ptr<ABCDAnalyser> ABCDAnalyserPtr;
}

#endif /* ABCDANALYSER_H_ */
