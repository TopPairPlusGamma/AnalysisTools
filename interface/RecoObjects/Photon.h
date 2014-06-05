/*
 * Photon.h
 *
 *  Created on: 22 April 2013
 *      Author: Nik Berry
 */

#ifndef PHOTON_H_
#define PHOTON_H_
#include <vector>
#include <string>
#include <boost/array.hpp>
#include "Particle.h" 

namespace BAT {

namespace PhotonAlgorithm {
enum value {
    Default,
    NUMBER_OF_PHOTONALGORITHMS
};

const boost::array<std::string, PhotonAlgorithm::NUMBER_OF_PHOTONALGORITHMS> prefixes = { { 
        "recoPhotons" } }; //recoPhotons

const boost::array<std::string, PhotonAlgorithm::NUMBER_OF_PHOTONALGORITHMS> names = { { 
        "Photon"} };
}


class Photon: public BAT::Particle {
public:
	Photon();
	Photon(double energy, double px, double py, double pz);
	virtual ~Photon();
	void setUsedAlgorithm(PhotonAlgorithm::value algorithm);
	double ecalIsolation() const;
        double hcalIsolation() const;
	double hcalIsolation2012() const;
        double trackerIsolation() const;
	double superClusterEta() const;
    	double sigmaIEtaIEta() const;
	double superClusterPhi() const;
        double superClusterEnergy() const;
        double superClusterSeedEnergy() const;
        double Ecal3x3Cluster() const;
        double Ecal5x5Cluster() const;
	double HadOverEm() const;
	double TrackVeto() const;
	double ConversionSafeElectronVeto() const;
	double SingleTowerHoE() const;
	double PFChargedHadronIso() const;
	double PFNeutralHadronIso() const;
	double PFPhotonIso() const;
	double RhoCorrectedPFChargedHadronIso(double rho) const;
	double RhoCorrectedPFNeutralHadronIso(double rho) const;
	double RhoCorrectedPFPhotonIso(double rho) const;
	double phoSCChIso() const;
	double phoSCNuIso() const;
	double phoSCPhIso() const;
	double phoRandConeChIso() const;
	double phoRandConeNuIso() const;
	double phoRandConePhIso() const;
	double RhoCorrectedSCChIso(double rho) const;
	double RhoCorrectedSCNuIso(double rho) const;
	double RhoCorrectedSCPhIso(double rho) const;
	double getEfficiencyCorrection() const;	
	
	//void setUsedAlgorithm(PhotonAlgorithm::value algo);
	void setEcalIsolation(double EIso);
	void setHcalIsolation(double HIso);
	void setHcalIsolation2012(double HIso2012);
	void setTrackerIsolation(double TrckIso);
	void setSuperClusterEta(double eta);
	void setSigmaIEtaIEta(double sigma);
	void setSuperClusterPhi(double phi);
	void setSuperClusterEnergy(double SCenergy);
	void setSuperClusterSeedEnergy(double SCseedE);
	void setEcal3x3Cluster(double E3x3);
	void setEcal5x5Cluster(double E5x5);
	void setHadOverEm(double HoverE);
	void setTrackVeto(double TrkVeto);
	void setConversionSafeElectronVeto(double ConvSEVeto);
	void setSingleTowerHoE(double HtowoE);
	void setPFChargedHadronIso(double PfChargedIso03);
	void setPFNeutralHadronIso(double PfNeutralIso03);
	void setPFPhotonIso(double PfPhotonIso03);
	void setRhoCorrectedPFChargedHadronIso(double RhoCorrPfChargedIso03);
	void setRhoCorrectedPFNeutralHadronIso(double RhoCorrPfNeutralIso03);
	void setRhoCorrectedPFPhotonIso(double RhoCorrPfPhotonIso03);
	void setphoSCChIso(double phoSCChIso);
	void setphoSCNuIso(double phoSCNuIso);
	void setphoSCPhIso(double phoSCPhIso);
	void setphoRandConeChIso(double phoRandConeChIso);
	void setphoRandConeNuIso(double phoRandConeNuIso);
	void setphoRandConePhIso(double phoRandConePhIso);
	void setRhoCorrectedSCChIso(double RhoCorrSCChIso);
	void setRhoCorrectedSCNuIso(double RhoCorrSCNuIso);
	void setRhoCorrectedSCPhIso(double RhoCorrSCPhIso);
	
	
	virtual bool isInBarrelRegion() const;
    	bool isInCrack() const;
    	bool isInEndCapRegion() const;
	virtual std::string toString() const;

private:
        PhotonAlgorithm::value usedAlgorithm_;
	double EcalIso;
	double HcalIso;
	double HcalIso2012;
	double TrackIso;
	double superCluster_Eta;
	double sigma_IEtaIEta;
	double superCluster_Phi;
	double superCluster_Energy;
	double superCluster_SeedEnergy;
	double Ecal_3x3_Cluster;
	double Ecal_5x5_Cluster;
	double hadOverEm;
	double trackVeto;
	double Conversion_Safe_Electron_Veto;
	double singleTowerHoE;
	double pfChargedHadronIso;
	double pfNeutralHadronIso;
	double pfPhotonIso;
	double rhocorrectedpfChargedIso;
	double rhocorrectedpfNeutralIso;
	double rhocorrectedpfPhotonIso;
	double phoscchIso;
	double phoscnuIso;
	double phoscphIso;
	double phorandconechIso;
	double phorandconenuIso;
	double phorandconephIso;
	double rhocorrectedscchIso;
	double rhocorrectedscnuIso;
	double rhocorrectedscphIso;

};

typedef boost::shared_ptr<Photon> PhotonPointer;
typedef std::vector<PhotonPointer> PhotonCollection;
	
}

#endif /* PHOTON_H_ */
