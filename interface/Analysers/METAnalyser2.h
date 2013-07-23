/*
 * METAnalyser2.h
 *
 *  Created on: 9 July 2013
 *      Author: N.Berry
 */

#ifndef METANALYSER2_H_
#define METANALYSER2_H_

#include "BasicAnalyser.h"
#include "../RecoObjects/MET.h"
#include "../RecoObjects/Particle.h"
#include "../RecoObjects/Jet.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../Selections/BasicSelection.h"
#include <boost/shared_ptr.hpp>

namespace BAT {

class METAnalyser2: public BAT::BasicAnalyser {
public:
	METAnalyser2(HistogramManagerPtr histMan, std::string histogramFolder = "PhotonAnalysis");
	virtual ~METAnalyser2();
	void analyse(const EventPtr);
	void analyseMET(const EventPtr);
//	void analyse(const EventPtr, const ParticlePointer, const JetCollection);

	void createHistograms();
	void useTTbarPlusMETSetup(bool use);
	
protected:
//	void analyseTransverseMass(const EventPtr, const ParticlePointer);
//	void analyse_ST(const EventPtr, const ParticlePointer, const JetCollection);
//	void analyse_HT(const EventPtr, const JetCollection);

private:
	SelectionPointer topMuMuRefSelection_;
	bool ttbarPlusMETAnalysisSetup_;

};

typedef boost::scoped_ptr<METAnalyser2> METAnalyser2LocalPtr;
typedef boost::shared_ptr<METAnalyser2> METAnalyser2Ptr;

} /* namespace BAT */
#endif /* METANALYSER2_H_ */
