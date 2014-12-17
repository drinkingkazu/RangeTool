#ifndef RANGEBENCHMARK_H
#define RANGEBENCHMARK_H

namespace util {

  /// bench-mark func: for util::UniqueRangeSet::Insert function
  bool bmark_range_insert(const size_t nentries);

  /// bench-mark func: for util::Range::Exclude
  bool bmark_range_exclude(const UniqueRangeSet<double>& range_set);
  
}
#endif
