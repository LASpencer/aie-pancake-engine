#include "stdafx.h"
#include "EventBase.h"



EventBase::EventBase(EventID id) : m_id(id)
{
}

EventBase::~EventBase()
{
}

EventBase::EventID EventBase::getEventID()
{
	return m_id;
}
