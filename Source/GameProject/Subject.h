#pragma once
#include "stdafx.h"

class Observer;
class EventBase;

/*	Abstract class for classes which need to inform observers of events
	that occurred. Subjects should use an EventManager object to 
	implement these methods.
*/
class Subject
{
public:
	Subject() {};
	virtual ~Subject() {};

	virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
	virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
	virtual void clearObservers() = 0;
	virtual void notifyObservers(EventBase* event) = 0;
	virtual bool isSubscribed(const Observer* observer) const = 0;
};

