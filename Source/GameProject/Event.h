#pragma once
#include "EventBase.h"

// Event containing no information
class Event : public EventBase {
public:
	Event(EventID id);
	virtual ~Event();
protected:
	// Returns true if id is for event requiring no arguments
	virtual bool isValidID(EventID id);
};