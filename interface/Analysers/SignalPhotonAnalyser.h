/*
 * SignalPhotonAnalyser.h
 *  Created on: 26 April 2013
 *      Author: N.Berry
 */

#ifndef SIGNALPHOTONANALYSER_H_
#define SIGNALPHOTONANALYSER_H_
#include "BasicAnalyser.h"
#include <boost/shared_ptr.hpp>
#include "../Selections/BasicSelection.h"

namespace BAT {

class SignalPhotonAnalyser: public BasicAnalyser {
public:
	SignalPhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "PhotonAnalysis");
	virtual ~SignalPhotonAnalyser();
	/**
	 * Analyses all photons in an event
	 */
	void analyse(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons);
	void analyse(const EventPtr);
	void analyse_signalPhotons(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons);
	void createHistograms();

private:
 	SelectionPointer topMuMuRefSelection_;
 	SelectionPointer topEERefSelection_;
 	SelectionPointer topEMuRefSelection_;

};
typedef boost::scoped_ptr<SignalPhotonAnalyser> SignalPhotonAnalyserLocalPtr;
typedef boost::shared_ptr<SignalPhotonAnalyser> SignalPhotonAnalyserPtr;
}

#endif /* PHOTONANALYSER_H_ */
