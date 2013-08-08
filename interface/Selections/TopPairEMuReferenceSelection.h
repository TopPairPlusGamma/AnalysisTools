 /*
  * TopPairEMuReferenceSelection.h
  *
  *  Created on: 30 May 2013
  *      Author: N.Berry
  */

#ifndef TopPairEMuReferenceSelection_H_
#define TopPairEMuReferenceSelection_H_

#include "BasicSelection.h"

namespace BAT {

namespace TTbarEMuReferenceSelection {
enum Step {
	EventCleaningAndTrigger,
	DiLeptonSelection,
	AtLeastOneGoodJets,
	AtLeastTwoGoodJets,
	AtLeastOneBtag,
	AtLeastOnePhoton,
	JustOneGoodPhoton,
	NUMBER_OF_SELECTION_STEPS
};

const std::string StringSteps[NUMBER_OF_SELECTION_STEPS] = { //
		"Event cleaning and High Level Trigger", //
				"di lepton selection", //
				">= 1 jets",
				">= 2 jets",
				">=1 CSV b-tag", //
				">=1 Photon",
				"==1 Photon"
		};
}

class TopPairEMuReferenceSelection: public BAT::BasicSelection {
public:
	TopPairEMuReferenceSelection(unsigned int numberOfSelectionSteps =
			TTbarEMuReferenceSelection::NUMBER_OF_SELECTION_STEPS);
	virtual ~TopPairEMuReferenceSelection();

	virtual bool isGoodJet(const JetPointer jet) const;
	virtual bool isBJet(const JetPointer jet) const;
	virtual bool isGoodMuon(const MuonPointer muon) const;
	virtual bool isGoodElectron(const ElectronPointer electron) const;
	virtual bool isGoodPhoton(const PhotonPointer photon, const EventPtr event) const;
	
	//definitions of loose objects
	virtual bool isLooseElectron(const ElectronPointer electron) const;
	virtual bool isLooseMuon(const MuonPointer electron) const;
	
	//isolation definitions
	virtual bool isIsolatedElectron(const LeptonPointer lepton) const;
	virtual bool isIsolatedMuon(const LeptonPointer lepton) const;
	
	virtual bool passesSelectionStep(const EventPtr event, unsigned int selectionStep) const;

	virtual bool passesEventCleaning(const EventPtr event) const;
	virtual bool passesTriggerSelection(const EventPtr event) const;
	virtual bool passesDiLeptonSelection(const EventPtr event) const;
	virtual bool passesZmassVeto(const EventPtr event) const;
	virtual bool hasAtLeastNGoodJets(const EventPtr event, int Njets) const;
	virtual bool hasAtLeastOneGoodBJet(const EventPtr event) const;
//	virtual bool hasAtLeastTwoGoodBJets(const EventPtr event) const;
	virtual bool passesMetCut(const EventPtr event) const;
	virtual bool hasAtLeastOneGoodPhoton(const EventPtr event) const;
	virtual bool hasJustOneGoodPhoton(const EventPtr event) const;

	virtual const LeptonPointer signalLepton(const EventPtr event) const;
	virtual const ElectronCollection signalElectrons(const EventPtr event) const;
	virtual const MuonCollection signalMuons(const EventPtr event) const;
//	virtual void signalLeptons(const EventPtr event);
	virtual const PhotonCollection signalPhotons(const EventPtr event) const;
	virtual const JetCollection cleanedJets(const EventPtr event) const;
	virtual const JetCollection cleanedBJets(const EventPtr event) const;
};

typedef boost::shared_ptr<TopPairEMuReferenceSelection> TopPairEMuReferenceSelectionPointer;

} /* namespace BAT */
#endif /* TopPairEMuReferenceSelection_H_ */
