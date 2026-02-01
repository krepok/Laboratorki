#include "Player.h"

Player::Player(SDL_Renderer* _renderer)
	: texture{ SDL_FRect{200, 500, 40, 40} }, renderer{ _renderer }, angle { 0 }
{
	for (int i = 0; i < numberOfLines; i++)
	{
		points[(-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)] = getStandardPoint((-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i));
		wallTextures[(-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)] = { 0, nullptr };
	}
}

SDL_FPoint Player::getStandardPoint(double angleSight)
{
	return { static_cast<float>(maxSight * cos((angle + angleSight) * std::numbers::pi / 180) + texture.x + texture.w / 2), static_cast<float>(maxSight * sin((angle + angleSight) * std::numbers::pi / 180) + texture.y + texture.h / 2) };
}

double Player::getDistance(const SDL_FPoint& point)
{
	return sqrt((texture.x + texture.w / 2 - point.x) * (texture.x + texture.w / 2 - point.x) + (texture.y + texture.h / 2 - point.y) * (texture.y + texture.h / 2 - point.y));
}

void Player::renderLines() const
{
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	for (const auto& [angleSight, point] : points)
	{
		SDL_RenderLine(renderer, texture.x + texture.w / 2, texture.y + texture.h / 2, point.x, point.y);
	}
}

bool Player::isPointValid(const SDL_FPoint& point, double angleSight) const 
{
	double trueAngle = abs(fmod(angle + angleSight, 360.0));
	if (((trueAngle >= 0 && trueAngle < 90) || (trueAngle > 270)) && point.x < texture.x + texture.w / 2)
	{
		return false;
	}
	if ((trueAngle > 90 && trueAngle < 270) && point.x > texture.x + texture.w / 2)
	{
		return false;
	}
	if (trueAngle == 90 && point.y < texture.y + texture.h / 2)
	{
		return false;
	}
	if (trueAngle == 270 && point.y > texture.y + texture.h / 2)
	{
		return false;
	}
	return true;
}

void Player::walkW(const Walls& walls)
{
	texture.y -= speed;
	if (checkCollision(walls))
	{
		texture.y += speed;
		while (!checkCollision(walls))
		{
			texture.y--;
		}
		texture.y++;
	}
	getPoints(walls);
}

void Player::walkA(const Walls& walls)
{
	texture.x -= speed;
	if (checkCollision(walls))
	{
		texture.x += speed;
		while (!checkCollision(walls))
		{
			texture.x--;
		}
		texture.x++;
	}
	getPoints(walls);
}

void Player::walkS(const Walls& walls)
{
	texture.y += speed;
	if (checkCollision(walls))
	{
		texture.y -= speed;
		while (!checkCollision(walls))
		{
			texture.y++;
		}
		texture.y--;
	}
	getPoints(walls);
}

void Player::walkD(const Walls& walls)
{
	texture.x += speed;
	if (checkCollision(walls))
	{
		texture.x -= speed;
		while (!checkCollision(walls))
		{
			texture.x++;
		}
		texture.x--;
	}
	getPoints(walls);
}

void Player::walkWnew(const Walls& walls)
{
	texture.y += speed * sin(angle * std::numbers::pi / 180);
	texture.x += speed * cos(angle * std::numbers::pi / 180);
	if (checkCollision(walls))
	{
		texture.y -= speed * sin(angle * std::numbers::pi / 180);
		texture.x -= speed * cos(angle * std::numbers::pi / 180);
		while (!checkCollision(walls))
		{
			texture.y += sin(angle * std::numbers::pi / 180);
			texture.x += cos(angle * std::numbers::pi / 180);
		}
		texture.y -= 2 * sin(angle * std::numbers::pi / 180);
		texture.x -= 2 * cos(angle * std::numbers::pi / 180);
	}
	getPoints(walls);
}

void Player::walkSnew(const Walls& walls)
{
	texture.y -= speed * sin(angle * std::numbers::pi / 180);
	texture.x -= speed * cos(angle * std::numbers::pi / 180);
	if (checkCollision(walls))
	{
		texture.y += speed * sin(angle * std::numbers::pi / 180);
		texture.x += speed * cos(angle * std::numbers::pi / 180);
		while (!checkCollision(walls))
		{
			texture.y -= sin(angle * std::numbers::pi / 180);
			texture.x -= cos(angle * std::numbers::pi / 180);
		}
		texture.y += 2 * sin(angle * std::numbers::pi / 180);
		texture.x += 2 * cos(angle * std::numbers::pi / 180);
	}
	getPoints(walls);
}

