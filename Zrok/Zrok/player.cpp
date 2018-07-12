#include <iostream>
#include "comunicate.h"
#include "player.h"

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
	bool ret = false;

	return ret;
}


// ----------------------------------------------------
bool Player::Take(const vector<string>& args)
{
	bool ret = false;

	return ret;
}

// ----------------------------------------------------
void Player::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << "\nYou do not own any item.\n";
		return;
	}

	cout << "\n";
}

// ----------------------------------------------------
bool Player::Drop(const vector<string>& args)
{
	bool ret = false;

	return ret;
}

// ----------------------------------------------------
bool Player::Equip(const vector<string>& args)
{
	bool ret = false;

	return ret;
}

// ----------------------------------------------------
bool Player::UnEquip(const vector<string>& args)
{
	bool ret = false;

	return ret;
}

// ----------------------------------------------------
bool Player::Examine(const vector<string>& args) const
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	bool ret = true;

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.\n";
		ret = false;
	}

	target->Inventory();
	target->Stats();

	return ret;
}

// ----------------------------------------------------
bool Player::Attack(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	bool ret = true;

	if (target == NULL)
	{
		cout << "\n" << args[1] << " is not here.";
		ret = false;
	}

	combat_target = target;
	cout << "\nYou jump to attack " << target->name << "!\n";
	return ret;
}

// ----------------------------------------------------
bool Player::Loot(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	bool ret = false;

	return ret;
}

// ----------------------------------------------------
bool Player::Lock(const vector<string>& args)
{
	bool ret = false;

	return ret;
}

// ----------------------------------------------------
bool Player::UnLock(const vector<string>& args)
{
	bool ret = false;

	return ret;
}