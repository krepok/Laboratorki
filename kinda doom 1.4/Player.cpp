#include "Player.h"

Player::Player(SDL_Renderer* _renderer)
	: texture{ SDL_FRect{200, 500, 40, 40} }, renderer{ _renderer }, angle{ 0 }
{
	for (int i = 0; i < numberOfLines; i++)
	{
		wallTextures[(-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)] = { { getStandardPoint((-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)), { 0, nullptr } } };
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
	for (const auto& [angleSight, vectorPoint] : wallTextures)
	{
		SDL_RenderLine(renderer, texture.x + texture.w / 2, texture.y + texture.h / 2, vectorPoint.rbegin()->first.x, vectorPoint.rbegin()->first.y);
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

void Player::walkWnew(const Walls& wallsTexture, const Walls& wallsColision)
{
	texture.y += speed * sin(angle * std::numbers::pi / 180);
	texture.x += speed * cos(angle * std::numbers::pi / 180);
	if (checkCollision(wallsColision))
	{
		texture.y -= speed * sin(angle * std::numbers::pi / 180);
		texture.x -= speed * cos(angle * std::numbers::pi / 180);
		while (!checkCollision(wallsColision))
		{
			texture.y += sin(angle * std::numbers::pi / 180);
			texture.x += cos(angle * std::numbers::pi / 180);
		}
		texture.y -= 2 * sin(angle * std::numbers::pi / 180);
		texture.x -= 2 * cos(angle * std::numbers::pi / 180);
	}
	getPoints(wallsTexture);
}

void Player::walkSnew(const Walls& walls, const Walls& wallsColision)
{
	texture.y -= speed * sin(angle * std::numbers::pi / 180);
	texture.x -= speed * cos(angle * std::numbers::pi / 180);
	if (checkCollision(wallsColision))
	{
		texture.y += speed * sin(angle * std::numbers::pi / 180);
		texture.x += speed * cos(angle * std::numbers::pi / 180);
		while (!checkCollision(wallsColision))
		{
			texture.y -= sin(angle * std::numbers::pi / 180);
			texture.x -= cos(angle * std::numbers::pi / 180);
		}
		texture.y += 2 * sin(angle * std::numbers::pi / 180);
		texture.x += 2 * cos(angle * std::numbers::pi / 180);
	}
	getPoints(walls);
}

void Player::walkDnew(const Walls& walls, const Walls& wallsColision)
{
	texture.y += speed * sin((90 + angle) * std::numbers::pi / 180);
	texture.x += speed * cos((90 + angle) * std::numbers::pi / 180);
	if (checkCollision(wallsColision))
	{
		texture.y -= speed * sin((90 + angle) * std::numbers::pi / 180);
		texture.x -= speed * cos((90 + angle) * std::numbers::pi / 180);
		while (!checkCollision(wallsColision))
		{
			texture.y += sin((90 + angle) * std::numbers::pi / 180);
			texture.x += cos((90 + angle) * std::numbers::pi / 180);
		}
		texture.y -= 2 * sin((90 + angle) * std::numbers::pi / 180);
		texture.x -= 2 * cos((90 + angle) * std::numbers::pi / 180);
	}
	getPoints(walls);
}

void Player::walkAnew(const Walls& walls, const Walls& wallsColision)
{
	texture.y -= speed * sin((90 + angle) * std::numbers::pi / 180);
	texture.x -= speed * cos((90 + angle) * std::numbers::pi / 180);
	if (checkCollision(wallsColision))
	{
		texture.y += speed * sin((90 + angle) * std::numbers::pi / 180);
		texture.x += speed * cos((90 + angle) * std::numbers::pi / 180);
		while (!checkCollision(wallsColision))
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
	for (int i = 0; i < numberOfLines; i++)
	{
		wallTextures[(-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)] = { { getStandardPoint((-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)), { 0, nullptr } } };
	}
	for (int i = 0; i < numberOfLines; i++)
	{
		double angleSight{ (-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i) };
		for (auto& wall : walls.walls)
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

				if (isPointValid(newPoint, angleSight))
				{
					wallTextures[angleSight].push_back({ newPoint, { getPercentage(wall, newPoint), &wall } });
				}
			}
		}

		size_t size{ wallTextures[angleSight].size() };
		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size - 1 - i; j++)
			{
				if (getDistance(wallTextures[angleSight][j].first) < getDistance(wallTextures[angleSight][j + 1].first))
				{
					std::swap(wallTextures[angleSight][j], wallTextures[angleSight][j + 1]);
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
	int temp = static_cast<int>(255 * pow(((maxSight - 20 - distance) / (maxSight - 20)), 4)) + 1;;


	return temp;
}

float Player::getPosition(double distance, SDL_FRect screen)
{
	float yNdcBase = (-50) / (distance * tan(40 * std::numbers::pi / 360));
	return screen.h * (0.5 - yNdcBase / 2);
}

float Player::getHeight(double distance, SDL_FRect screen)
{
	return (100 / (2 * distance * tan(40 * std::numbers::pi / 360))) * screen.h;
}

void Player::render() const
{
	renderLines();

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderFillRect(renderer, &texture);
}


//void Player::renderGround(SDL_FRect screen)
//{
//	int width = screen.h / 2;
//	for (int i = 0; i < width; i += 3)
//	{
//		SDL_FRect temp(screen.x, screen.h - i, screen.w, 3);
//		double color = pow(((maxSight - 20 - i) / (maxSight - 20)), 10);
//
//		SDL_SetRenderDrawColor(renderer, 183 * color, 233 * color, 143 * color, 255);
//		SDL_RenderFillRect(renderer, &temp);
//	}
//}

void Player::to3D(SDL_FRect screen)
{
	for (int i = 0; i < numberOfLines; i++)
	{
		for (const auto& [point, wall] : wallTextures[(-angleOfSight + 2 * angleOfSight / (numberOfLines - 1) * i)])
		{
			double distance{ getDistance(point) };
			if (distance < maxSight - 20)
			{
				int color{ getColor(distance) };
				float pos1{ getPosition(distance, screen) };
				float height{ getHeight(distance, screen) };

				if (wall.second != nullptr && wall.second->wallpaper == nullptr)
				{
					SDL_SetRenderDrawColor(renderer, 0, color, color, 255);

					SDL_FRect temp{ screen.x + screen.w / numberOfLines * i, pos1 - height, screen.w / numberOfLines, height };
					SDL_RenderFillRect(renderer, &temp);
				}
				else if (wall.second != nullptr && wall.second->isGIF)
				{
					SDL_FRect rect{ 0, 0, 0, 0 };
					SDL_GetTextureSize(wall.second->wallpaper, &rect.w, &rect.h);

					SDL_FRect src{(wall.second->counter % static_cast<int>(rect.w / wall.second->src.w)) * wall.second->src.w + wall.second->src.w * wall.first, wall.second->src.h * (wall.second->counter / (static_cast<int>(rect.w / wall.second->src.w))), screen.w / numberOfLines, wall.second->src.h };
					SDL_FRect temp{ screen.x + screen.w / numberOfLines * i, pos1 - height, screen.w / numberOfLines, height };

					SDL_SetTextureColorMod(wall.second->wallpaper, color, color, color);
					SDL_RenderTexture(renderer, wall.second->wallpaper, &src, &temp);
					SDL_SetTextureColorMod(wall.second->wallpaper, 255, 255, 255);
				}
				else if (wall.second != nullptr && wall.second->wallpaper != nullptr)
				{
					SDL_FRect rect{ 0, 0, 0, 0 };
					SDL_GetTextureSize(wall.second->wallpaper, &rect.w, &rect.h);

					SDL_FRect src{ rect.w * wall.first, 0, screen.w / numberOfLines, rect.h };
					SDL_FRect temp{ screen.x + screen.w / numberOfLines * i, pos1 - height, screen.w / numberOfLines, height };

					SDL_SetTextureColorMod(wall.second->wallpaper, color, color, color);
					SDL_RenderTexture(renderer, wall.second->wallpaper, &src, &temp);
					SDL_SetTextureColorMod(wall.second->wallpaper, 255, 255, 255);
				}
			}
		}
	}
}