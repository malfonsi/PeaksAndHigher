

// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile this code with a C++11 std enabled compiler or use it with a ROOT version compiled with C++11 features enable (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif


#ifndef UNIMAINZ_TESTCLASSESINTREE_XE1TTPCEVENT
#define UNIMAINZ_TESTCLASSESINTREE_XE1TTPCEVENT


#include "Rtypes.h"
//#include "TObject.h" //only if we derive from TObject
#include "TClonesArray.h"
#include "TRefArray.h"


#include "Xe1tTpcPeak.hpp"



class Xe1tTpcEvent 
// : public TObject //derivation from TObject not strictly required in this case
{

private:
  // Some event-wide trivial variables for testing
  Long64_t mEvtNumber = -1LL ;      //C++11 in-class initialisation extension
  Double_t mTimeStamp = -1.0 ;      //C++11 in-class initialisation extension

  // The pointer to the peaks
  TClonesArray   *pTpcPeaks;      //-> This arrow instructs the ROOT automatic Streamer to assume
				  // that the pointer is always valid (and one has to keep this
				  // promise! compare with the constructor!).     
  
  // Let's test the TRefArray features
  TRefArray     *pRefS1Peaks;
  TRefArray     *pRefS2Peaks;

public:
  constexpr static Int_t kMaxTpcPeaksPerEvent = 10;
  
  Xe1tTpcEvent() ; //A standard constructor is required for ROOT I/O

  ~Xe1tTpcEvent() ;

  //  const TRefArray* S1List() const { return pRefS1Peaks; } //they do not work of course... maybe 
  //  const TRefArray& S2List() const { return *pRefS2Peaks; } //with the new TTreeFormula of ROOT6.06 ?

  Long64_t EvtId() const { return mEvtNumber; } 
  Int_t NbPeaks() const { return pTpcPeaks->GetEntries(); }
  Int_t NbS1() const { return pRefS1Peaks->GetLast() + 1; } //Yes, this is the total number of events of
  Int_t NbS2() const { return pRefS2Peaks->GetLast() + 1; } //a TRefArray... complain with the ROOT team!
  

  const Xe1tTpcPeak* S1(UInt_t index) const 
  { return static_cast<Xe1tTpcPeak*>( pRefS1Peaks->At(index) ); }
  
  const Xe1tTpcPeak* S2(UInt_t index) const 
  { return static_cast<Xe1tTpcPeak*>( pRefS2Peaks->At(index) ); } 


  void ClearEvent() ;

  void BuildExampleEvent(Double_t bias);

};


#endif // #ifndef UNIMAINZ_TESTCLASSESINTREE_XE1TTPCEVENT









