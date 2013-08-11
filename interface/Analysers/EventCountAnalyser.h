/*
 * EventCountAnalyser.h
 *
 *  Created on: 24 Mar 2011
 *      Author: kreczko
 */

#ifndef EVENTCOUNTANALYSER_H_
#define EVENTCOUNTANALYSER_H_

#include "BasicAnalyser.h"

//DiLepton
#include "../Selections/TopPairMuMuReferenceSelection.h"
#include "../Selections/TopPairEEReferenceSelection.h"
#include "../Selections/TopPairEMuReferenceSelection.h"

namespace BAT {

class EventCountAnalyser: public BAT::BasicAnalyser {
public:
	EventCountAnalyser(HistogramManagerPtr histMan, std::string histogramFolder = "EventCount");
	virtual ~EventCountAnalyser();
	virtual void analyse(const EventPtr);
	virtual void createHistograms();
	void setHistogramLabels();

	void topMuMuReferenceSelection(const EventPtr event);
	void topMuMuReferenceSelectionUnweighted(const EventPtr event);
	void topEEReferenceSelection(const EventPtr event);
	void topEEReferenceSelectionUnweighted(const EventPtr event);
	void topEMuReferenceSelection(const EventPtr event);
	void topEMuReferenceSelectionUnweighted(const EventPtr event);
	
	void individualCuts(const EventPtr event);

private:
	//dilepton
	SelectionPointer topMuMuRefSelection_;
	SelectionPointer topEERefSelection_;
	SelectionPointer topEMuRefSelection_;

};

} /* namespace BAT */
#endif /* EVENTCOUNTANALYSER_H_ */

