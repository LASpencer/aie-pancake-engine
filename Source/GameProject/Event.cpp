#include "stdafx.h"
#include "Event.h"

Event::Event(EventID id) : EventBase(id)
{
	if (!isValidID(id)) {
		throw std::invalid_argument("Invalid event ID");
	}
}

Event::~Event()
{
}

bool Event::isValidID(EventID id)
{
	// These events need no additional information
	// beyond the subject producing them
	return	id == destroyed ||
		id == state_entered ||
		id == state_exited ||
		id == gain_focus ||
		id == lose_focus ||
		id == mouse_over ||
		id == mouse_exit;
}
