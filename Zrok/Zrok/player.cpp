#include <iostream>
#include "comunicate.h"
#include "player.h"
#include "exit.h"
#include "item.h"
#include "room.h"

// ----------------------------------------------------
Player::Player(const char* title, const char* description, Room* room) :
	Creature(title, description, room)
{
	type = PLAYER;
}

// ----------------------------------------------------
Player::~Player()
{
}

// ----------------------------------------------------
void Player::Look(const vector<string>& args) const
{
	if (args.size() > 1)
	{
		for (list<Entity*>::const_iterator it = parent->container.begin(); it != parent->container.cend(); ++it)
		{
			if (Same((*it)->name, args[1]) || ((*it)->type == EXIT && Same(args[1], ((Exit*)(*it))->GetNameFrom((Room*)parent))))
			{
				(*it)->Look();
				return;
			}
		}

		if (Same(args[1], "me"))
		{
			cout << "\n" << name << "\n";
			cout << description << "\n";
		}
	}
	else
	{
		parent->Look();
	}
}

// ----------------------------------------------------
bool Player::Go(const vector<string>& args)
{
	bool ret = true;
	Exit* exit = GetRoom()->GetExit(args[1]);

	if (exit == NULL)
	{
		cout << "\nThere is no exit at '" << args[1] << "'.\n";
		ret = false;
	}

	else if (exit->locked)
	{
		cout << "\nThat exit is locked.\n";
		ret = false;
	}

	else {

		cout << "\nYou take direction " << exit->GetNameFrom((Room*)parent) << "...\n";
		ChangeParentTo(exit->GetDestinationFrom((Room*)parent));
		parent->Look();
	}

	return ret;
}


// ----------------------------------------------------
bool Player::Take(const vector<string>& args)
{
	if (args.size() == 4)
	{
		Item* item = (Item*)parent->Find(args[3], ITEM);

		// we could pick something from a container in our inventory ...
		if (item == NULL) {
			item = (Item*)Find(args[3], ITEM);
			cout << "\nCannot find '" << args[3] << "' in this room or in your inventory.\n";
		}

		else {
			Item* subitem = (Item*)item->Find(args[1], ITEM);

			if (subitem == NULL)
			{
				cout << "\n" << item->name << " does not contain '" << args[1] << "'.\n";
			}
			else {
				cout << "\nYou take " << subitem->name << " from " << item->name << ".\n";
				subitem->ChangeParentTo(this);
			}
		}		
	}
	else if (args.size() == 2)
	{
		Item* item = (Item*)parent->Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item here with that name.\n";
		}

		else {
			cout << "\nYou take " << item->name << ".\n";
			item->ChangeParentTo(this);
		}
	}

	return false;
}

// ----------------------------------------------------
void Player::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << "\nYou do not own any item.\n";
	}
	
	else if(items.size > 0){
		for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
		{
			if (*it == weapon)
				cout << "\n" << (*it)->name << " (as weapon)";
			else if (*it == armour)
				cout << "\n" << (*it)->name << " (as armour)";
			else
				cout << "\n" << (*it)->name;
		}
	}	

	cout << "\n";
}

// ----------------------------------------------------
bool Player::Drop(const vector<string>& args)
{
	bool ret = false;


	if (args.size() == 2)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nThere is no item on you with that name.\n";
		}

		else {
			cout << "\nYou drop " << item->name << "...\n";
			item->ChangeParentTo(parent);
			ret = true;
		}
	}
	else if (args.size() == 4)
	{
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\nCan not find '" << args[1] << "' in your inventory.\n";
		}

		else {
			Item* container = (Item*)parent->Find(args[3], ITEM);

			if (container == NULL)
			{
				container = (Item*)Find(args[3], ITEM);
				cout << "\nCan not find '" << args[3] << "' in your inventory or in the room.\n";
			}

			else {
				cout << "\nYou put " << item->name << " into " << container->name << ".\n";
				item->ChangeParentTo(container);
				ret = true;
			}
		}
	}

	return ret;
}

// ----------------------------------------------------
bool Player::Equip(const vector<string>& args)
{
	bool ret = true;

	Item* item = (Item*)Find(args[1], ITEM);

	if (item == NULL)
	{
		cout << "\nCannot find '" << args[1] << "' is not in your inventory.\n";
		ret = false;
	}

	else {
		switch (item->item_type)
		{
		case WEAPON:
			weapon = item;
			break;

		case ARMOUR:
			armour = item;
			break;

		default:
			cout << "\n" << item->name << " cannot be equipped.\n";
			ret = false;
		}
		cout << "\nYou equip " << item->name << "...\n";
	}	

	return ret;
}

