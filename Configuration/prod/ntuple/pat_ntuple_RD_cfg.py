import FWCore.ParameterSet.Config as cms
process = cms.Process("PAT")
runOnMC = False

from TopAnalysis.Configuration.pat_template_cff import applyPAT
applyPAT(process, runOnMC=runOnMC)

process.source.fileNames = [
    '/store/user/jhgoh/MuEG/Run2012A-22Jan2013-v1-KCMSSkim20131027_1/4407ef23eed415918ae815f01ecb7627/skim_1_1_2W6.root',
]
