
// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile this code with a C++11 std enabled compiler or use it with a ROOT version compiled with C++11 features enable (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif


#include "TFile.h"
#include "TTree.h"

#include "Xe1tTpcPeak.hpp"
#include "Xe1tTpcEvent.hpp"

#include <iostream>


TCanvas testgroup1canvas("testgroup1canvas","Double click me!",200,200) ;

void WaitForDClick()
{
  cout << "\nDouble-click the canvas to continue\r" << flush;
  testgroup1canvas.Modified() ; testgroup1canvas.Update() ; testgroup1canvas.WaitPrimitive() ;
  cout << "                                                            \n";
}


void testgroup1test3()
{
  using std::cout;
  using std::endl;
  using std::flush;

  auto prootfile = TFile::Open("testTPCevent.root");
  auto ptree = static_cast<TTree*>( prootfile->Get("treeTPC") );
  ptree->SetScanField(0);
  //  ptree->Print();

  // 6)

  cout << "\n *****************************************************************************";
  cout << "\n YOU SHOULD RUN THIS TEST IN A FRESH ROOT SESSION ";
  cout << "\n 6) NEXT TEST IS: ptree->Scan(\"pRefS1Peaks@->GetLast()+1\"); //do I need to load the TClonesArray branch?\n";

  WaitForDClick();
  
  cout << "________________________________________________________\n";
  ptree->Scan("pRefS1Peaks@->GetLast()+1");
  cout << "________________________________________________________\n\n";

  cout << " A TRefArray knows about its own size and do not need to load the referenced TClonesArray elements\n";

  WaitForDClick();

  cout << " Run the next test scripts in fresh ROOT session. " << endl;

}
