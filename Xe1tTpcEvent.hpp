

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
#include "TRandom.h"

#include "Xe1tTpcPeak.hpp"

//remove when debugging is done
#include <iostream>


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

  const TRefArray* GetS1List() const { return pRefS1Peaks; } //is const suitable?
  const TRefArray* GetS2List() const { return pRefS2Peaks; } //is const suitable?

  void ClearEvent() ;

  void BuildExampleEvent(Double_t bias);

};


#endif // #ifndef UNIMAINZ_TESTCLASSESINTREE_XE1TTPCEVENT









