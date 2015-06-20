
// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile/run this macro with a ROOT version compiled with C++11 features enable (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif



#include "TPCevent.hpp"

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"


void testpreparation()
{
  TFile* poutfile = TFile::Open("testTPCevent.root","recreate");
  TTree* ptree = new TTree("treeTPC","tree for testing TPC event");
  
  Xe1tTpcEvent* pevent = new Xe1tTpcEvent();
  TBranch* pbranch = ptree->Branch("TPC", &pevent, 32000, 99); //maximum splitting
  pbranch->SetAutoDelete(kFALSE); //Enables this mechanism for TObject-derived
				  //objects to re-use the allocated memory for
				  //the same object instead of releasing it back
				  //to the system (btw kFalse is the default)

  ptree->BranchRef(); //Needed to autoload referenced objects

  const Long64_t totevents = 10;

  for (int ievt = 0; ievt < totevents; ++ievt) {
    pevent->BuildExampleEvent(ievt * 1000.0);
    ptree->Fill();
  }
  
  ptree->Write();
  delete pevent;
  delete poutfile; //Should delete also ptree
}

/*
IMPORTANT OUTCOME OF THIS TEST:

1) Due to TClonesArray and TObject allocators, the Xe1tTpcXXX objects are
allocated only the minimal necessary times and the location reused many times
(as testified by the debugging messages in the constructors)

*/
