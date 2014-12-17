#ifndef RANGE_CXX
#define RANGE_CXX

#include "Range.h"
namespace util {

  template <class T>
  UniqueRangeSet<T> Range<T>::Exclude(const UniqueRangeSet<T>& range_s) const
  {
    UniqueRangeSet<T> res;
    auto tmp = (*this);
    for(auto const& s : range_s) {

      if(res.size() == range_s.size()+1) break;

      if(tmp.first == tmp.second) break;

      if(s < tmp) continue;

      if(tmp < s) { res.insert(s); break; }

      // Inclusive (1)
      if(tmp.first <= s.first && s.second <= tmp.second) {
	if(tmp.first != s.first) res.emplace(tmp.first,s.first);
	tmp.first=s.second;
	continue;
      }
      
      // Inclusive (2)
      if(s.first <= tmp.first && tmp.second <= s.second) break;

      // Half-overlap (1)
      if(tmp.first < s.first) {
	if(tmp.first != s.first) res.emplace(tmp.first,s.first);
	break;
      }

      // Half-overlap (2)
      if(s.first <= tmp.first) {
	tmp.first = s.second;
      }
    }

    return res;
  }
}
#endif
