#ifndef RANGETEST_H
#define RANGETEST_H

#include "UniqueRangeSet.h"

namespace util {
  
  namespace range {

    enum MergeErrorType_t {
      kMergeNoError,
      kMergeInclusive,
      kMergeHalfOverlap,
      kMergeExclusive
    };

    /// bench-mark func: for util::UniqueRangeSet::Insert function
    double bmark_insert(const size_t nentries);
    
    /// bench-mark func: for util::Range::Exclude
    double bmark_exclude(const size_t nentries);

    /// testing overlap
    MergeErrorType_t test_overlap();
  }
}
#endif
