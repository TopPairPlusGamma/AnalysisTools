/*
 * Muon.cpp
 *
 *  Created on: Jun 25, 2010
 *      Author: lkreczko
 */

#include "../../interface/RecoObjects/Muon.h"
#include "../../interface/GlobalVariables.h"

namespace BAT {
const double initialBigValue = 123456789;

Muon::Muon() :
		Lepton(), //
		usedAlgorithm_(MuonAlgorithm::Default), //
		isGlobalMuon_(false), //
		isTrackerMuon_(false), //
		isPFMuon_(false), //
		normalisedChi2_(initialBigValue), //
		numberOfValidMuonHits_(-1), //
		numberOfValidPixelHits_(-1), //
		numberOfValidHits_(-1), //
		pixelLayersWithMeasurement_(-1), //
		trackerLayersWithMeasurement_(-1), //
		numberOfMatches_(-1), //
		numberOfMatchedStations_(-1) {

}

Muon::Muon(double energy, double px, double py, double pz) :
		Lepton(energy, px, py, pz), //
		usedAlgorithm_(MuonAlgorithm::Default), //
		isGlobalMuon_(false), //
		isTrackerMuon_(false), //
		isPFMuon_(false), //
		normalisedChi2_(initialBigValue), //
		numberOfValidMuonHits_(-1), //
		numberOfValidPixelHits_(-1), //
		numberOfValidHits_(-1), //
		pixelLayersWithMeasurement_(-1), //
		trackerLayersWithMeasurement_(-1), //
		numberOfMatches_(-1), //
		numberOfMatchedStations_(-1) {

}

Muon::~Muon() {
}

bool Muon::isGlobal() const {
	return isGlobalMuon_;
}

bool Muon::isTracker() const {
	return isTrackerMuon_;
}

bool Muon::isPFMuon() const {
	return isPFMuon_;
}

void Muon::makeGlobal(bool global) {
	isGlobalMuon_ = global;
}

void Muon::setTrackerMuon(bool isTrackerMuon) {
	isTrackerMuon_ = isTrackerMuon;
}

void Muon::setPFMuon(bool pf) {
	isPFMuon_ = pf;
}

void Muon::setNormalisedChi2(double normChi2) {
	normalisedChi2_ = normChi2;
}

void Muon::setNumberOfValidHits(int nValidHits) {
	numberOfValidHits_ = nValidHits;
}

void Muon::setNumberOfValidMuonHits(int nValidHits) {
	numberOfValidMuonHits_ = nValidHits;
}

void Muon::setNumberOfValidPixelHits(int nValidHits) {
	numberOfValidPixelHits_ = nValidHits;
}

void Muon::setPixelLayersWithMeasurement(int pixelLayers) {
	pixelLayersWithMeasurement_ = pixelLayers;
}

void Muon::setNumberOfMatchedStations(int nMatchedStations) {
	numberOfMatchedStations_ = nMatchedStations;
}

void Muon::setNumberOfMatches(int nMatches) {
	numberOfMatches_ = nMatches;
}

bool Muon::isPFLepton() const {
	return usedAlgorithm_ == MuonAlgorithm::ParticleFlow;
}

void Muon::setUsedAlgorithm(MuonAlgorithm::value algorithm) {
	usedAlgorithm_ = algorithm;
}

void Muon::setTrackerLayersWithMeasurement(int layers) {
	trackerLayersWithMeasurement_ = layers;
}

int Muon::trackerLayersWithMeasurement() const {
	return trackerLayersWithMeasurement_;
}

int Muon::numberOfMatchedStations() const {
	return numberOfMatchedStations_;
}

int Muon::numberOfMatches() const {
	return numberOfMatches_;
}

int Muon::numberOfValidHits() const {
	return numberOfValidHits_;
}

int Muon::numberOfValidMuonHits() const {
	return numberOfValidMuonHits_;
}

int Muon::numberOfValidPixelHits() const {
	return numberOfValidPixelHits_;
}

int Muon::pixelLayersWithMeasurement() const {
	return pixelLayersWithMeasurement_;
}

double Muon::normChi2() const {
	return normalisedChi2_;
}

//https://indico.cern.ch/getFile.py/access?contribId=1&resId=2&materialId=slides&confId=257630  ID and Iso efficiencies.
//double Muon::getEfficiencyCorrection() const {  //no idea what the second number in the correction is - need to find out/
//	double correction(1.);
//	double muEta(eta());
//
//	if(abs(muEta)<0.9)
//		correction = 0.9984*0.9990;
//	else if(abs(muEta)>=0.9 && abs(muEta)<1.2)
//		correction = 0.9990*1.0011;
//	else if(abs(muEta)>=1.2 && abs(muEta)<2.1)
//		correction = 0.9986*1.0013;
//	else if(abs(muEta)>=2.1 && abs(muEta)<2.4)
//		correction = 1.0000*1.0242;
//
//	return correction;
//}

double Muon::getEfficiencyCorrection() const {
        double correction(1.);
        double muEta(eta());
	
	if(Globals::MuonIDSFUp == true){

       		if(abs(muEta)<0.9)
               		correction = 0.9986; 
       		else if(abs(muEta)>=0.9 && abs(muEta)<1.2)
               		correction = 0.9992;
       		else if(abs(muEta)>=1.2 && abs(muEta)<2.1)
               		correction = 0.9987;
       		else if(abs(muEta)>=2.1 && abs(muEta)<2.4)
               		correction = 1.0003;
		
	} else if(Globals::MuonIDSFDown == true){
	
             if(abs(muEta)<0.9)
                     correction = 0.9982; 
             else if(abs(muEta)>=0.9 && abs(muEta)<1.2)
                     correction = 0.9988;
             else if(abs(muEta)>=1.2 && abs(muEta)<2.1)
                     correction = 0.9985;
             else if(abs(muEta)>=2.1 && abs(muEta)<2.4)
                     correction = 0.9997;
		     
	} else {

        	if(abs(muEta)<0.9)
			correction = 0.9984;
		else if(abs(muEta)>=0.9 && abs(muEta)<1.2)
                	correction = 0.9990;
       		else if(abs(muEta)>=1.2 && abs(muEta)<2.1)
                	correction = 0.9986;
        	else if(abs(muEta)>=2.1 && abs(muEta)<2.4)
                	correction = 1.0000;

	}
	
	return correction;

}

double Muon::getdiMuonTriggerSF() const {

	double SF = 0.967;

	return SF;
	
}

double Muon::getdiLeptonTriggerSF() const {

	double SF = 0.953;

	return SF;
	
}

}
