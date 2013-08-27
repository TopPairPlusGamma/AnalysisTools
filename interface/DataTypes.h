/*
 * Enumerators.h
 *
 *  Created on: Jun 30, 2010
 *      Author: lkreczko
 */

#ifndef ENUMERATORS_H_
#define ENUMERATORS_H_
#include <string>
#include <boost/array.hpp>

namespace BAT {
namespace DataType {
enum value {
	ElectronHad,
	MuHad,
	SingleElectron,
	SingleMu,
	DoubleMu,
	DoubleElectron,
	MuEG,
	TTGamma,
	TTJets,
	Wjets,
	Zjets,
	QCD_Pt_20_30_BCtoE,
	QCD_Pt_20_30_EMEnriched,
	QCD_Pt_20_MuEnrichedPt_15,
	QCD_Pt_30_80_BCtoE,
	QCD_Pt_30_80_EMEnriched,
	QCD_Pt_80_170_BCtoE,
	QCD_Pt_80_170_EMEnriched,
	PhotonJets_Pt40to100,
	PhotonJets_Pt100to200,
	PhotonJets_Pt200toInf,
	PhotonJets_Pt200to400,
	PhotonJets_Pt400toInf,
	VQQ,
	singleTop_And_W, 
	singleTopTChannel,
	singleTopSChannel,
	singleAntiTop_And_W,
	singleAntiTopTChannel,
	singleAntiTopSChannel,
	WWtoAnything,
	WZtoAnything,
	ZZtoAnything,
	TTJets_matchingdown,
	TTJets_matchingup,
	TTJets_scaledown,
	TTJets_scaleup,
	WJets_matchingdown,
	WJets_matchingup,
	WJets_scaledown,
	WJets_scaleup,
	ZJets_matchingdown,
	ZJets_matchingup,
	ZJets_scaledown,
	ZJets_scaleup,
	TTJetsPlusZ,
	TTbarPlusW,
	TTJets_SemiLept,
	TTJets_FullLept,
	TTJets_Hadronic,
	DYJetsToLL_M_10To50,
	DYJetsToLL_M_50,
	NUMBER_OF_DATA_TYPES
};

const boost::array<std::string, DataType::NUMBER_OF_DATA_TYPES> names = { {
//
		"ElectronHad",//
		"MuHad", //
		"SingleElectron",//
		"SingleMu",//
		"DoubleMu", //
		"DoubleElectron",
		"MuEG", 
		"TTGamma",
		"TTJet", //
		"WJetsToLNu", //
		"DYJetsToLL",
		"QCD_Pt_20_30_BCtoE",
		"QCD_Pt_20_30_EMEnriched",
		"QCD_Pt_20_MuEnrichedPt_15",
		"QCD_Pt_30_80_BCtoE",
		"QCD_Pt_30_80_EMEnriched",
		"QCD_Pt_80_170_BCtoE",
		"QCD_Pt_80_170_EMEnriched",
		"GJets_HT-40To100", //
		"GJets_HT-100To200", //
		"GJets_HT-200ToInf", //
		"GJets_HT-200To400", //
		"GJets_HT-400ToInf", //
		"VqqJets", //
		"T_tW-channel", //
		"T_t-channel", //
		"T_s-channel", //
		"Tbar_tW-channel", //
		"Tbar_t-channel", //20
		"Tbar_s-channel", //
		"WWtoAnything", //
		"WZtoAnything", //
		"ZZtoAnything", //
		"TTJets-matchingdown", //
		"TTJets-matchingup", //
		"TTJets-scaledown", //
		"TTJets-scaleup", //
		"WJets-matchingdown", //
		"WJets-matchingup", //
		"WJets-scaledown", //
		"WJets-scaleup", //
		"ZJets-matchingdown",//
		"ZJets-matchingup",//
		"ZJets-scaledown",//
		"ZJets-scaleup",//
		"TTbarZIncl", //
		"TTbarInclWIncl", //
		"TTJets_SemiLept",//
		"TTJets_FullLept",//
		"TTJets_Hadronic",//
		"DYJetsToLL_M-10To50",//
		"DYJetsToLL_M-50"//
		} };
}

}

#endif /* ENUMERATORS_H_ */
