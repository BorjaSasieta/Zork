#include <iostream>
#include "comunicate.h"
#include "Entity.h"

// ----------------------------------------------------
Entity::Entity(const char* name, const char* description, Entity* parent = NULL) :
	name(name), description(description), parent(parent)
{
	type = ENTITY;

	if (parent != NULL)
		parent->container.push_back(this);
}

// ----------------------------------------------------
Entity::~Entity()
{}

// ----------------------------------------------------
void Entity::Look() const
{
	cout << name << "\n";
	cout << description << "\n";
}

// ----------------------------------------------------
void Entity::Tick()
{}

// ----------------------------------------------------
void Entity::ChangeParentTo(Entity* new_parent)
{
	if (parent != NULL)
		parent->container.remove(this);

	parent = new_parent;

	if (parent != NULL)
		parent->container.push_back(this);
}

// ----------------------------------------------------
bool Entity::Find(Entity* entity) const
{
	bool ret = false;
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it) == entity)
			ret = true;
	}

	return ret;
}

// ----------------------------------------------------
Entity* Entity::Find(EntityType type) const
{
	Entity* ret = NULL;
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == type)
			ret = *it;
	}

	return ret;
}

// ----------------------------------------------------
Entity* Entity::Find(const string& name, EntityType type) const
{
	Entity* ret = NULL;
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == type)
		{
			if (Same((*it)->name, name))
				ret = *it;
		}
	}

	return ret;
}

// ----------------------------------------------------
void Entity::FindAll(EntityType type, list<Entity*>& list_to_fill) const
{
	for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	{
		if ((*it)->type == type)
			list_to_fill.push_back(*it);
	}
}