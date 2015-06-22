

// PLEASE COMPILE ROOT WITH C++11 STD OR USE ROOT6 (WHICH IS COMPULSORY COMPILED WITH C++11 STD)
#if __cplusplus < 201103L
#error Please compile this code with a C++11 std enabled compiler or use it with a ROOT version compiled with C++11 features enable (e.g. ROOT6 is compulsory compiled with C++11 standard)
#endif



#include "Xe1tTpcEvent.hpp"
#include "Xe1tTpcPeak.hpp"

extern TRandom* gRandom;

Xe1tTpcEvent::Xe1tTpcEvent() //A standard constructor is required for ROOT I/O
{    
  pTpcPeaks = new TClonesArray("Xe1tTpcPeak", kMaxTpcPeaksPerEvent);
  pRefS1Peaks = new TRefArray;
  pRefS2Peaks = new TRefArray;
  
  //for DEBUG only... comment this line out otherwise
  std::cout << "Default constructor of Xe1tTpcEvent called" << std::endl;
}

Xe1tTpcEvent::~Xe1tTpcEvent() {
  ClearEvent(); //takes care of the TCloneArray, as in the ROOT Event class
  delete pRefS1Peaks; pRefS1Peaks = 0; //Is this reset to 0 strictly needed by ROOT, e.g. by
  delete pRefS2Peaks; pRefS2Peaks = 0; //Streamers?!?! TO BE CHECKED
}

void Xe1tTpcEvent::ClearEvent() {
  pTpcPeaks->Clear("C"); //With the "C" option, the TClonesArray will call the method "Clear" of
			 //each Xe1tTpcPeak. Well, at the moment this class is trivial, but the
			 //principle is that Clear() should take care of the deallocation (or even
			 //better the re-use, that is the final goal) of the dynamically allocated
			 //memory. TClonesArray has also a Delete() method, but this will call the
			 //destructors so any specific memory re-use that the embedded class could
			 //have implemented is not exploited
  pRefS1Peaks->Delete(); //TRefArray is not the owner of the referenced objects, so Delete()
  pRefS2Peaks->Delete(); //clears the list but does not destroy the referenced objects
}


void Xe1tTpcEvent::BuildExampleEvent(Double_t bias) {

  //The ROOT event class here save current object count, and set it back to this at the end of the
  //function... 
  Int_t objectnumber = TProcessID::GetObjectCount();
  
  ClearEvent();

  mEvtNumber = static_cast<Long64_t>( bias ) ; //Just to fill with some value
  mTimeStamp = bias*10. + gRandom->Uniform(0.,8.); //Just to fill with some value

  // Yes you are right, this piece should be embedded in a proper "AddPeak()"/"AddS1()"/"AddS2()" methods, but for
  // this test I am too lazy to do that

  auto npeaks = static_cast<Int_t>( gRandom->Uniform(2 , kMaxTpcPeaksPerEvent) ); //C++11 new type-deducing feature with "auto"

  for (Int_t ipeak = 0; ipeak < npeaks ; ++ipeak) {
    auto ppeak = static_cast<Xe1tTpcPeak*>( pTpcPeaks->ConstructedAt(ipeak) );

    ppeak->SetVars(bias+ipeak*10.0, bias+ipeak*7.0); //again just some values

    //Let's make just for this example any first peak every three peaks a S1, any second a S2 and
    //any third nothing interesting
    if(ipeak%3 == 0) pRefS1Peaks->Add(ppeak);
    if(ipeak%3 == 1) pRefS2Peaks->Add(ppeak);
  }
  
  //The next 4 lines are the comments within the ROOT Event class
  //  "Restore Object count 
  //   To save space in the table keeping track of all referenced objects
  //   we assume that our events do not address each other. We reset the 
  //   object count to what it was at the beginning of the event."
  TProcessID::SetObjectCount(objectnumber);
}
