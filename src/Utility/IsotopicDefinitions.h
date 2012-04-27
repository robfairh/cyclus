// IsotopicDefinitions.h
#if !defined(_ISOTOPICDEFINITIONS_H)
#define _ISOTOPICDEFINITIONS_H

#include <map>
#include "boost/shared_ptr.hpp"

/* -- Useful Definitions -- */
/**
   avagadro's number
*/
#define AVOGADRO 6.02e23

/**
   smallest kilogram value
*/
#define EPS_KG 1e-6

/**
   smallest percent
*/
#define EPS_PERCENT 1e-14
/* -- */

/* -- Useful Typedefs -- */
/**
   Isotope integer, ZZZAAA
 */
typedef int Iso;

/**
   map of isotope integer to value (mass or atom)
   and a pointer to said map
 */
typedef std::map<Iso, double> CompMap;
typedef boost::shared_ptr<CompMap> CompMap_p;

/**
   a pointer to a composition
 */
struct comp_t;
typedef boost::shared_ptr<comp_t> comp_p;
/* -- */

/* -- Useful Structs -- */
/**
   a container fully describing an isotopic composition

   this container is responsible for managing the memory of its
   mass_fractions member. this responsibility is implied through the
   logging process: a composition is given an id when it is logged.
 */
struct comp_t {
  // members
  int ID;
  CompMap_p mass_fractions;
  comp_p parent;
  int decay_time;

  // constructors & destructor
  comp_t() {
    CompMap_p cp(new CompMap);
    init(cp);
  }
  comp_t(CompMap_p fracs) {
    init(fracs);
  }
  comp_t(const comp_t& other) {
    copy(other);
  }
  ~comp_t() {
    mass_fractions.reset();
    parent.reset();
  }
  
  // operators
  comp_t& operator=(const comp_t& other) {
    if (this != &other) {
      copy(other);
    }
    return *this;
  };
  bool operator==(const comp_t& other) const {
    return (ID == other.ID);
  }
  bool operator!=(const comp_t& other) const {
    return !(*this == other);
  }
  bool operator<(const comp_t& other) const {
    return (ID < other.ID);
  }
  bool operator<(const comp_p& other) const {
    return (*this < *other);
  }

  // utility
  void init(CompMap_p fracs) {
    comp_p cp(new comp_t);
    ID = 0;
    mass_fractions = fracs; // ptr copy
    parent = cp; // ptr copy
    decay_time = 0;
  }
  void copy(const comp_t& other) {
    ID = other.ID;
    mass_fractions = other.mass_fractions; // ptr copy
    parent = other.parent; // ptr copy
    decay_time = other.decay_time;
  }
  bool logged() {
    return (ID > 0 && mass_fractions != 0);
  }
  void normalize() {
    double total = 0.0;
    for (CompMap::iterator it = mass_fractions->begin(); it != mass_fractions->end(); it++) {
      total += it->second;
    }
    for (CompMap::iterator it = mass_fractions->begin(); it != mass_fractions->end(); it++) {
      it->second /= total;
    }
  }
};
/* -- */

#endif
