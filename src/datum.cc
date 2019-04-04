#include "datum.h"

#include <boost/pool/singleton_pool.hpp>


namespace cyclus {

typedef boost::singleton_pool<Datum, sizeof(Datum)> DatumPool;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Datum* Datum::AddValBase(const char* field, boost::spirit::hold_any val,
                         std::vector<int>* shape) {
  vals_.push_back(std::pair<const char*, boost::spirit::hold_any>(field, val));
  std::vector<int> s;
  if (shape == NULL)
    shapes_.push_back(s);
  else
    shapes_.push_back(*shape);
  return this;
}

Datum* Datum::AddVal(const char* field, boost::spirit::hold_any val,
                     std::vector<int>* shape) {
  fields_.push_back(std::string(field));
  return AddValBase(field, val, shape);
}

Datum* Datum::AddVal(std::string field, boost::spirit::hold_any val,
                     std::vector<int>* shape) {
  fields_.push_back(field);
  return AddValBase(field.c_str(), val, shape);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Datum::Record() {
  manager_->AddDatum(this);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Datum::Datum(Recorder* m, std::string title) : title_(title), manager_(m) {
  // The (vect) size to reserve is chosen to be just bigger than most/all cyclus
  // core tables.  This prevents extra reallocations in the underlying
  // vector as vals are added to the datum.
  vals_.reserve(10);
  shapes_.reserve(10);
  fields_.reserve(10);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Datum::~Datum() {}

std::string Datum::title() {
  return title_;
}

const Datum::Vals& Datum::vals() {
  return vals_;
}

const Datum::Shapes& Datum::shapes() {
  return shapes_;
}

const Datum::Fields& Datum::fields() {
  return fields_;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void* Datum::operator new(size_t size) {
  if (size != sizeof(Datum)) {
    return ::operator new(size);
  }

  while (true) {
    void* ptr = DatumPool::malloc();
    if (ptr != NULL) {
      return ptr;
    }

    std::new_handler globalNewHandler = std::set_new_handler(0);
    std::set_new_handler(globalNewHandler);

    if (globalNewHandler) {
      globalNewHandler();
    } else {
      throw std::bad_alloc();
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Datum::operator delete(void* rawMemory) throw() {
  if (rawMemory == 0) {
    return;
  }
  DatumPool::free(rawMemory);
}

}  // namespace cyclus
