#pragma once

#include <vector>
#include <list>
#include <cstdint>

//Enumeration of possible events
enum EventType {
    ObjectCreate,
    ObjectDelete,
    RenderComponentCreate,
    RenderComponentDelete,
    KeyAdvance,
    KeyBrake,
    KeyIncSpin,
    KeyDecSpin,
    KeySelect
};

//Vector containing a vector with pointers to objects
typedef std::vector<uintptr_t> EventData;

//A event contains a type and the data related to the object
struct Event {

    EventType type;
    EventData data;

};

//An event listener contains a type and a pointer to the funcion to active
struct EventListener{
    EventType listenerType;
    void (*listener)(EventData);
};

//List containig event listeners
typedef std::list<EventListener> EventListenerList;