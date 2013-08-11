toolsFolder = 'BristolAnalysis/Tools/'
import os
if os.environ.has_key('toolsFolder'):
    toolsFolder = os.environ['toolsFolder']
    
#center of mass energy: 7TeV for 2010/2011 data/MC, 8TeV for 2012 data
#this value will be part of the output file name: DataType_CenterOfMassEnergyTeV_lumipb-1_....
centerOfMassEnergy = 8    
#number of events to be processed
maxEvents = 10000 # -1 to run over all
#integrated luminosity the MC simulation will be scaled to
lumi = 19584#pb-1


if centerOfMassEnergy == 8:
    #File for pile-up re-weighting
    nTuple_version = 9
    PUFile = toolsFolder + "data/PileUp_2012_69300_truth_finebin.root"
    #+5%
#    PUFile = toolsFolder + "data/PileUp_2012_72765_truth_finebin.root"
    #-5%
#    PUFile = toolsFolder + "data/PileUp_2012_65835_truth_finebin.root"
else:
    #File for pile-up re-weighting
    nTuple_version = 8
    PUFile = toolsFolder + "data/PileUp_2011_truth_finebin_68000microbarn.root"
    #+5%
#    PUFile = toolsFolder + "data/PileUp_2011_truth_finebin_71400microbarn.root"
    #-5%
#    PUFile = toolsFolder + "data/PileUp_2011_truth_finebin_64600microbarn.root"


wizardtest = "root://dc2-grid-64.brunel.ac.uk//dpm/brunel.ac.uk/home/cms/store/user/phy6phs/LHE2EDM_WHIZARD_2to5_ttA/nTuple_v10_Summer12-PU_S7_START52_V9-v1_diLeptonPlus2Jets_final/*.root"
testntuple = "/data1/TTGammaAnalysis/TestNTuple/Test_nTuple_53X_mc.root"
piondir = "root://dc2-grid-64.brunel.ac.uk//dpm/brunel.ac.uk/home/cms//store/user/phy6phs/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final/*.root"
dir = "~/ttgamma/CMSSW_5_3_9/src/data"
SemiLept = "/TTJets_SemiLeptMGDecays_8TeV-madgraph/nTuple_v9a_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_LeptonPlus3Jets/*.root"
FullLept = "/TTJets_FullLeptMGDecays_8TeV-madgraph/nTuple_v9a_Summer12_DR53X-PU_S10_START53_V7A-v2_LeptonPlus3Jets/*.root"
Hadronic = "/TTJets_HadronicMGDecays_8TeV-madgraph/nTuple_v9a_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_LeptonPlus3Jets/*.root"
Massive = "/TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/nTuple_v9a_Summer12-PU_S10_START53_V7C-v1_LeptonPlus3Jets_PDFweights/*.root"
WPlusJets = "/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/GLOBALTAGV7A-v2/nTuple_v9a_Summer12_DR53X-PU_S10_START53_V7A-v2_LeptonPlus3Jets/*.root"
local = "/home/philip/workspace/git/TestSample/TTJets_nTuple_53X_mc.root"
#Jet Energy Resolutions files (L7 corrections)                                                                                                                                                                                     
bJetResoFile = toolsFolder + "data/bJetReso.root"
lightJetResoFile = toolsFolder + "data/lightJetReso.root"

#use HitFit for analysis
useHitFit = False
produceFitterASCIIoutput = False
inputFiles = [
#testntuple 
#dir + SemiLept 
 
 wizardtest
#'root://dc2-grid-64.brunel.ac.uk//dpm/brunel.ac.uk/home/cms//store/user/phy6phs/DoubleMu_EcalRecover_11Dec2012-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final/*.root' 
#local 
            ]

#relative Path from calling BAT to the TopQuarkAnalysis folder
TQAFPath = ""

#file with information (cross-section, number of processed events) for event weight calculation
datasetInfoFile = ""

if centerOfMassEnergy == 7:
    if nTuple_version == 7:
        datasetInfoFile = toolsFolder + "python/DataSetInfo_V7.py"
    else:
        datasetInfoFile = toolsFolder + "python/DataSetInfo.py"
elif centerOfMassEnergy == 8:
    datasetInfoFile = toolsFolder + "python/DataSetInfo_8TeV.py"

custom_file_suffix = "TEST"