void Player::walkDnew(const Walls& walls)
{
	texture.y += speed * sin((90 + angle) * std::numbers::pi / 180);
	texture.x += speed * cos((90 + angle) * std::numbers::pi / 180);
	if (checkCollision(walls))
	{
		texture.y -= speed * sin((90 + angle) * std::numbers::pi / 180);
		texture.x -= speed * cos((90 + angle) * std::numbers::pi / 180);
		while (!checkCollision(walls))
		{
			texture.y += sin((90 + angle) * std::numbers::pi / 180);
			texture.x += cos((90 + angle) * std::numbers::pi / 180);
		}
		texture.y -= 2 * sin((90 + angle) * std::numbers::pi / 180);
		texture.x -= 2 * cos((90 + angle) * std::numbers::pi / 180);
	}
	getPoints(walls);
}

void Player::walkAnew(const Walls& walls)
{
	texture.y -= speed * sin((90 + angle) * std::numbers::pi / 180);
	texture.x -= speed * cos((90 + angle) * std::numbers::pi / 180);
	if (checkCollision(walls))
	{
		texture.y += speed * sin((90 + angle) * std::numbers::pi / 180);
		texture.x += speed * cos((90 + angle) * std::numbers::pi / 180);
		while (!checkCollision(walls))
		{
			texture.y -= sin((90 + angle) * std::numbers::pi / 180);
			texture.x -= cos((90 + angle) * std::numbers::pi / 180);
		}
		texture.y += 2 * sin((90 + angle) * std::numbers::pi / 180);
		texture.x += 2 * cos((90 + angle) * std::numbers::pi / 180);
	}
	getPoints(walls);
}

void Player::turnRight(const Walls& walls)
{
	angle = abs(fmod(angle + 1, 360));
	getPoints(walls);
}

void Player::turnLeft(const Walls& walls)
{
	if (angle - 1 < 0)
	{
		angle = 360 + angle;
	}
	angle = abs(fmod(angle - 1, 360));
	getPoints(walls);
}

void Player::getPoints(const Walls& walls)
{
	for (auto& [angleSight, point] : points)
	{
		point = getStandardPoint(angleSight);
		wallTextures[angleSight] = { 0, nullptr };
	}
	for (const auto& wall : walls.walls)
	{
		for (auto& [angleSight, point] : points)
		{
			double phi = angle + angleSight + 90;
			double p = (texture.x + texture.w / 2) * cos(phi * (std::numbers::pi / 180)) + (texture.y + texture.h / 2) * sin(phi * (std::numbers::pi / 180));
			if (p < 0)
			{
				p = -p;
				phi -= 180;
			}

			double delta1 = wall.p1.x * cos(phi * (std::numbers::pi / 180)) + wall.p1.y * sin(phi * (std::numbers::pi / 180)) - p;
			double delta2 = wall.p2.x * cos(phi * (std::numbers::pi / 180)) + wall.p2.y * sin(phi * (std::numbers::pi / 180)) - p;

			if ((delta1 > 0 && delta2 < 0) || (delta1 < 0 && delta2 > 0) || delta1 == 0 || delta2 == 0)
			{
				double a1 = cos(phi * (std::numbers::pi / 180));
				double b1 = sin(phi * (std::numbers::pi / 180));
				double c1 = -p;

				double a2 = wall.p2.y - wall.p1.y;
				double b2 = wall.p1.x - wall.p2.x;
				double c2 = -wall.p1.x * wall.p2.y + wall.p1.y * wall.p2.x;

				double det = a1 * b2 - a2 * b1;
				double detX = -c1 * b2 + c2 * b1;
				double detY = -a1 * c2 + a2 * c1;

				float x{};
				float y{};

				if (!(det == 0 && detX == 0 && detY == 0))
				{
					x = detX / det;
					y = detY / det;
				}
				else
				{
					double distanceP1 = getDistance(wall.p1);
					double distanceP2 = getDistance(wall.p2);

					if (distanceP1 < distanceP2)
					{
						x = wall.p1.x;
						y = wall.p1.y;
					}
					else
					{
						x = wall.p2.x;
						y = wall.p2.y;
					}
				}

				SDL_FPoint newPoint{ x, y };

				double oldDistance = getDistance(point);
				double newDistance = getDistance(newPoint);

				if (newDistance < oldDistance && isPointValid(newPoint, angleSight))
				{
					point = newPoint;
					if (wall.wallpaper != nullptr)
					{
						wallTextures[angleSight] = { getPercentage(wall, newPoint), wall.wallpaper };
					}
				}
			}
		}
	}
}

