 


// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile this code with C++11 std enabled or use it with a ROOT version compiled with C++11 features enabled (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif


#ifndef UNIMAINZ_TESTCLASSESINTREE_XE1TTPCPEAK
#define UNIMAINZ_TESTCLASSESINTREE_XE1TTPCPEAK



#include "Rtypes.h"
#include "TObject.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRandom.h"

//remove when debugging is done (used to quickly debug constructor calls)
#include <iostream>

class Xe1tTpcPeak : public TObject //TObject-derivation required to be in a TCloneArray 
{
private:
  //some trivial variable for testing
  Float_t mTotArea = 3.0;            //C++11 in-class initialisation extension 
  Float_t mBottomArea = 2.0;         //C++11 in-class initialisation extension

public:
  //Default constructor required by ROOT I/O, it is assumed by the automatic Streamer()
  Xe1tTpcPeak()                  //initialise using C++11 extension
  //  {}
  { std::cout << "Default constructor of Xe1tTpcPeak called" << std::endl; } //remove after debug

  //Constructor to set values
  Xe1tTpcPeak(Float_t tot, Float_t bottom) 
    : mTotArea(tot), mBottomArea(bottom) {}; //override the values specified in the C++11 extension
  
  void SetVars(Float_t tot, Float_t bottom) { mTotArea = tot; mBottomArea = bottom; }
  void Clear(Option_t* = "") override {} //Let's test the C++11 override cross-check

  const Float_t& Tot() const { return mTotArea; }
  const Float_t& Bottom() const { return mBottomArea; }

  ClassDef(Xe1tTpcPeak, 1); //Required by the ROOT I/O to automatically generate Streamer()
};


#endif // #ifndef UNIMAINZ_TESTCLASSESINTREE_XE1TTPCPEAK









