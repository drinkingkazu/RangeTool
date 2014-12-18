#ifndef RANGE_H
#define RANGE_H

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
    
    /// Ordering w/ another Range
    inline bool operator< (const Range& rhs) const
    {return ( _window.second < rhs.Start() ); }
    inline bool operator> (const Range& rhs) const
    {return ( _window.first > rhs.End() ); }
    inline bool operator==(const Range& rhs) const
    {return ( _window.first == rhs.Start() && _window.second == rhs.End() ); }
    inline bool operator!=(const Range& rhs) const
    {return !( (*this) == rhs ); }

    // Ordering w/ T
    inline bool operator< (const T& rhs) const
    {return (_window.second < rhs); }
    inline bool operator> (const T& rhs) const
    {return (_window.first > rhs); }

    /// Merging utility
    void Merge(const Range& a) {
      _window.first  = std::min( _window.first,  a.Start() );
      _window.second = std::max( _window.second, a.End()   );
    }

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

#endif