bool Player::checkCollision(const Walls& walls)
{
	for (const auto& wall : walls.walls)
	{
		double a1 = wall.p2.y - wall.p1.y;
		double b1 = wall.p1.x - wall.p2.x;
		double c1 = -wall.p1.x * wall.p2.y + wall.p1.y * wall.p2.x;

		double a2 = wall.p2.x - wall.p1.x;
		double b2 = wall.p2.y - wall.p1.y;
		double c2 = -a2 * (texture.x + texture.w / 2) - b2 * (texture.y + texture.h / 2);

		double det = a1 * b2 - a2 * b1;
		double detX = -c1 * b2 + c2 * b1;
		double detY = -a1 * c2 + a2 * c1;

		if (det == 0)
		{
			double distanceP1 = getDistance(wall.p1);
			double distanceP2 = getDistance(wall.p2);

			if (distanceP1 <= texture.w / 2 || distanceP2 <= texture.w / 2)
				return true;
		}

		float x = detX / det;
		float y = detY / det;

		if (wall.p2.x - x != 0)
		{
			double lambdaX = (x - wall.p1.x) / (wall.p2.x - x);
			if (lambdaX >= 0)
			{
				SDL_FPoint temp{ x, y };
				double distance = getDistance(temp);
				if (distance <= texture.w / 2)
					return true;
			}
			else
			{
				double distanceP1 = getDistance(wall.p1);
				double distanceP2 = getDistance(wall.p2);

				if (distanceP1 <= texture.w / 2 || distanceP2 <= texture.w / 2)
					return true;
			}
		}
		else
		{
			double lambdaY = (y - wall.p1.y) / (wall.p2.y - y);
			if (lambdaY >= 0)
			{
				SDL_FPoint temp{ x, y };
				double distance = getDistance(temp);
				if (distance <= texture.w / 2)
					return true;
			}
			else
			{
				double distanceP1 = getDistance(wall.p1);
				double distanceP2 = getDistance(wall.p2);

				if (distanceP1 <= texture.w / 2 || distanceP2 <= texture.w / 2)
					return true;
			}
		}
	}
	return false;
}

double Player::getPercentage(const Wall& wall, const SDL_FPoint& point)
{
	double percentage = abs(wall.p1.x - point.x) / abs(wall.p1.x - wall.p2.x);
	if (wall.p1.x - wall.p2.x == 0)
		percentage = abs(wall.p1.y - point.y) / abs(wall.p1.y - wall.p2.y);
	return percentage;
}

int Player::getColor(double distance)
{
	return static_cast<int>(255 * pow(((maxSight - 20 - distance) / (maxSight - 20)), 4)) + 1;
}

float Player::getPosition(double distance, SDL_FRect screen)
{
	double alpha{ asin(2 / distance) * 180 / std::numbers::pi };
	float pos = screen.y + screen.h / 2 + alpha / 2 * screen.h;
	
	return pos;
}

void Player::render() const
{
	renderLines();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderFillRect(renderer, &texture);
}

void Player::to3D(SDL_FRect screen)
{
	auto it{ points.begin() };
	for (int i = 0; i < numberOfLines; i++)
	{
		double distance{ getDistance(it->second) };
		if (distance < maxSight - 20)
		{
			int color{ getColor(distance) };
			float pos{ getPosition(distance, screen) };
			float height{ 2 * (pos - screen.h / 2) };

			if (wallTextures[it->first].second == nullptr)
			{
				SDL_SetRenderDrawColor(renderer, 0, color, color, 255);

				SDL_FRect temp{ screen.x + screen.w / numberOfLines * i, pos - height, screen.w / numberOfLines, height };
				SDL_RenderFillRect(renderer, &temp);
			}
			else
			{
				SDL_FRect rect{0, 0, 0, 0};
				SDL_GetTextureSize(wallTextures[it->first].second, &rect.w, &rect.h);

				SDL_FRect src{ rect.w * wallTextures[it->first].first, 0, screen.w / numberOfLines, rect.h };
				SDL_FRect temp{ screen.x + screen.w / numberOfLines * i, pos - height, screen.w / numberOfLines, height };

				SDL_SetTextureColorMod(wallTextures[it->first].second, color, color, color);
				SDL_RenderTexture(renderer, wallTextures[it->first].second, &src, &temp);
				SDL_SetTextureColorMod(wallTextures[it->first].second, 255, 255, 255);
			}
		}
		std::advance(it, 1);
	}
}
