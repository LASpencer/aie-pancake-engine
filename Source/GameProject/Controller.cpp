#include "stdafx.h"
#include "Controller.h"

Controller::Controller() : Component()
{
}

Controller::~Controller()
{
}

Controller::Identifier Controller::getID()
{
	return controller;
}
