/*
 * TopPairMuPlusJetsPlusMETSelection.cpp
 *
 *  Created on: 11 Mar 2013
 *      Author: Nicko the sicko
 */
/*
#include "../../interface/Selections/TopPairMuPlusJetsRefAsymJetsSelection.h"

namespace BAT {

TopPairMuPlusJetsRefAsymJetsSelection::TopPairMuPlusJetsRefAsymJetsSelection(unsigned int numberOfSelectionSteps) :
		TopPairMuPlusJetsReferenceSelection(numberOfSelectionSteps) {

}

TopPairMuPlusJetsRefAsymJetsSelection::~TopPairMuPlusJetsRefAsymJetsSelection() {
}

bool TopPairMuPlusJetsRefAsymJetsSelection::passesSelectionStep(const EventPtr event, unsigned int selectionStep) const {
	if (selectionStep <= TTbarMuPlusJetsRefAsymJetsSelection::AtLeastFourGoodJets) {
		return TopPairMuPlusJetsReferenceSelection::passesSelectionStep(event, selectionStep);
	} else if (selectionStep == TTbarMuPlusJetsRefAsymJetsSelection::AsymmetricJetCuts) {
		return passesAsymmetricJetCuts(event);
	} else if (selectionStep == TTbarMuPlusJetsRefAsymJetsSelection::AtLeastOneBtag) {
		return hasAtLeastOneGoodBJet(event);
	} else if (selectionStep == TTbarMuPlusJetsRefAsymJetsSelection::AtLeastTwoBtags) {
		return hasAtLeastTwoGoodBJets(event);
	}

	return false;
}

bool TopPairMuPlusJetsRefAsymJetsSelection::passesAsymmetricJetCuts(const EventPtr event) const {
	const JetCollection goodElectronCleanedJets = cleanedJets(event);
	if (goodMuonCleanedJets.size() < 3) // good jets have a cut of 30 GeV!
		return false;
	JetPointer leadingJet = goodMuonCleanedJets.front();
	JetPointer secondLeadingJet = goodMuonCleanedJets.at(1);
	JetPointer thirdLeadingJet = goodMuonCleanedJets.at(2);
	return leadingJet->pt() > 70 && secondLeadingJet->pt() > 50 && thirdLeadingJet->pt() > 50;
}

} /* namespace BAT */