// ----------------------------------------------------
bool Player::UnEquip(const vector<string>& args)
{
	bool ret = true;

	if (!IsAlive())
		ret = false;

	else {
		Item* item = (Item*)Find(args[1], ITEM);

		if (item == NULL)
		{
			cout << "\n" << item->name << " is not in your inventory.\n";
			ret = false;
		}

		else {
			if (item == weapon) {
				cout << "\nYou un-equip " << item->name << "...\n";
				weapon = NULL;
			}
				
			else if (item == armour) {
				cout << "\nYou un-equip " << item->name << "...\n";
				armour = NULL;
			}
				
			else
			{
				cout << "\n" << item->name << " is not equipped.\n";
				ret = false;
			}
			
		}		
	}	

	return ret;
}

// ----------------------------------------------------
bool Player::Examine(const vector<string>& args) const
{
	bool ret = true;
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		ret = false;
	}

	else {
		target->Inventory();
		target->Stats();
	}	

	return ret;
}

// ----------------------------------------------------
bool Player::Attack(const vector<string>& args)
{
	bool ret = true;
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.";
		ret = false;
	}

	else {
		combat_target = target;
		cout << "\nYou jump to attack " << target->name << "!\n";
	}

	return ret;
}

// ----------------------------------------------------
bool Player::Loot(const vector<string>& args)
{
	bool ret = true;
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		ret = false;
	}

	else if (target->IsAlive() == true)
	{
		cout << "\n" << target->name << " cannot be looted until it is killed.\n";
		ret = false;
	}

	else {
		list<Entity*> items;
		target->FindAll(ITEM, items);

		if (items.size() > 0)
		{
			cout << "\nYou loot " << target->name << "'s corpse:\n";

			for (list<Entity*>::const_iterator it = items.begin(); it != items.cend(); ++it)
			{
				Item* i = (Item*)(*it);
				cout << "You find: " << i->name << "\n";
				i->ChangeParentTo(this);
			}
		}
		else
			cout << "\nYou loot " << target->name << "'s corpse, but find nothing there.\n";
	}	

	return ret;
}

// ----------------------------------------------------
bool Player::Lock(const vector<string>& args)
{
	bool ret = true;

	if (!IsAlive())
		ret = false;

	else {
		Exit* exit = GetRoom()->GetExit(args[1]);

		if (exit == NULL)
		{
			cout << "\nThere is no exit at '" << args[1] << "'.\n";
			ret = false;
		}

		else if (exit->locked == true)
		{
			cout << "\nThat exit is already locked.\n";
			ret = false;
		}

		else {
			Item* item = (Item*)Find(args[3], ITEM);

			if (item == NULL)
			{
				cout << "\nItem '" << args[3] << "' not found in your inventory.\n";
				ret = false;
			}

			else if (exit->key != item)
			{
				cout << "\nItem '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
				ret = false;
			}
			else {
				cout << "\nYou lock " << exit->GetNameFrom((Room*)parent) << "...\n";
				exit->locked = true;
			}
		}
	}
	

	return ret;
}

// ----------------------------------------------------
bool Player::UnLock(const vector<string>& args)
{
	bool ret = true;

	if (!IsAlive())
		ret = false;

	else {
		Exit* exit = GetRoom()->GetExit(args[1]);

		if (exit == NULL)
		{
			cout << "\nThere is no exit at '" << args[1] << "'.\n";
			ret = false;
		}

		else if (exit->locked == false)
		{
			cout << "\nThat exit is not locked.\n";
			ret = false;
		}

		else {
			Item* item = (Item*)Find(args[3], ITEM);

			if (item == NULL)
			{
				cout << "\nKey '" << args[3] << "' not found in your inventory.\n";
				ret = false;
			}

			else if (exit->key != item)
			{
				cout << "\nKey '" << item->name << "' is not the key for " << exit->GetNameFrom((Room*)parent) << ".\n";
				ret = false;
			}

			else {
				cout << "\nYou unlock " << exit->GetNameFrom((Room*)parent) << "...\n";
				exit->locked = false;
			}
		}		
	}

	return ret;
}