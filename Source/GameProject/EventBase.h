#pragma once

//  Abstract base class for Event objects.
class EventBase {
public:
	// Types of events that can be created
	enum EventID {
		destroyed,			//Subject was destroyed
		state_entered,		//State was entered
		state_exited,		//State was exited
		gain_focus,			//State gained focus
		lose_focus,			//State lost focus
		mouse_over,			//The mouse cursor is over the subject
		mouse_exit,			//The mouse cursor has left the subject
		clicked,			//The subject was clicked
		mouse_release,		//A mouse button was released
		collision,			//Collision occurred
		terrain_collision	//Collision between entity and terrain

	};

	EventBase(EventID id);
	virtual ~EventBase();

	EventID getEventID();

protected:
	EventID m_id;
	// Check if event id is possible for concrete class
	virtual bool isValidID(EventID id) = 0;
};