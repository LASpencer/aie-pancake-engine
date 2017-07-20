#pragma once
#include "Input.h"
#include "EventBase.h"

class InputEvent : public EventBase {
public:
	InputEvent(EventID id, aie::EInputCodes inputCode);
	virtual ~InputEvent();

	aie::EInputCodes getInputCode();


protected:
	aie::EInputCodes m_inputCode;		//Code for key or mouse button causing event

	virtual bool isValidID(EventID id);
};