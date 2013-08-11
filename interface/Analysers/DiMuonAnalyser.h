#ifndef DIMUONANALYSER_H_
#define DIMUONANALYSER_H_

#include "BasicAnalyser.h"
#include "../../interface/TopPairEventCandidate.h"
#include "../../interface/HistHelpers/HistogramManager.h"

namespace BAT {

class DiMuonAnalyser: public BAT::BasicAnalyser {
public:
	DiMuonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "DiMuonAnalysis");
	virtual ~DiMuonAnalyser();

	void analyse(const EventPtr);
    void analyse(const EventPtr, const MuonCollection);
    void createHistograms();
};

typedef boost::scoped_ptr<DiMuonAnalyser> DiMuonAnalyserLocalPtr;

}

#endif /* DIMUONANALYSER_H_ */
