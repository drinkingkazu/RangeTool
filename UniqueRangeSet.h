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

    void Merge(const UniqueRangeSet<T>& in)
    { for(auto const& r : in) emplace(r._window.first,r._window.second); }

    UniqueRangeSet<T> Exclusive(const T start, const T end) const
    {
      UniqueRangeSet<T> res;

      auto start_iter = std::lower_bound(this->begin(),this->end(),start);
      auto end_iter   = std::lower_bound(this->begin(),this->end(),end);
      
      // Anything to add to the head?
      if(start < (*start_iter)._window.first) res.emplace(start,(*start_iter)._window.first);

      auto iter = start_iter;
      T  tmp_end=end;
      while(iter != this->end()) {
	if(iter != start_iter)
	  res.emplace(tmp_end,(*iter)._window.first);
	tmp_end   = (*iter)._window.second;
	if(iter == end_iter) break;
	++iter;
      }

      // Anything to add to the tail?
      if(tmp_end < end) 
	res.emplace(tmp_end,end);

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
