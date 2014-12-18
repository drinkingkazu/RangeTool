#ifndef RANGEUTIL_H
#define RANGEUTIL_H

#include "UniqueRangeSet.h"

namespace util {
  
  namespace range {

    /// bench-mark func: for util::UniqueRangeSet::Insert function
    double bmark_insert(const size_t nentries);
    
    /// bench-mark func: for util::Range::Exclude
    double bmark_exclude(const size_t nentries);
  }
}
#endif
