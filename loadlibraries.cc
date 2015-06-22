
{
  // Run first this un-named script before using the libraries:
  //   .x loadlibraries.cc
  // you can also start root asking to run the script
  //   root loadlibraries.cc

  // Starting with ROOT6, DO NOT INCLUDE any of these lines in a script
  // that makes use of the libraries. Even DO NOT PROGRAMMATICALLY LAUNCH 
  // this script from other scripts, e.g. with:
  //    gROOT->ProcessLine(".x loadlibraries.cc")
  // if this script uses the libraries.
  // To make the long story short, starting with ROOT6, libraries becomes 
  // REALLY LOADED AND AVAILABLE ONLY WHEN YOU ARE BACK TO THE ROOT PROMPT
  // at the end of main script. A workaround (not tried so far) has been 
  // introduced in ROOT6 v6.04 (see release note)

  gSystem->CompileMacro("Xe1tTpcPeak.cpp","kgf","Xe1tTpcPeak");
  gSystem->CompileMacro("Xe1tTpcEvent.cpp","kgf","Xe1tTpcEvent");
}
