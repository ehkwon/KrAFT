#include "KrAFT/GenericNtuple/interface/KLeptonJetTreeReducer.h"

using namespace std;

KLeptonJetTreeReducer::KLeptonJetTreeReducer(const std::string modeName,
                                           const std::string inputFileName,
                                           const std::string outputFileName):
  KFlatTreeReducerBase(modeName, inputFileName, outputFileName)
{

  outTree_->Branch("lepton_pt" , &lepton_pt_ , "lepton_pt/D" );
  //outTree_->Branch("lepton_eta", &lepton_eta_, "lepton_eta/D");
  //outTree_->Branch("lepton_phi", &lepton_phi_, "lepton_phi/D");
  outTree_->Branch("lepton_iso", &lepton_iso_, "lepton_iso/D");

  jets_   = new std::vector<TLorentzVector>;
  bTags_  = new std::vector<double>();
  outTree_->Branch("jets" , "std::vector<TLorentzVector>" , &jets_);
  outTree_->Branch("bTags", &bTags_);
}

bool KLeptonJetTreeReducer::analyze()
{
  if ( event_->muons_type_->size() == 0 ) return false;
  if ( event_->muons_type_->at(0) == 0 ) return false;
  // Select leptons
  LorentzVector leptonP4;
  const double muon_pt   = event_->muons_pt_->at(0);
  const double muon_eta  = event_->muons_eta_->at(0);
  const double muon_phi  = event_->muons_phi_->at(0);
  const double muon_mass = event_->muons_m_->at(0);
  
  if ( muon_pt < 26 or abs(muon_eta) > 2.1 ) return false;
  if ( event_->muons_relIso_->at(0) >= 0.12 ) return false;

  leptonP4.SetPtEtaPhiM(muon_pt, muon_eta, muon_phi, muon_mass);


  for ( int i=0, n=event_->jets_pt_->size(); i<n; ++i )
  {
    const double jetPt = event_->jets_pt_->at(i);

    LorentzVector jetP4;
    jetP4.SetPtEtaPhiM(jetPt, event_->jets_eta_->at(i), event_->jets_phi_->at(i), event_->jets_m_->at(i));
    jets_->push_back(jetP4);
    bTags_->push_back(event_->jets_bTag_->at(i));
  }
//  bTagCut_ = 0.898; // Tight cut
//  bTagCut_ = 0.679; // Medium cut
//  bTagCut_ = 0.244; // Loose cut



  return true;
}

