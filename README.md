# PeaksAndHigher

A skeleton data layout for XENON1T as a class-based ROOT TTree. Advanced features like TObject allocators, TClonesArray, TRef, TRefArrays are tested to qualify this approach. More stuff can be investigated later, but the answer if these ones fit our needs and are performant is the first priority.

The concepts coming from PAX are implemented in classes, from "Hits" up to "Peaks", then "Higher"-level concepts like "Interactions" (coming from the pairing of one S1 and one S2). If this is satisfying, others like "BiPo", etc.. can be added, providing a reconstruction framework to the analysis
