#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <time.h>
#include "comunicate.h"
#include "Entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"

#define TICK_FREQUENCY 0.5f

using namespace std;

class World
{
public:

	World();
	~World();

	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	void GameLoop();

private:

	clock_t tick_timer;
	list<Entity*> entities;
	Player* player;
	
};

#endif //__World__
