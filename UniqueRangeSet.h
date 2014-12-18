#ifndef UNIQUERANGESET_H
#define UNIQUERANGESET_H

#include <set>
#include <iostream>
#include <exception>
#include "Range.h"

namespace util {

  /**
     \class UniqueRangeSet
     std::set<range> w/ modified insert function. Original std::set
     does not allow modification of element. I assume what we're interested
     in is "find if the range already exists, and merge if it exists". The
     insert function does that by recursively looking up overlapping elements
     w.r.t. input argument of insert function.
  */
  template <class T>
  class UniqueRangeSet : public std::set<util::Range<T> > {
  public:
    UniqueRangeSet(){}

    ~UniqueRangeSet(){}

    UniqueRangeSet<T> Exclusive(const T start, const T end)
    {
      UniqueRangeSet<T> res;
      auto tmp = Range<T>(start,end);
      
      for(auto const& s : (*this)) {
	
	//std::cout<<"Inspecting: "<<s._window.first << " : " << s._window.second << std::endl;
	
	if(res.size() == this->size()+1) break;
	
	if(tmp._window.first == tmp._window.second) break;
	
	if(s < tmp) continue;
	
	if(tmp < s) { res.insert(s); break; }

	// Inclusive (1)
	if(tmp._window.first <= s._window.first && s._window.second <= tmp._window.second) {
	  if(tmp._window.first != s._window.first) res.emplace(tmp._window.first,s._window.first);
	  tmp._window.first=s._window.second;
	  continue;
	}
	
	// Inclusive (2)
	if(s._window.first <= tmp._window.first && tmp._window.second <= s._window.second) break;
	
	// Half-overlap (1)
	if(tmp._window.first < s._window.first) {
	  if(tmp._window.first != s._window.first) res.emplace(tmp._window.first,s._window.first);
	  break;
	}
	
	// Half-overlap (2)
	if(s._window.first <= tmp._window.first) {
	  tmp._window.first = s._window.second;
	}
      }
      return res;
    }
    
    /// Modified insert that merges overlapping range. Return = # merged range.
    size_t emplace(const T& start,const T& end) {
      
      auto res = std::set<util::Range<T> >::emplace(start,end);
      if(res.second) return 0;
      
      auto& iter = res.first;
      auto tmp_a = Range<T>(start,end);
      size_t ctr=0;
      while(iter != this->end()) {
	tmp_a.Merge((*iter));
	this->erase(iter);
	iter = this->find(tmp_a);
	++ctr;
      }
      this->insert(tmp_a);
      return ctr;
    }

    /// Modified insert that merges overlapping range. Return = # merged range.
    size_t insert(const Range<T>& a)
    {return emplace(a._window.first,a._window.second);}

  };
}

#endif
