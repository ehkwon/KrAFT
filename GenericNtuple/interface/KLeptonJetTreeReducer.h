#ifndef KrAFT_GenericNtuple_KLeptonJetTreeReducer_H
#define KrAFT_GenericNtuple_KLeptonJetTreeReducer_H

#include "KrAFT/GenericNtuple/interface/KFlatTreeReducerBase.h"

class KLeptonJetTreeReducer : public KFlatTreeReducerBase
{
public:
  KLeptonJetTreeReducer(const std::string modeName,
                       const std::string inputFileName,
                       const std::string outputFileName);
  void run() { KFlatTreeReducerBase::run(); }

private:
  virtual bool analyze();

private:
  // Cache for Leptons, depend on decay modes
  typedef doubles* doublesP;
  typedef ints* intsP;

private:
  // Branch items for output tree
  double lepton_pt_, lepton_eta_, lepton_phi_, lepton_iso_;

  std::vector<TLorentzVector>* jets_;
  std::vector<double>* bTags_;
};

#endif
