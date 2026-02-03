#include "Wall.h"
#include "Player.h"
#include <set>

#pragma once
class Projectile
{
private:
	Wall wall;
	double angle;
	double length;
	double speed;
	double distance;

public:
	Projectile(const Player&, Walls&);

	Projectile& operator=(const Projectile&);

	friend struct Projectiles;

	Wall createExplosion(Player&, const SDL_FPoint&);
};

struct Projectiles
{
	std::vector<Projectile> projectiles;

	void move(Walls&, Player&, const Walls&);
};