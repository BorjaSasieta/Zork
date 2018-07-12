#include <iostream>
#include "comunicate.h"
#include "creature.h"

// ----------------------------------------------------
Creature::Creature(const char* title, const char* description) :
	Entity(title, description, NULL)
{
	type = CREATURE;
	hit_points = 1;
	min_damage = max_damage = min_protection = max_protection = 0;
	combat_target = NULL;
}

// ----------------------------------------------------
Creature::~Creature()
{}

// ----------------------------------------------------
void Creature::Look(const vector<string>& args) const
{
	cout << name << "\n";
	cout << description << "\n";
	
}

// ----------------------------------------------------
bool Creature::Go(const vector<string>& args)
{
	bool ret = false;

	return ret;
}

// ----------------------------------------------------
bool Creature::Take(const vector<string>& args)
{
	bool ret = false;

	

	
	return ret;
}

// ----------------------------------------------------
void Creature::Inventory() const
{
	list<Entity*> items;
	FindAll(ITEM, items);

	if (items.size() == 0)
	{
		cout << name << " does not own any items\n";
		return;
	}

	cout << "\n" << name << " owns:\n";
}

// ----------------------------------------------------
bool Creature::Equip(const vector<string>& args)
{
	bool ret = false;

	

	return ret;
}

// ----------------------------------------------------
bool Creature::UnEquip(const vector<string>& args)
{
	bool ret = false;



	return ret;
}


// ----------------------------------------------------
bool Creature::AutoEquip()
{
	bool ret = false;



	return ret;
}

// ----------------------------------------------------
bool Creature::Lock(const vector<string>& args)
{
	bool ret = false;



	return ret;
}

// ----------------------------------------------------
bool Creature::UnLock(const vector<string>& args)
{
	bool ret = false;



	return ret;
}

// ----------------------------------------------------
bool Creature::Drop(const vector<string>& args)
{
	bool ret = false;



	return ret;
}

// ----------------------------------------------------
void Creature::Tick()
{
	if (combat_target != NULL)
	{
		if (parent->Find(combat_target) == true)
			MakeAttack();
		else
			combat_target = NULL;
	}
}

// ----------------------------------------------------
bool Creature::Attack(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	if (target == NULL)
		return false;

	combat_target = target;
	cout << "\n" << name << " attacks " << target->name << "!\n";
	return true;
}

// ----------------------------------------------------
int Creature::MakeAttack()
{
	int result = 0;

	return result;
}

// ----------------------------------------------------
int Creature::ReceiveAttack(int damage)
{
	int received;

	return received;
}

// ----------------------------------------------------
void Creature::Die()
{
	cout << name << " dies.\n";
}

// ----------------------------------------------------
bool Creature::Loot(const vector<string>& args)
{
	Creature *target = (Creature*)parent->Find(args[1], CREATURE);

	bool ret = false;

	cout << "\n" << name << " loots " << target->name << "'s corpse\n";

	return ret;
}

// ----------------------------------------------------
void Creature::Stats() const
{
	cout << "\nHit Points: " << hit_points;
	
	cout << "\n";
}