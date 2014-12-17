#ifndef RANGE_H
#define RANGE_H

#include <set>
#include <vector>
#include <iostream>
#include <exception>

namespace util {

  template <class T>
  class UniqueRangeSet;

  /**
     \class Range
      std::pair to represent a "Range" w/ notion of ordering.
      Note the specialization requires a template class T to have less operator
      implemented.
  */
  template <class T>
  class Range {
    friend class UniqueRangeSet<T>;

  private:
    Range(){}

  public:
    Range(const T& start,
	  const T& end)
      : _window(start,end)
    { if(start>=end) throw std::runtime_error("Inserted invalid range: end before start."); }
    
    ~Range(){}
    
    /// Intuitive accessor
    const T& Start() const { return _window.first;  }
    const T& End()   const { return _window.second; }
    /// Setter
    void Set(const T& s, const T& e)
    { 
      if(s>=e) throw std::runtime_error("Inserted invalid range: end before start."); 
      _window.first  = s;
      _window.second = e;
    }
    
    /// Ordering
    inline bool operator< (const Range& rhs) const
    {return ( _window.second < rhs.Start() ); }
    
    /// Merging utility
    void Merge(const Range& a) {
      _window.first  = std::min( _window.first,  a.Start() );
      _window.second = std::max( _window.second, a.End()   );
    }

    /// UniqueRangeSet generator for a given set of ranges
    UniqueRangeSet<T> Exclude(const UniqueRangeSet<T>& range_s) const;

  protected:
    /// Protected to avoid user's illegal modification on first/second (sorry users!)
    std::pair<T,T> _window;
  };

}

namespace std {
  // Implement pointer comparison in case it's useful
  template <class T>
  class less<util::Range<T>*>
  {
  public:
    bool operator()( const util::Range<T>* lhs, const util::Range<T>* rhs )
    { return (*lhs) < (*rhs); }
  };
}

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
    
    /// Modified insert that merges overlapping range. Return = # merged range.
    size_t Insert(const Range<T>& a) {
      
      auto res = std::set<util::Range<T> >::insert(a);
      if(res.second) return 0;
      
      auto& iter = res.first;
      auto tmp_a = a;
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

  };
}

#endif





