#include <iostream>
#include "comunicate.h"
#include "creature.h"
#include "exit.h"
#include "item.h"
#include "room.h"


// ----------------------------------------------------
Room::Room(const char* title, const char* description) :
	Entity(title, description, NULL)
{
	type = ROOM;
}

// ----------------------------------------------------
Room::~Room()
{
}

// ----------------------------------------------------
void Room::Look() const
{
	cout << "\n" << name << "\n";
	cout << description;

	// List exits --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
		}
	}

	// List items --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == ITEM)
		{
			Item* item = (Item*)*it;
			cout << "\nThere is an item here: " << item->name;
		}
	}

	// List creatures --
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == CREATURE)
		{
			Creature* cr = (Creature*)*it;
			cout << "\nThere is someone else here: " << cr->name;
		}
	}

	cout << "\n";
}

// ----------------------------------------------------
Exit* Room::GetExit(const string& direction) const
{
	Exit* ret = NULL;
 	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == EXIT)
		{
			Exit* ex = (Exit*)*it;
			const char* aux = ex->GetNameFrom(this);
			if (Same(direction, aux)) {
				ret = ex;
			}				
		}
	}

	return ret;
}