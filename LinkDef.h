//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Classes
#pragma link C++ namespace util+;
#pragma link C++ class util::Range<int>+;
#pragma link C++ class util::Range<size_t>+;
#pragma link C++ class util::Range<double>+;
#pragma link C++ class util::UniqueRangeSet<int>+;
#pragma link C++ class util::UniqueRangeSet<size_t>+;
#pragma link C++ class util::UniqueRangeSet<double>+;

// Functions
#pragma link C++ namespace util::range+;
#pragma link C++ function util::range::bmark_insert(const size_t)+;
#pragma link C++ function util::range::bmark_exclude(const util::UniqueRangeSet<double>&)+;
//ADD_NEW_CLASS ... do not change this line
#endif

