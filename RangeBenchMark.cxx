#ifndef RANGEBENCHMARK_CXX
#define RANGEBENCHMARK_CXX

#include "Range.h"
namespace util {

  //
  // Bench-marking function
  //

  bool bmark_range_insert(const size_t nentries)
  {
    UniqueRangeSet<size_t> range_set;
    for(size_t i=0; i<nentries; ++i) {
      range_set.emplace(4*i,4*i+3);
    }
    return (range_set.size() == nentries);
  }

  bool bmark_range_exclude(const UniqueRangeSet<double>& range_set)
  {
    auto const& start = (*range_set.begin()).Start();
    auto const& end   = (*range_set.rbegin()).End();

    Range<double> inclusive_range(start - (end-start)*0.1, end + (end-start)*0.1);

    return ( (range_set.size() + 1) == inclusive_range.Exclude(range_set).size() );
  }

  
}
#endif
