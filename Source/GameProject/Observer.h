#pragma once

class Subject;
class EventBase;

/*	Abstract class for classes observing a subject
	An Observer must implement methods allowing it to respond to 
	events it has been informed of. 
	The addSubject and removeSubject methods can be used to 
	provide conditions for accepting a subject, and any setup and
	clean up needed when following or leaving a subject.
*/
class Observer : public std::enable_shared_from_this<Observer>
{
public:
	Observer() {};
	virtual ~Observer() {};

	// Inform observer of event that occurred
	virtual void notify(Subject* subject, EventBase* event) = 0;

	// Return true if observer can follow subject
	virtual bool addSubject(Subject* subject) = 0;

	// Perform any cleanup needed when removing subject
	virtual void removeSubject(Subject* subject) = 0;
};

