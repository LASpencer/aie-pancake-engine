#include "stdafx.h"
#include "EventManager.h"
#include "Observer.h"
#include "Event.h"

EventManager::EventManager() : m_owner(nullptr)
{
}

EventManager::EventManager(Subject * owner) : m_owner(owner)
{
}


EventManager::~EventManager()
{
	Event wasDestoyed(EventBase::destroyed);
	notifyObservers(&wasDestoyed);
}

void EventManager::addObserver(std::shared_ptr<Observer> observer)
{
	// Check if observer is already in list
	bool observerInList = false;
	std::vector<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (it->expired()) {
			// Remove expired observers
			it = m_observers.erase(it);
		}
		else {
			std::shared_ptr<Observer> current(*it);
			if (observer.get() == current.get()) {
				observerInList = true;
				break;
			}
			++it;
		}
	}
	if (!observerInList) {
		// Check if observer accepts subscription
		if (observer->addSubject(m_owner)) {
			// Add new observer to list
			m_observers.push_back(observer);
		}
	}
}

void EventManager::removeObserver(std::shared_ptr<Observer> observer)
{
	// Find observer in list
	std::vector<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (it->expired()) {
			// Remove expired observers
			it = m_observers.erase(it);
		}
		else {
			std::shared_ptr<Observer> current(*it);
			if (observer.get() == current.get()) {
				// Inform subject it is being removed
				observer->removeSubject(m_owner);
				m_observers.erase(it);
				break;
			}
			++it;
		}
	}
}

void EventManager::clearObservers()
{
	// Inform subjects they are to be removed
	for (std::weak_ptr<Observer> observer : m_observers) {
		if (!observer.expired()) {
			std::shared_ptr<Observer> subscriber(observer);
			subscriber->removeSubject(m_owner);
		}
	}
	m_observers.clear();
}

void EventManager::notifyObservers(EventBase* event)
{
	std::vector<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		std::shared_ptr<Observer> observer = it->lock();
		if (!observer) {
			// Remove expired observers
			it = m_observers.erase(it);
		}
		else {
			// Notify observer of event, with owner as its origin
			observer->notify(m_owner, event);
			++it;
		}
	}
}

bool EventManager::isSubscribed(const Observer * observer) const
{
	// Find observer in list
	std::vector<std::weak_ptr<Observer>>::const_iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		std::shared_ptr<Observer> current = it->lock();
		if (observer == current.get()) {
			return true;
		}
		++it;
	}
	return false;
}

void EventManager::setOwner(Subject * owner)
{
	m_owner = owner;
}
