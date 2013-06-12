// EventBackend.h
#if !defined(_EVENTBACKEND_H)
#define _EVENTBACKEND_H

#include "Event.h"
#include <vector>
#include <boost/intrusive_ptr.hpp>

typedef boost::intrusive_ptr<Event> event_ptr;
typedef std::vector<event_ptr> EventList;

/*!
An abstract base class for listeners (e.g. output databases) that want
to receive data generated by the simulation.
*/
class EventBackend {
  public:

    /// Used to pass a list of new/collected events
    virtual void notify(EventList events) = 0;

    /*!
    Used to uniquely identify a backend - particularly if there are more
    than one in a simulation.
    */
    virtual std::string name() = 0;

    /*!
    Used to notify the backend that no more events will be sent (i.e.
    the simulatoin is over).
    */
    virtual void close() = 0;
};

#endif