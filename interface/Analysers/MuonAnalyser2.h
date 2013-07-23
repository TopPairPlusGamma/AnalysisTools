/*
 * MuonAnalyser2.h
 *
 *  Created on: 9 July 2013
 *      Author: N.Berry
 */

#ifndef MUONANALYSER2_H_
#define MUONANALYSER2_H_
#include "BasicAnalyser.h"
#include "../Selections/BasicSelection.h"
#include <boost/shared_ptr.hpp>

namespace BAT {

class MuonAnalyser2: public BasicAnalyser {
public:
	MuonAnalyser2(HistogramManagerPtr histMan, std::string histogramFolder = "PhotonAnalysis");
	virtual ~MuonAnalyser2();

	/**
	 * Analyses all muons in an event
	 */
	void analyse(const EventPtr);
	void analyseAllMuons(const EventPtr);
	void analyseSignalMuons(const EventPtr);
	/**
	 * Analyses a single muon
	 */
	void createHistograms();

	void useTTbarPlusMETSetup(bool use);
	
private:
	SelectionPointer topMuMuRefSelection_;
	bool ttbarPlusMETAnalysisSetup_;
};
typedef boost::scoped_ptr<MuonAnalyser2> MuonAnalyser2LocalPtr;
typedef boost::shared_ptr<MuonAnalyser2> MuonAnalyser2Ptr;
}

#endif /* MUONANALYSER2_H_ */
