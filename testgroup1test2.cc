
// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile this code with a C++11 std enabled or use it with a ROOT version compiled with C++11 features enable (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif


#include "TFile.h"
#include "TTree.h"

#include "Xe1tTpcPeak.hpp"
#include "Xe1tTpcEvent.hpp"

#include <iostream>


TCanvas testgroup1test2canvas1 ;


void testgroup1test2()
{
  using std::cout;
  using std::endl;

  auto prootfile = TFile::Open("testTPCevent.root");
  auto ptree = static_cast<TTree*>( prootfile->Get("treeTPC") );
  ptree->Print();

  cout << "\n 1) Next test is: ptree->Scan(\"mEvtNumber\"); //i.e. a request not accessing the Peaks' TCloneArray\n";

  cout << "Double-click the canvas to continue" << endl;
  testgroup1test1canvas1.Modified() ; testgroup1test1canvas1.Update() ; testgroup1test1canvas1.WaitPrimitive() ;

  ptree->Scan("mEvtNumber");

  cout << "Please scroll up and note the debug message on the Xe1tTpcEvent construction called at the very beginning."
    "\n This is called also once (i.e. the object is reused). MOREOVER NO Xe1tTpcPeak OBJECT IS CONSTRUCTED"
    " (no debug message from constructors) BECAUSE THEY ARE NOT REQUIRED."
    " \n Therefore a TClonesArray can efficently manage object in a TTree, avoiding to read from disk unnecessary objects\n";

  cout << "Double-click the canvas to continue" << endl;
  testgroup1test1canvas1.Modified() ; testgroup1test1canvas1.Update() ; testgroup1test1canvas1.WaitPrimitive() ;

  cout << "\n 2) Next test is: ptree->Scan(\"mEvtNumber:pTpcPeaks@->GetEntries():mTotArea\"); //i.e. now a variable within the Peaks' TClonesArray is requested.\n";

  cout << "Double-click the canvas to continue" << endl;
  testgroup1test1canvas1.Modified() ; testgroup1test1canvas1.Update() ; testgroup1test1canvas1.WaitPrimitive() ;

  ptree->Scan("mEvtNumber:pTpcPeaks@->GetEntries():mTotArea");

  cout << "Please scroll up and check how Xe1tTpcPeak are constructed: only when required and only the first time!"
    " \n (compare with the number of elements in the TClonesArray per event). Any already constructed element is just re-used." << endl;


  /*
  ptree->Scan("mIntVar:mFloatVar:pTpcPeaks@->GetEntries()"
	      ":mBottomArea:mTotArea:fUniqueID"
	      ":pRefS1Peaks->fUniqueID:pRefS1Peaks->mTotArea"
	      ":pRefS2Peaks->fUniqueID:pRefS2Peaks->mTotArea");
  ptree->Scan("mIntVar:mFloatVar:pTpcPeaks@->GetEntries():Bottom():Tot():fUniqueID:"
	      "pRefS1Peaks->fUniqueID:pRefS1Peaks->Tot():pRefS2Peaks->fUniqueID:pRefS2Peaks->Tot()");
  */
}
