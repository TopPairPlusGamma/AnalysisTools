/*
 *  ABCDAnalyser.cpp
 *
 *  Created on: 29th Aril 2014
 *      Author: N.Berry
 */
 
#include "../../interface/Analysers/ABCDAnalyser.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"                                                                                                                
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"
#include "../../interface/Selections/BasicSelection.h"
#include "TLatex.h"
 
namespace BAT {

void ABCDAnalyser::analyse(const EventPtr event, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons){

	//all photons
        analyse(event);
        //signal photons
        analyse_signalPhotons(event, signalPhotons, cleanJets, signalElectrons, signalMuons);

}

void ABCDAnalyser::analyse(const EventPtr event) {

	double weight_ = event->weight() * prescale_ * scale_;
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ABCD_all");
	
	const PhotonCollection photons = event->Photons();
	const JetCollection jets = event->Jets();
        const ElectronCollection electrons = event->Electrons();
        const MuonCollection muons = event->Muons();
	const METPointer met = event->MET();

	// want the event to pass the selection steps up to DiLeptonVeto (including OneIsolatedElectron which we want) - from BasicSelection.cpp
	//also want the event to pass the selection step of at least 4 good jets
//	bool passesSelection = topMuMuRefSelection_->passesSelectionUpToStep(event, TTbarMuMuReferenceSelection::AtLeastOnePhotonPostSelection);
	
//	if (passesSelection) {
//		const JetCollection jets(topMuMuRefSelection_->cleanedJets(event));
//		const JetCollection bJets(topMuMuRefSelection_->cleanedBJets(event));
//		const PhotonCollection photons = topMuMuRefSelection_->signalPhotons(event);
//		histMan_->setCurrentJetBin(jets.size());
//		histMan_->setCurrentBJetBin(bJets.size());
//		const LeptonPointer signalLepton = topMuMuRefSelection_->signalPhotons(event); 
//		const ElectronPointer electron(boost::static_pointer_cast<Electron>(signalLepton));
//		double pfiso = electron->pfRelativeIsolation(); //removed 0.3 from brackets
//		double electronIDMVA = electron->mvaTrigV0();

//		histMan_->H2D_BJetBinned("Particle_Flow_Isolation_v._Missing_Transverse_Energy")->Fill(met->et(), pfiso, weight);
//		histMan_->H2D_BJetBinned("ElectronID_MVA_v._Missing_Transverse_Energy")->Fill(met->et(), electronIDMVA, weight);
//		histMan_->H2D_BJetBinned("Particle_Flow_Isolation_v._ElectronID_MVA")->Fill(electronIDMVA, pfiso, weight);


	for (unsigned int index = 0; index < photons.size(); ++index) {
		const PhotonPointer photon(photons.at(index));
		
		if(photon->isInBarrelRegion()) {
		
			histMan_->H2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta")->Fill(photon->RhoCorrectedSCChIso(event->rho()), photon->sigmaIEtaIEta(), weight_);
		
		}
		
		if(photon->isInEndCapRegion()) {
		
			histMan_->H2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta")->Fill(photon->RhoCorrectedSCChIso(event->rho()), photon->sigmaIEtaIEta(), weight_);
		
		}
		
			histMan_->H2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta")->Fill(photon->RhoCorrectedSCChIso(event->rho()), photon->sigmaIEtaIEta(), weight_);

	}

}

void ABCDAnalyser::analyse_signalPhotons(const EventPtr event, PhotonCollection signalPhotons, JetCollection jets, ElectronCollection electrons, MuonCollection muons) {

	double weight_ = event->weight() * prescale_ * scale_;
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ABCD_signal");
	

	for (unsigned int index = 0; index < signalPhotons.size(); ++index) {
		const PhotonPointer photon(signalPhotons.at(index));
		
		if(photon->isInBarrelRegion()) {
		
			histMan_->H2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta")->Fill(photon->RhoCorrectedSCChIso(event->rho()), photon->sigmaIEtaIEta(), weight_);
		
		}
		
		if(photon->isInEndCapRegion()) {
		
			histMan_->H2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta")->Fill(photon->RhoCorrectedSCChIso(event->rho()), photon->sigmaIEtaIEta(), weight_);
		
		}
		
			histMan_->H2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta")->Fill(photon->RhoCorrectedSCChIso(event->rho()), photon->sigmaIEtaIEta(), weight_);

	}
}


void ABCDAnalyser::createHistograms() {
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ABCDall");

		histMan_->addH2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta","RhoCorrectedSCFRChIso_v._Sigma_ietaieta", 200, 0, 20, 200, 0, 20);
			
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ABCD_signal");
		
		histMan_->addH2D_BJetBinned("RhoCorrectedSCFRChIso_v._Sigma_ietaieta","RhoCorrectedSCFRChIso_v._Sigma_ietaieta", 200, 0, 20, 200, 0, 20);

}

} //end namespace BAT
