/*
 * PhotonAnalyser.h
 *  Created on: 26 April 2013
 *      Author: N.Berry
 */

#ifndef PHOTONANALYSER_H_
#define PHOTONANALYSER_H_
#include "BasicAnalyser.h"
#include <boost/shared_ptr.hpp>
#include "../Selections/BasicSelection.h"

namespace BAT {

class PhotonAnalyser: public BasicAnalyser {
public:
	PhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "PhotonAnalysis");
	virtual ~PhotonAnalyser();
	/**
	 * Analyses all photons in an event
	 */
	void analyse(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons);
	void analyse(const EventPtr);
	void analyse_signalPhotons(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons);
	void analyse_NminusOnePhotons(const EventPtr, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons, TString cut);
	void createHistograms();
	void createHistograms(TString cut);

private:
 	SelectionPointer topMuMuRefSelection_;
 	SelectionPointer topEERefSelection_;
 	SelectionPointer topEMuRefSelection_;
	
};
typedef boost::scoped_ptr<PhotonAnalyser> PhotonAnalyserLocalPtr;
typedef boost::shared_ptr<PhotonAnalyser> PhotonAnalyserPtr;
}

#endif /* PHOTONANALYSER_H_ */
