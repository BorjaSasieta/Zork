#include <iostream>
#include "room.h"
#include "exit.h"

// ----------------------------------------------------
Exit::Exit(const char* name, const char* opposite_name, const char* description, Room* origin, Room* destination, bool one_way) :
	Entity(name, description, (Entity*)origin),
	closed(false), locked(false), key(NULL), one_way(one_way), destination(destination), opposite_name(opposite_name)
{
	type = EXIT;

	if (one_way == false)
		destination->container.push_back(this);
}

// ----------------------------------------------------
Exit::~Exit()
{
}


// ----------------------------------------------------
void Exit::Look() const
{
	cout << name << " to " << opposite_name << "\n";
	cout << description << "\n";
}

// ----------------------------------------------------
const string& Exit::GetNameFrom(const Room* room) const
{
	string ret;
	if (room == parent)
		ret = name;
	if (room == destination)
		ret = opposite_name;
	return ret;
}

// ----------------------------------------------------
Room* Exit::GetDestinationFrom(const Room* room) const
{
	Room* ret = NULL;
	if (room == parent)
		ret = destination;
	if (room == destination)
		ret = (Room*)parent;

	return ret;
}