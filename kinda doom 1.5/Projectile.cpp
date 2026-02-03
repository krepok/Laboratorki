#include "Projectile.h"

Projectile::Projectile(const Player& player, Walls& walls)
	: angle{ player.angle }, length{ 150 }, speed{ 30 }, distance{ 0 }
{
	wall.p1.x = player.texture.x + player.texture.w / 2 + cos((angle + 90) * std::numbers::pi / 180) * 20;
	wall.p1.y = player.texture.y + player.texture.h / 2 + sin((angle + 90) * std::numbers::pi / 180) * 20;

	wall.p2.x = wall.p1.x + cos(angle * std::numbers::pi / 180) * length;
	wall.p2.y = wall.p1.y + sin(angle * std::numbers::pi / 180) * length;

	wall.wallpaper = IMG_LoadTexture(player.renderer, "assets/laser3.png");

	wall.isGIF = false;
	walls.walls.push_back(wall);
}

Projectile& Projectile::operator=(const Projectile& pr)
{
	this->wall = pr.wall;
	this->angle = pr.angle;
	this->length = pr.length;
	this->speed = pr.speed;
	this->distance = pr.distance;
	return *this;
}

void Projectiles::move(Walls& walls, Player& player, const Walls& collision)
{
	static std::map<int, size_t> explosions;
	static int counterExp{};
	counterExp = (counterExp + 1) % 16;

	walls.walls.erase(walls.walls.end() - projectiles.size(), walls.walls.end());
	size_t initialSize{ walls.walls.size() };

	int counter{};
	std::set<size_t> toDelete;

	for (auto& pr : projectiles)
	{
		size_t size1{ toDelete.size() };

		if (pr.distance >= 5000)
		{
			toDelete.insert(counter);
		}

		for (const auto& wall : collision.walls)
		{
			double a1 = wall.p2.y - wall.p1.y;
			double b1 = wall.p1.x - wall.p2.x;
			double c1 = -wall.p1.x * wall.p2.y + wall.p1.y * wall.p2.x;

			double a2 = pr.wall.p2.y - pr.wall.p1.y;
			double b2 = pr.wall.p1.x - pr.wall.p2.x;
			double c2 = -pr.wall.p1.x * pr.wall.p2.y + pr.wall.p1.y * pr.wall.p2.x;

			double det = a1 * b2 - a2 * b1;
			double detX = -c1 * b2 + c2 * b1;
			double detY = -a1 * c2 + a2 * c1;

			if (det == 0 && detX == 0 && detY == 0)
			{
				toDelete.insert(counter);
				break;
			}
			else if (det == 0)
			{
				continue;
			}

			float x = detX / det;
			float y = detY / det;
			SDL_FPoint p{ x, y };


			double lambda1;
			double lambda2;
			
			if (wall.p2.x - wall.p1.x != 0)
			{
				lambda1 = (x - wall.p1.x) / (wall.p2.x - x);
			}
			else
			{
				lambda1 = (y - wall.p1.y) / (wall.p2.y - y);
			}

			if (pr.wall.p2.y - pr.wall.p1.y != 0)
			{
				lambda2 = (y - pr.wall.p1.y) / (pr.wall.p2.y - y);
			}
			else
			{
				lambda2 = (x - pr.wall.p1.x) / (pr.wall.p2.x - x);
			}

			if (lambda1 >= 0 && lambda2 >= 0)
			{
				toDelete.insert(counter);
				Wall exp{ pr.createExplosion(player, p) };
				//std::cout << initialSize << ' ' << explosions.size() << '\n';

				if (initialSize == walls.walls.size())
					walls.walls.push_back(exp);
				else
					walls.walls.insert(walls.walls.begin() + initialSize, exp);

				if (counterExp == 0)
				{
					explosions[15] += 1;
				}
				else
				{
					explosions[counterExp - 1] += 1;
				}

				break;
			}
		}

		counter++;

		if (size1 == toDelete.size())
		{
			pr.distance += pr.speed;
			pr.wall.p1.x += cos(pr.angle * std::numbers::pi / 180) * pr.speed;
			pr.wall.p2.x += cos(pr.angle * std::numbers::pi / 180) * pr.speed;

			pr.wall.p1.y += sin(pr.angle * std::numbers::pi / 180) * pr.speed;
			pr.wall.p2.y += sin(pr.angle * std::numbers::pi / 180) * pr.speed;

			walls.walls.push_back(pr.wall);
		}
	}

	for (const auto& del : toDelete)
	{
		projectiles.erase(projectiles.begin() + del);
	}

	int cn{ -1 };
	for (auto& [c, size] : explosions)
	{
		if (counterExp == c)
		{
			for (int i = 0; i < size; i++)
			{
				walls.walls.erase(walls.walls.end() - projectiles.size() - explosions.size() + i);
			}
			cn = c;
		}
	}
	explosions.erase(cn);

	player.getPoints(walls);
}

Wall Projectile::createExplosion(Player& player, const SDL_FPoint& p)
{
	SDL_FPoint p1{ p.x - cos(player.angle * std::numbers::pi / 180) * 5 + cos((player.angle + 90) * std::numbers::pi / 180) * 50, p.y - sin(player.angle * std::numbers::pi / 180) * 5 + sin((player.angle + 90) * std::numbers::pi / 180) * 50 };
	SDL_FPoint p2{ p.x - cos(player.angle * std::numbers::pi / 180) * 5 - cos((player.angle + 90) * std::numbers::pi / 180) * 50, p.y - sin(player.angle * std::numbers::pi / 180) * 5 - sin((player.angle + 90) * std::numbers::pi / 180) * 50 };
	Wall explosion{ p1, p2, "assets/explosion (7).png", {0, 0, 64, 64}, 16, 16, player.renderer };
	std::cout << "Exp\n";

	return explosion;
}
