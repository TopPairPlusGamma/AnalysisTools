/*
 * TTbarDiLeptonAnalyser.h
 *
 *  Created on: 10 Aug 2013
 *      Author: phil
 */

#ifndef TTBARDILEPTONANALYSER_H_
#define TTBARDILEPTONANALYSER_H_

#include "BasicAnalyser.h"
#include "METAnalyser.h"
#include "DiElectronAnalyser.h"
#include "DiMuonAnalyser.h"
#include "EMuAnalyser.h"
#include "ElectronAnalyser.h"
#include "MuonAnalyser.h"
#include "PhotonAnalyser.h"
#include "SignalPhotonAnalyser.h"
#include "VertexAnalyser.h"
#include "JetAnalyser.h"
#include "../Selections/BasicSelection.h"

#include <string>

namespace BAT {

class TTbarDiLeptonAnalyser: public BAT::BasicAnalyser {
public:
	TTbarDiLeptonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "TTbarDiLeptonAnalysis");
	virtual ~TTbarDiLeptonAnalyser();
	virtual void analyse(const EventPtr);
	virtual void createHistograms();

	void muMuSignalAnalysis(const EventPtr);
	void eESignalAnalysis(const EventPtr);
	void eMuSignalAnalysis(const EventPtr);

private:
	//signal selections
	SelectionPointer topMuMuRefSelection_, topEERefSelection_, topEMuRefSelection_;

	//signal region
	METAnalyserLocalPtr metAnalyserMuMuRefSelection_, metAnalyserEERefSelection_, metAnalyserEMuRefSelection_;

	JetAnalyserLocalPtr jetAnalyserMuMuRefSelection_, jetAnalyserEERefSelection_, jetAnalyserEMuRefSelection_;

	DiElectronAnalyserLocalPtr diElectronAnalyserEERefSelection_;
	DiMuonAnalyserLocalPtr diMuonAnalyserMuMuRefSelection_;
	EMuAnalyserLocalPtr eMuAnalyserEMuRefSelection_;

	//photon anlyser
	PhotonAnalyserLocalPtr photonAnalyserMuMuRefSelection_, photonAnalyserEERefSelection_, photonAnalyserEMuRefSelection_;

	//ttphoton anlyser
	SignalPhotonAnalyserLocalPtr ttphotonAnalyserMuMuRefSelection_, ttphotonAnalyserEERefSelection_, ttphotonAnalyserEMuRefSelection_;

};

typedef boost::scoped_ptr<BAT::TTbarDiLeptonAnalyser> TTbarDiLeptonAnalyserLocalPtr;
} /* namespace BAT */
#endif /* TTBARDILEPTONANALYSER_H_ */
