
#ifndef EMUANALYSER_H_
#define EMUANALYSER_H_

#include "BasicAnalyser.h"
#include "../../interface/TopPairEventCandidate.h"
#include "../../interface/HistHelpers/HistogramManager.h"

namespace BAT {

class EMuAnalyser: public BAT::BasicAnalyser {
public:
	EMuAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "EMuAnalysis");
	virtual ~EMuAnalyser();

	void analyse(const EventPtr);
    void analyse(const EventPtr, const ElectronCollection, const MuonCollection);
    void createHistograms();
};

typedef boost::scoped_ptr<EMuAnalyser> EMuAnalyserLocalPtr;

}

#endif /* EMUANALYSER_H_ */
