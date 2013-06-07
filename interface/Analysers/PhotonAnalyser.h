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
	void analyse(const EventPtr);
	void analyseMuMu(const EventPtr);
	void analyseEE(const EventPtr);
//	void analyseEMu(const EventPtr);
	/**
	 * Analyses a single photon
	 */
	void analysePhoton(const EventPtr);
	void createHistograms();
	void useTTbarPlusMETSetup(bool use);
	
private:
	SelectionPointer topMuMuRefSelection_;
	SelectionPointer topEERefSelection_;
//	SelectionPointer topEMuRefSelection_;
	bool ttbarPlusMETAnalysisSetup_;
	
};
typedef boost::scoped_ptr<PhotonAnalyser> PhotonAnalyserLocalPtr;
typedef boost::shared_ptr<PhotonAnalyser> PhotonAnalyserPtr;
}

#endif /* PHOTONANALYSER_H_ */
