/*
 * TTbarPhotonAnalyser.h
 *
 *  Created on: 10 Aug 2013
 *      Author: phil
 */

#ifndef TTBARPHOTONANALYSER_H_
#define TTBARPHOTONANALYSER_H_

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
#include "ABCDAnalyser.h"
#include "../Selections/BasicSelection.h"

#include <string>

namespace BAT {

class TTbarPhotonAnalyser: public BAT::BasicAnalyser {
public:
	TTbarPhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "TTbarPhotonAnalysis");
	virtual ~TTbarPhotonAnalyser();
	virtual void analyse(const EventPtr);
	virtual void createHistograms();
	void muMuSignalAnalysis(const EventPtr);
	void eESignalAnalysis(const EventPtr);
	void eMuSignalAnalysis(const EventPtr);

private:
	//signal selections
	SelectionPointer topMuMuPhotonSelection_, topEEPhotonSelection_, topEMuPhotonSelection_;

	//signal region
	METAnalyserLocalPtr metAnalyserMuMuPhotonSelection_, metAnalyserEEPhotonSelection_, metAnalyserEMuPhotonSelection_;

	JetAnalyserLocalPtr jetAnalyserMuMuPhotonSelection_, jetAnalyserEEPhotonSelection_, jetAnalyserEMuPhotonSelection_;

	DiElectronAnalyserLocalPtr diElectronAnalyserEEPhotonSelection_;
	DiMuonAnalyserLocalPtr diMuonAnalyserMuMuPhotonSelection_;
	EMuAnalyserLocalPtr eMuAnalyserEMuPhotonSelection_;

	//photon anlyser
	PhotonAnalyserLocalPtr photonAnalyserMuMuPhotonSelection_, photonAnalyserEEPhotonSelection_, photonAnalyserEMuPhotonSelection_;

	//ttphoton anlyser
	SignalPhotonAnalyserLocalPtr ttphotonAnalyserMuMuPhotonSelection_, ttphotonAnalyserEEPhotonSelection_, ttphotonAnalyserEMuPhotonSelection_;

	//Vertex analyser
 	//  VertexAnalyserLocalPtr vertexAnalyserMuMuPhotonSelection_, vertexAnalyserEEPhotonSelection_, vertexAnalyserEMuPhotonSelection_;

	//ABCD Analyser
	//ABCDAnalyserLocalPtr abcdAnalyserMuMuPhotonSelection_, abcdAnalyserEEPhotonSelection_, abcdAnalyserEMuPhotonSelection_;
 
};

typedef boost::scoped_ptr<BAT::TTbarPhotonAnalyser> TTbarPhotonAnalyserLocalPtr;
} /* namespace BAT */
#endif /* TTBARPHOTONANALYSER_H_ */
