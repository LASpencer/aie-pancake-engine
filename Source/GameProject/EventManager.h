#pragma once
#include "Subject.h"

/*	Used by other Subjects to avoid multiple inheritance
	Owning subject implements its methods by calling an 
	EventManager's method. */
class EventManager :
	public Subject
{
public:
	EventManager();
	EventManager(Subject* owner);
	~EventManager();

	// Adds new observer
	virtual void addObserver(std::shared_ptr<Observer> observer);

	// Removes observer
	virtual void removeObserver(std::shared_ptr<Observer> observer);

	// Clears all observers from array
	virtual void clearObservers();

	/** Sends event to all observers
	*	@param event Event to inform observers of*/
	virtual void notifyObservers(EventBase* event);

	/** Tests if observer is in array
	*	@param observer observer to look for
	*	@return true if observer found*/
	virtual bool isSubscribed(const Observer* observer) const;

	void setOwner(Subject* owner);

protected:
	std::vector<std::weak_ptr<Observer>> m_observers;
	Subject* m_owner;
};

