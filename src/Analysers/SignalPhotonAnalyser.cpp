#include "../../interface/Analysers/SignalPhotonAnalyser.h"
#include "../../interface/GlobalVariables.h"
#include "../../interface/Selections/TopPairMuMuReferenceSelection.h"
#include "../../interface/Selections/TopPairEEReferenceSelection.h"
#include "../../interface/Selections/TopPairEMuReferenceSelection.h"

namespace BAT {

void SignalPhotonAnalyser::analyse(const EventPtr event, PhotonCollection signalPhotons, JetCollection cleanJets, ElectronCollection signalElectrons, MuonCollection signalMuons){

	//all photons
	analyse(event);
	//signal photons
	analyse_signalPhotons(event, signalPhotons, cleanJets, signalElectrons, signalMuons);

}

void SignalPhotonAnalyser::analyse(const EventPtr event){

	//const ElectronCollection electrons = topEERefSelection_->goodElectrons(event);
	//const MuonCollection muons = topMuMuRefSelection_->goodMuons(event);

	weight_ = event->weight() * prescale_ * scale_;
	const JetCollection jets = event->Jets();
	const ElectronCollection electrons = event->Electrons();
	const PhotonCollection photons = event->Photons();
	const MuonCollection muons = event->Muons();

	const MCParticleCollection genPart(event->GenParticles());
	
	unsigned int numberOfGenParts(genPart.size());
	int motherInd = 0;
		for (unsigned int i = 0; i < numberOfGenParts; i++) {

			// find photon
			if (abs(genPart.at(i)->pdgId()) == (22)){
				motherInd = genPart.at(genPart.at(i)->motherIndex())->pdgId();
				///cout << "found photon, mother is: " << genPart.at(genPart.at(i)->motherIndex())->pdgId() << endl;
				break;
			}
			//	&& abs(genPart.at(genPart.at(i)->motherIndex())->pdgId()) == (24))

		}

	
	if(abs(motherInd) == 6 || abs(motherInd) == 5 || abs(motherInd) == 24 || abs(motherInd) == 2212 || abs(motherInd) == 11 || abs(motherInd) == 13){
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttsigAllPhotons");
	}else if(abs(motherInd) == 11 || abs(motherInd) == 13){
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttlepAllPhotons");
	}else{
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttfakeAllPhotons");
	}

	histMan_->H1D_BJetBinned("Number_Of_Photons")->Fill(photons.size(), weight_);

	for (unsigned int index = 0; index < photons.size(); ++index) {
		const PhotonPointer photon(photons.at(index));
		histMan_->H1D_BJetBinned("Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("Photon_Phi")->Fill(photon->phi(), weight_);
		histMan_->H1D_BJetBinned("Photon_ET")->Fill(photon->et(), weight_);

		if (photon->isInEndCapRegion()){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_endcap")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCChIso_endcap")->Fill(photon->phoSCChIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCNuIso_endcap")->Fill(photon->phoSCNuIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCPhIso_endcap")->Fill(photon->phoSCPhIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap")->Fill(photon->RhoCorrectedSCChIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap")->Fill(photon->RhoCorrectedSCNuIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap")->Fill(photon->RhoCorrectedSCPhIso(event->rho()), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCChIso_barrel")->Fill(photon->phoSCChIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCNuIso_barrel")->Fill(photon->phoSCNuIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCPhIso_barrel")->Fill(photon->phoSCPhIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel")->Fill(photon->RhoCorrectedSCChIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel")->Fill(photon->RhoCorrectedSCNuIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel")->Fill(photon->RhoCorrectedSCPhIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RandConeChIso_barrel")->Fill(photon->phoRandConeChIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RandConeNuIso_barrel")->Fill(photon->phoRandConeNuIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RandConePhIso_barrel")->Fill(photon->phoRandConePhIso(), weight_);
		}

		histMan_->H1D_BJetBinned("Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("Photon_EcalIso")->Fill(photon->ecalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso")->Fill(photon->hcalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso2012")->Fill(photon->hcalIsolation2012(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrckIso")->Fill(photon->trackerIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCeta")->Fill(photon->superClusterEta(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCphi")->Fill(photon->superClusterPhi(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCenergy")->Fill(photon->superClusterEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCSeedEnergy")->Fill(photon->superClusterSeedEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_E3x3")->Fill(photon->Ecal3x3Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_E5x5")->Fill(photon->Ecal5x5Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrkVeto")->Fill(photon->TrackVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_ConvSEVeto")->Fill(photon->ConversionSafeElectronVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_HtowoE")->Fill(photon->SingleTowerHoE(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso")->Fill(photon->PFChargedHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso")->Fill(photon->PFNeutralHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFPhotonIso")->Fill(photon->PFPhotonIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCChIso")->Fill(photon->phoSCChIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCNuIso")->Fill(photon->phoSCNuIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCPhIso")->Fill(photon->phoSCPhIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RandConeChIso")->Fill(photon->phoRandConeChIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RandConeNuIso")->Fill(photon->phoRandConeNuIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RandConePhIso")->Fill(photon->phoRandConePhIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCChIso")->Fill(photon->RhoCorrectedSCChIso(event->rho()), weight_);
		histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCNuIso")->Fill(photon->RhoCorrectedSCNuIso(event->rho()), weight_);
		histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCPhIso")->Fill(photon->RhoCorrectedSCPhIso(event->rho()), weight_);

		for (unsigned int index = 0; index < jets.size(); ++index) {
			const JetPointer jet(jets.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_jets")->Fill(photon->deltaR(jet), weight_);
		}

		for (unsigned int index = 0; index < electrons.size(); ++index) {
			const ElectronPointer electron(electrons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_electrons")->Fill(photon->deltaR(electron), weight_);
		}

		for (unsigned int index = 0; index < muons.size(); ++index) {
			const MuonPointer muon(muons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_muons")->Fill(photon->deltaR(muon), weight_);
		}
	}

}

void SignalPhotonAnalyser::analyse_signalPhotons(const EventPtr event, PhotonCollection signalPhotons, JetCollection jets, ElectronCollection electrons, MuonCollection muons){

//	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/SignalPhotons");

	//const ElectronCollection electrons = topMuMuRefSelection_->goodElectrons(event);
	//const MuonCollection muons = topMuMuRefSelection_->goodMuons(event);

	weight_ = event->weight() * prescale_ * scale_;
//	const JetCollection jets = event->Jets();
//	const ElectronCollection electrons = event->Electrons();
//	const MuonCollection muons = event->Muons();

	const MCParticleCollection genPart(event->GenParticles());
	
	unsigned int numberOfGenParts(genPart.size());
	int motherInd = 0;
	MCParticlePointer phoMother;
	MCParticleCollection phoMothers;
	MCParticleCollection genPhotons;
	
		for (unsigned int i = 0; i < numberOfGenParts; i++) {

			// find photon
			if (abs(genPart.at(i)->pdgId()) == (22) && !event->isRealData()){
			
				const MCParticlePointer phoMother(genPart.at(genPart.at(i)->motherIndex()));
				phoMothers.push_back(phoMother);
//				cout << "The number of photon mothers is " << phoMothers.size() << endl;
				
				motherInd = genPart.at(genPart.at(i)->motherIndex())->pdgId();
//				cout << "found photon, mother is: " << genPart.at(genPart.at(i)->motherIndex())->pdgId() << endl;
				
				const MCParticlePointer genPhoton(genPart.at(i));
				genPhotons.push_back(genPhoton);
				//cout << "Number of generated photons = " << genPhotons.size() << endl;
			
			
			}
			//	&& abs(genPart.at(genPart.at(i)->motherIndex())->pdgId()) == (24))
			

		}
		

	if(abs(motherInd) == 6 || abs(motherInd) == 5 || abs(motherInd) == 24 || abs(motherInd) == 2212 || abs(motherInd) == 11 || abs(motherInd) == 13 ){
		histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttsigSignalPhotons");
	}else if(abs(motherInd) == 11 || abs(motherInd) == 13){
		histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttlepSignalPhotons");
	}else{
		histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttfakeSignalPhotons");
	}


	histMan_->H1D_BJetBinned("Number_Of_Photons")->Fill(signalPhotons.size(), weight_);

	for (unsigned int index = 0; index < signalPhotons.size(); ++index) {
		const PhotonPointer photon(signalPhotons.at(index));
		histMan_->H1D_BJetBinned("Photon_Pt")->Fill(photon->pt(), weight_);
		histMan_->H1D_BJetBinned("Photon_Eta")->Fill(photon->eta(), weight_);
		histMan_->H1D_BJetBinned("Photon_AbsEta")->Fill(fabs(photon->eta()), weight_);
		histMan_->H1D_BJetBinned("Photon_Phi")->Fill(photon->phi(), weight_);
		histMan_->H1D_BJetBinned("Photon_ET")->Fill(photon->et(), weight_);

		if (photon->isInEndCapRegion()){
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_endcap")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCChIso_endcap")->Fill(photon->phoSCChIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCNuIso_endcap")->Fill(photon->phoSCNuIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCPhIso_endcap")->Fill(photon->phoSCPhIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap")->Fill(photon->RhoCorrectedSCChIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap")->Fill(photon->RhoCorrectedSCNuIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap")->Fill(photon->RhoCorrectedSCPhIso(event->rho()), weight_);
		} else if (photon->isInBarrelRegion()) {
			histMan_->H1D_BJetBinned("Photon_sigma_ietaieta_barrel")->Fill(photon->sigmaIEtaIEta(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_PFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel")->Fill(photon->PFChargedHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel")->Fill(photon->PFNeutralHadronIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel")->Fill(photon->PFPhotonIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCChIso_barrel")->Fill(photon->phoSCChIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCNuIso_barrel")->Fill(photon->phoSCNuIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_SCPhIso_barrel")->Fill(photon->phoSCPhIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel")->Fill(photon->RhoCorrectedSCChIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel")->Fill(photon->RhoCorrectedSCNuIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel")->Fill(photon->RhoCorrectedSCPhIso(event->rho()), weight_);
			histMan_->H1D_BJetBinned("Photon_RandConeChIso_barrel")->Fill(photon->phoRandConeChIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RandConeNuIso_barrel")->Fill(photon->phoRandConeNuIso(), weight_);
			histMan_->H1D_BJetBinned("Photon_RandConePhIso_barrel")->Fill(photon->phoRandConePhIso(), weight_);
		}

		histMan_->H1D_BJetBinned("Photon_HadOverEM")->Fill(photon->HadOverEm(), weight_);
		histMan_->H1D_BJetBinned("Photon_EcalIso")->Fill(photon->ecalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso")->Fill(photon->hcalIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_HcalIso2012")->Fill(photon->hcalIsolation2012(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrckIso")->Fill(photon->trackerIsolation(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCeta")->Fill(photon->superClusterEta(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCphi")->Fill(photon->superClusterPhi(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCenergy")->Fill(photon->superClusterEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCSeedEnergy")->Fill(photon->superClusterSeedEnergy(), weight_);
		histMan_->H1D_BJetBinned("Photon_E3x3")->Fill(photon->Ecal3x3Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_E5x5")->Fill(photon->Ecal5x5Cluster(), weight_);
		histMan_->H1D_BJetBinned("Photon_TrkVeto")->Fill(photon->TrackVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_ConvSEVeto")->Fill(photon->ConversionSafeElectronVeto(), weight_);
		histMan_->H1D_BJetBinned("Photon_HtowoE")->Fill(photon->SingleTowerHoE(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFChargedHadronIso")->Fill(photon->PFChargedHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFNeutralHadronIso")->Fill(photon->PFNeutralHadronIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_PFPhotonIso")->Fill(photon->PFPhotonIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCChIso")->Fill(photon->phoSCChIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCNuIso")->Fill(photon->phoSCNuIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_SCPhIso")->Fill(photon->phoSCPhIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RandConeChIso")->Fill(photon->phoRandConeChIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RandConeNuIso")->Fill(photon->phoRandConeNuIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RandConePhIso")->Fill(photon->phoRandConePhIso(), weight_);
		histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCChIso")->Fill(photon->RhoCorrectedSCChIso(event->rho()), weight_);
		histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCNuIso")->Fill(photon->RhoCorrectedSCNuIso(event->rho()), weight_);
		histMan_->H1D_BJetBinned("Photon_RhoCorrectedSCPhIso")->Fill(photon->RhoCorrectedSCPhIso(event->rho()), weight_);

		for (unsigned int index = 0; index < jets.size(); ++index) {
			const JetPointer jet(jets.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_jets")->Fill(photon->deltaR(jet), weight_);
		}

		for (unsigned int index = 0; index < electrons.size(); ++index) {
			const ElectronPointer electron(electrons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_electrons")->Fill(photon->deltaR(electron), weight_);
		}

		for (unsigned int index = 0; index < muons.size(); ++index) {
			const MuonPointer muon(muons.at(index));
			histMan_->H1D_BJetBinned("Photon_deltaR_muons")->Fill(photon->deltaR(muon), weight_);
		}
	}
}

SignalPhotonAnalyser::SignalPhotonAnalyser(HistogramManagerPtr histMan, std::string histogramFolder) :
                BasicAnalyser(histMan, histogramFolder) { //
}


SignalPhotonAnalyser::~SignalPhotonAnalyser(){
}

void SignalPhotonAnalyser::createHistograms() {

	histMan_->setCurrentHistogramFolder(histogramFolder_+"/ttsigAllPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_barrel", "SCFR Charged Hadron Iso (barrel); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_barrel", "SCFR Neutral Hadron Iso (barrel); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_barrel", "SCFR Photon Iso (barrel); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_endcap", "SCFR Charged Hadron Iso (endcap); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_endcap", "SCFR Neutral Hadron Iso (endcap); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_endcap", "SCFR Photon Iso (endcap); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso", "SCFR Charged Hadron Iso; ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso", "SCFR Neutral Hadron Iso; ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso", "SCFR Photon Iso; ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso_barrel", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso_barrel", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso_barrel", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	
	histMan_->setCurrentHistogramFolder(histogramFolder_+"/ttlepAllPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_barrel", "SCFR Charged Hadron Iso (barrel); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_barrel", "SCFR Neutral Hadron Iso (barrel); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_barrel", "SCFR Photon Iso (barrel); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_endcap", "SCFR Charged Hadron Iso (endcap); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_endcap", "SCFR Neutral Hadron Iso (endcap); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_endcap", "SCFR Photon Iso (endcap); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso", "SCFR Charged Hadron Iso; ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso", "SCFR Neutral Hadron Iso; ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso", "SCFR Photon Iso; ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso_barrel", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso_barrel", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso_barrel", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	
		
	histMan_->setCurrentHistogramFolder(histogramFolder_+"/ttfakeAllPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_barrel", "SCFR Charged Hadron Iso (barrel); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_barrel", "SCFR Neutral Hadron Iso (barrel); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_barrel", "SCFR Photon Iso (barrel); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_endcap", "SCFR Charged Hadron Iso (endcap); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_endcap", "SCFR Neutral Hadron Iso (endcap); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_endcap", "SCFR Photon Iso (endcap); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso", "SCFR Charged Hadron Iso; ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso", "SCFR Neutral Hadron Iso; ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso", "SCFR Photon Iso; ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso_barrel", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso_barrel", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso_barrel", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	
	histMan_->setCurrentHistogramFolder(histogramFolder_ + "/ttsigSignalPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_barrel", "SCFR Charged Hadron Iso (barrel); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_barrel", "SCFR Neutral Hadron Iso (barrel); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_barrel", "SCFR Photon Iso (barrel); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_endcap", "SCFR Charged Hadron Iso (endcap); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_endcap", "SCFR Neutral Hadron Iso (endcap); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_endcap", "SCFR Photon Iso (endcap); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso", "SCFR Charged Hadron Iso; ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso", "SCFR Neutral Hadron Iso; ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso", "SCFR Photon Iso; ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso_barrel", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso_barrel", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso_barrel", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);

		
	histMan_->setCurrentHistogramFolder(histogramFolder_+"/ttlepSignalPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_barrel", "SCFR Charged Hadron Iso (barrel); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_barrel", "SCFR Neutral Hadron Iso (barrel); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_barrel", "SCFR Photon Iso (barrel); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_endcap", "SCFR Charged Hadron Iso (endcap); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_endcap", "SCFR Neutral Hadron Iso (endcap); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_endcap", "SCFR Photon Iso (endcap); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso", "SCFR Charged Hadron Iso; ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso", "SCFR Neutral Hadron Iso; ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso", "SCFR Photon Iso; ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso_barrel", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso_barrel", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso_barrel", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	
		
	histMan_->setCurrentHistogramFolder(histogramFolder_+"/ttfakeSignalPhotons");

	histMan_->addH1D_BJetBinned("Number_Of_Photons", "Number of photons;N(#gamma);Events ", 6, -0.5, 5.5);
	histMan_->addH1D_BJetBinned("Photon_Pt", "Photon p_{T};p_{T}(#gamma)/GeV;Events/2GeV ", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_Eta", "Photon #eta; #eta(#gamma); Events/(0.02)", 300, -3, 3);
	histMan_->addH1D_BJetBinned("Photon_AbsEta", "Photon |#eta|; |#eta(#gamma)|; Events/(0.01)", 300, 0, 3);
	histMan_->addH1D_BJetBinned("Photon_Phi", "Photon #phi; #phi(#gamma); Events/(0.02)", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta", "Photon Sigma IEtaIEta; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_endcap", "Photon Sigma IEtaIEta EndCap; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_sigma_ietaieta_barrel", "Photon Sigma IEtaIEta Barrel; #sigmaI#etaI#eta; Events", 500, 0, 0.1);
	histMan_->addH1D_BJetBinned("Photon_HadOverEM", "Photon HadronicOverEM; HadOverEM; Events/(0.01)", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ET", "Photon E_{T}; E_{T}(#gamma); Events/(1 GeV)", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_EcalIso", "Photon Ecal Isolation; EcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso", "Photon Hcal Isolation; HcalIso; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_HcalIso2012", "Photon Hcal Isolation (2012); HcalIso2012; Events", 500, 0, 500);
	histMan_->addH1D_BJetBinned("Photon_TrckIso", "Photon Tracker Isolation; TrckIso; Events", 500, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCeta", "Photon Super Cluster Eta; #eta_{SC}; Events", 300, -3.5, 3.5);
	histMan_->addH1D_BJetBinned("Photon_SCphi", "Photon Super Cluster Phi; #phi_{SC}; Events", 400, -4, 4);
	histMan_->addH1D_BJetBinned("Photon_SCenergy", "Photon Super Cluster Energy; Energy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_SCSeedEnergy", "Photon Super Cluster Seed Energy; SeedEnergy_{SC}; Events", 1000, 0, 1000);
	histMan_->addH1D_BJetBinned("Photon_E3x3", "Photon Ecal 3x3 Cluster; E3x3; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_E5x5", "Photon Ecal 5x5 Cluster; E5x5; Events", 1100, -100, 1000);
	histMan_->addH1D_BJetBinned("Photon_TrkVeto", "Photon Track Veto; TrkVeto; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_deltaR_jets", "Photon #DeltaR(#gamma, jets); #DeltaR(#gamma, jets); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_electrons", "Photon #DeltaR(#gamma, electrons); #DeltaR(#gamma, electrons); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_deltaR_muons", "Photon #DeltaR(#gamma, #mu); #DeltaR(#gamma, #mu); Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_ConvSEVeto", "Photon Conversion Safe Electron Veto; 0=false, 1=true; Events", 2, 0, 2);
	histMan_->addH1D_BJetBinned("Photon_HtowoE", "Photon Single Tower HoverE; ; Events", 500, 0, 5);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_PFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_PFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_PFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_barrel", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_barrel", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_barrel", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFChargedHadronIso_endcap", "Photon PFChargedHadronIso; ; Events", 500, -20, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFNeutralHadronIso_endcap", "Photon PFNeutralHadronIso; ; Events", 500, -20, 50);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedPFPhotonIso_endcap", "Photon PFPhotonIso; ; Events", 500, -20, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_barrel", "SCFR Charged Hadron Iso (barrel); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_barrel", "SCFR Neutral Hadron Iso (barrel); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_barrel", "SCFR Photon Iso (barrel); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso_endcap", "SCFR Charged Hadron Iso (endcap); ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso_endcap", "SCFR Neutral Hadron Iso (endcap); ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso_endcap", "SCFR Photon Iso (endcap); ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_SCChIso", "SCFR Charged Hadron Iso; ; Events", 110, 0, 110);
	histMan_->addH1D_BJetBinned("Photon_SCNuIso", "SCFR Neutral Hadron Iso; ; Events", 105, 0, 35);
	histMan_->addH1D_BJetBinned("Photon_SCPhIso", "SCFR Photon Iso; ; Events", 500, 0, 130);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeChIso_barrel", "Random Cone Iso (Charged); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConeNuIso_barrel", "Random Cone Iso (Neutral); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RandConePhIso_barrel", "Random Cone Iso (Photon); ; Events", 100, 0, 20);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_barrel", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_barrel", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_barrel", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso_endcap", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso_endcap", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso_endcap", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCChIso", "SCFR Ch. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCNuIso", "SCFR Nu. Had.Iso. (#rho-corr)", 600, -1100, 100);
	histMan_->addH1D_BJetBinned("Photon_RhoCorrectedSCPhIso", "SCFR Photon Iso. (#rho-corr)", 600, -1100, 100);
	

}


}

