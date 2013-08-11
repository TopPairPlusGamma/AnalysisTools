mc_path = 'root://dc2-grid-64.brunel.ac.uk//dpm/brunel.ac.uk/home/cms//store/user/phy6phs/'
data_path = 'root://dc2-grid-64.brunel.ac.uk//dpm/brunel.ac.uk/home/cms//store/user/nberry/'
datasets = {'DoubleMu' : [  mc_path + 'DoubleMu_Run2012A-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
                            mc_path + 'DoubleMu_Run2012B-13Jul2012-v4_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
                            mc_path + 'DoubleMu_Run2012C-24Aug2012-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',    
			    mc_path + 'DoubleMu_Run2012D-16Jan2013-v2_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final'],
	'DoubleElectron' : [data_path + 'DoubleElectron_Run2012A-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
			    data_path + 'DoubleElectron_Run2012B-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
		 	    data_path + 'DoubleElectron_Run2012C-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
		 	    data_path + 'DoubleElectron_Run2012D-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final'],
	          'MuEG' : [data_path + 'MuEG_Run2012A-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
	 		    data_path + 'MuEG_Run2012B-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
	  		    data_path + 'MuEG_Run2012C-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final',
	   		    data_path + 'MuEG_Run2012D-22Jan2013-v1_AOD_nTuple_v10_GoldenJSON_diLeptonPlus2Jets_final'],	    
		 'TTGamma' : [mc_path + 'LHE2EDM_WHIZARD_2to5_ttA/nTuple_v10_Summer12-PU_S7_START52_V9-v1_diLeptonPlus2Jets_final'],	    	
                 'TTJet' : [mc_path + 'TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola_Summer12_DR53X-PU_S10_START53_V7C-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_rmgamma'],
                 'DYJetsToLL_M-10To50' : [mc_path + 'DYJetsToLL_M-10To50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
                 'DYJetsToLL_M-50' : [mc_path + 'DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
                 'TTJets_FullLept' : [mc_path + 'TTJets_FullLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
		 'TTJets_Hadronic' : [mc_path + 'TTJets_HadronicMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
                 'TTJets_SemiLept' : [mc_path + 'TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
		 'T_tW-channel' : [mc_path + 'T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
                 'Tbar_tW-channel' : [mc_path + 'Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
		 'WJetsToLNu' : [mc_path + 'WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v2_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
                 'QCD_Pt_20_MuEnrichedPt-15' : [mc_path + 'QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_Summer12_DR53X-PU_S10_START53_V7A-v3_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
		 'WWtoAnything' : [mc_path + 'WW_TuneZ2star_8TeV_pythia6_tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
                 'WZtoAnything' : [mc_path + 'WZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
		 'ZZtoAnything' : [mc_path + 'ZZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_nTuple_v10_diLeptonPlus2Jets_final'],
   
                     }

analysisModes = ['central',
                 'BJet_down',
                 'BJet_up',
                 'JES_down',
                 'JES_up',
                 'LightJet_down',
                 'LightJet_up',
                 'PU_down',
                 'PU_up',
		 'JetSmearing_up',
		 'JetSmearing_down',
                 'Test']

analysisModes.extend(['PDFWeights_%d' % weight for weight in range(1, 45)])

available_settings = ['JESsystematic', 'PUsystematic', 'BTagSystematic', 'LightTagSystematic', 'JetSmearingSystematic', 'custom_file_suffix']
default_settings = {
            'JESsystematic':0,
            'PUFile':'PileUp_2012_69300_truth_finebin.root',
            'BTagSystematic':0,
            'LightTagSystematic':0,
	    'JetSmearingSystematic':0,
            'custom_file_suffix':'',
            'pdfWeightNumber' : 0,
            }

analysis_settings = {
                     'BJet_down':{'BTagSystematic':-1},
                 'BJet_up':{'BTagSystematic':1},
                 'JES_down':{'JESsystematic':-1},
                 'JES_up':{'JESsystematic':1},
                 'LightJet_down':{'LightTagSystematic':-1},
                 'LightJet_up':{'LightTagSystematic':1},
                 'PU_down':{'PUFile':'PileUp_2012_65835_truth_finebin.root',
                            'custom_file_suffix':'PU_65835mb'
                            },
                 'PU_up':{'PUFile':'PileUp_2012_72765_truth_finebin.root',
                            'custom_file_suffix':'PU_72765mb'},
		 'JetSmearing_up':{'JetSmearingSystematic':1},
		 'JetSmearing_down':{'JetSmearingSystematic':-1},
                'Test': {'custom_file_suffix':'TESTING'}
                     }
for weight in range(1, 45):
    weight_txt = 'PDFWeights_%d' % weight 
    analysis_settings[weight_txt] = {'pdfWeightNumber' : weight,'custom_file_suffix': weight_txt}
from copy import deepcopy
#helperfunctions
def getAnalysisSettings(analysisMode):
    if not analysisMode in analysis_settings.keys():
        return default_settings
    
    settings = deepcopy(default_settings)
    settings.update(analysis_settings[analysisMode])
    return settings


#config start
toolsFolder = 'BristolAnalysis/Tools/'
import os
import sys
if os.environ.has_key('toolsFolder'):
    toolsFolder = os.environ['toolsFolder']
sample = ''
analysisMode = 'central'
if os.environ.has_key('analysisMode') and os.environ.has_key('sample'):
    sample = os.environ['sample']
    analysisMode = os.environ['analysisMode']
    if not analysisMode in analysisModes:
        print 'Unknown analysisMode=', analysisMode
        sys.exit()
    if not sample in datasets.keys():
        print 'Unknown sample=', sample
        sys.exit()
else:
    print 'Environmental variables "analysisMode" and "sample" not set'
    sys.exit()
    
settings = getAnalysisSettings(analysisMode)
if sample in ['TTJets-mcatnlo','TTJets-powheg']:
    suffixes = {'TTJets-mcatnlo':'MCatNLO','TTJets-powheg':'POWHEG'}
    if settings['custom_file_suffix'] == "":
        settings['custom_file_suffix'] = suffixes[sample]
    else:
        settings['custom_file_suffix'] = suffixes[sample] + '_' + settings['custom_file_suffix']    
    
#File for pile-up re-weighting
PUFile = toolsFolder + "data/" + settings['PUFile']
#JES Systematic, the +/- number of uncertainties to vary the jets with
JESsystematic = settings['JESsystematic']
JetSmearingSystematic = settings['JetSmearingSystematic']
BTagSystematic = settings['BTagSystematic']
LightTagSystematic = settings['LightTagSystematic']
custom_file_suffix = settings['custom_file_suffix']
print 'Parsed config settings:'
for setting,value in settings.iteritems():
    print setting, '=', value
input_folders = datasets[sample]
filetype = '*.root'
inputFiles = [path + '/' + filetype for path in input_folders]

#number of events to be processed
maxEvents = 0# 0 == all

#Jet Energy Resolutions files (L7 corrections)
bJetResoFile = toolsFolder + "data/bJetReso.root"
lightJetResoFile = toolsFolder + "data/lightJetReso.root"

#use HitFit for analysis
useHitFit = False
produceFitterASCIIoutput = False

#MET corrections application
applyMetSysShiftCorr = True
applyMetType0Corr = True

#relative Path from calling BAT to the TopQuarkAnalysis folder
TQAFPath = ""

#integrated luminosity the MC simulation will be scaled to
lumi = 19584.#pb-1

#center of mass energy: 7TeV for 2010/2011 data/MC, 8TeV for 2012 data
#this value will be part of the output file name: DataType_CenterOfMassEnergyTeV_lumipb-1_....
centerOfMassEnergy = 8

#file with information (cross-section, number of processed events) for event weight calculation
datasetInfoFile = ""
if centerOfMassEnergy == 7:
    datasetInfoFile = toolsFolder + "python/DataSetInfo.py"
elif centerOfMassEnergy == 8:
    datasetInfoFile = toolsFolder + "python/DataSetInfo_8TeV.py"
nTuple_version = 9
