
// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile this code with a C++11 std enabled compiler or use it with a ROOT version compiled with C++11 features enable (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif


#include "TFile.h"
#include "TTree.h"

#include "Xe1tTpcPeak.hpp"
#include "Xe1tTpcEvent.hpp"

#include <iostream>


TCanvas testgroup1test1canvas1 ;

void WaitForDClick()
{
  cout << "\nDouble-click the canvas to continue\r" << flush;
  testgroup1test1canvas1.Modified() ; testgroup1test1canvas1.Update() ; testgroup1test1canvas1.WaitPrimitive() ;
  cout << "                                                            \n";
}


void testgroup1test1()
{
  using std::cout;
  using std::endl;
  using std::flush;

  auto prootfile = TFile::Open("testTPCevent.root");
  auto ptree = static_cast<TTree*>( prootfile->Get("treeTPC") );
  ptree->Print();

  // 1)

  cout << "\n *****************************************************************************";
  cout << "\n 1) NEXT TEST IS: ptree->Scan(\"mEvtNumber\"); //i.e. a request not accessing the Peaks' TCloneArray\n";

  WaitForDClick();
  
  cout << "________________________________________________________\n";
  ptree->Scan("mEvtNumber");
  cout << "________________________________________________________\n\n";

  cout << " Please scroll up and note the debug message on the Xe1tTpcEvent construction called at the very beginning."
    "\n This is called only once (i.e. the object is reused). MOREOVER NO Xe1tTpcPeak OBJECT IS CONSTRUCTED"
    " (no debug message from constructors) BECAUSE THEY ARE NOT REQUIRED."
    " \n Therefore a TClonesArray can efficently manage object in a TTree, avoiding to read from disk unnecessary objects\n";

  WaitForDClick();


  // 2)

  cout << "\n *****************************************************************************";
  cout << "\n 2) NEXT TEST IS: ptree->Scan(\"mEvtNumber:pTpcPeaks@->GetEntries():mTotArea\",\"\",\"colsize=20\"); //i.e. now a variable within the Peaks' TClonesArray is requested.\n";

  WaitForDClick();

  cout << "____________________________________________________________________________\n";
  ptree->Scan("mEvtNumber:pTpcPeaks@->GetEntries():mTotArea","","colsize=20");
  cout << "____________________________________________________________________________\n\n";

  cout << " Please scroll up and check how Xe1tTpcPeak are constructed: only when required and only the first time!"
    " \n (compare with the number of elements in the TClonesArray per event). Any already constructed element is just re-used.\n\n";

  WaitForDClick();


  // 3)

  cout << "\n *****************************************************************************";
  cout << "\n 3) NEXT TEST IS: ptree->Scan(\"mEvtNumber:pTpcPeaks@->GetEntries():pTpcPeaks.mTotArea:pRefS1Peaks@->GetLast()+1:pRefS1Peaks.mTotArea:pRefS2Peaks@->GetLast()+1:pRefS2Peaks.mTotArea\");\n"
    " //This shows how a TClonesArray and TRefArray contained objects can be accessed\n"
    " //Note the use of @ to access methods of container rather than the \"contained\", I wonder how this will change with the new TTreeFormula of the upcoming ROOT 6.06\n"
    " //Note also the use of GetLast()+1 to know the total entries of a TRefArray as the last index + 1 (GetEntries() exists but they claim that it is inefficient in this case)\n" ;

  WaitForDClick();

  cout << "______________________________________________________________________________________________________________________________\n";
  ptree->Scan("mEvtNumber:pTpcPeaks@->GetEntries():pTpcPeaks.mTotArea:pRefS1Peaks@->GetLast()+1:pRefS1Peaks.mTotArea:pRefS2Peaks@->GetLast()+1:pRefS2Peaks.mTotArea","","colsize=20");
  cout << "______________________________________________________________________________________________________________________________\n\n";

  cout << " You can verify the use of TRefArray: it addresses the right element within TClonesArray without making unnecessary duplicates ";

  WaitForDClick();






  /*
  ptree->Scan("mIntVar:mFloatVar:pTpcPeaks@->GetEntries()"
	      ":mBottomArea:mTotArea:fUniqueID"
	      ":pRefS1Peaks->fUniqueID:pRefS1Peaks->mTotArea"
	      ":pRefS2Peaks->fUniqueID:pRefS2Peaks->mTotArea");
  ptree->Scan("mIntVar:mFloatVar:pTpcPeaks@->GetEntries():Bottom():Tot():fUniqueID:"
	      "pRefS1Peaks->fUniqueID:pRefS1Peaks->Tot():pRefS2Peaks->fUniqueID:pRefS2Peaks->Tot()");
  */
}
