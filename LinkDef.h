//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace util+;
//#pragma link C++ class util::Range<size_t>+;
#pragma link C++ class util::UniqueRangeSet<size_t>+;
#pragma link C++ class util::UniqueRangeSet<double>+;
#pragma link C++ class util::Range<size_t>+;
#pragma link C++ class util::Range<double>+;
#pragma link C++ function util::bmark_range_insert(const size_t)+;
#pragma link C++ function util::bmark_range_exclude(const util::UniqueRangeSet<double>&)+;
//ADD_NEW_CLASS ... do not change this line
#endif

