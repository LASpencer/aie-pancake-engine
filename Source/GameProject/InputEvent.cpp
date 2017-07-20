#include "stdafx.h"
#include "InputEvent.h"

InputEvent::InputEvent(EventID id, aie::EInputCodes inputCode) : EventBase(id), m_inputCode(inputCode)
{
	if (!isValidID(id)) {
		throw std::invalid_argument("Invalid event ID");
	}
}

InputEvent::~InputEvent()
{
}

aie::EInputCodes InputEvent::getInputCode()
{
	return m_inputCode;
}


bool InputEvent::isValidID(EventID id)
{
	// The following require an input code for mouse button clicked
	return	id == clicked ||
		id == mouse_release;
}
