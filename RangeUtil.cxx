#ifndef RANGEBENCHMARK_CXX
#define RANGEBENCHMARK_CXX

#include "RangeUtil.h"
#include <time.h>
namespace util {
  namespace range {

    //
    // Bench-marking function
    //
    double bmark_insert(const size_t nentries)
    {
      UniqueRangeSet<size_t> range_set;
      clock_t time_sum = 0;
      for(size_t i=0; i<nentries; ++i) {
	clock_t time_start = clock();
	range_set.emplace(4*i,4*i+3);
	time_sum += clock() - time_start;
      }
      return (range_set.size() == nentries ? ((double)time_sum)/CLOCKS_PER_SEC : -1);
    }
    
    double bmark_exclude(const size_t nentries)
    {
      UniqueRangeSet<double> sample;
      for(size_t i=0; i<nentries; ++i)
	sample.emplace((double)(4*i),(double)(4*i+3));

      auto const& start = (*sample.begin()).Start();
      auto const& end   = (*sample.rbegin()).End();

      clock_t time_start = clock();
      auto res = sample.Exclusive( (start - (end - start)*0.1),
				   (end + (end - start)*0.1) );
      clock_t time_end = clock();
      if( res.size() != (nentries + 1) ) return -1;
      return ((double)(time_end - time_start))/CLOCKS_PER_SEC;
    }
  }  
}
#endif
