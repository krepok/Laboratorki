#pragma once
#include <SDL3/SDL.h>
#include <map>
#include <cmath>
#include <numbers>
#include "Wall.h"
#include <iostream>

static constexpr int numberOfLines = 320;
static constexpr double angleOfSight = 20;
static constexpr double maxSight = 1500;
static constexpr int speed = 5;

class Player
{
private:
	SDL_Renderer* renderer;
	SDL_FRect texture;
	double angle;
	std::map<double, SDL_FPoint> points;
	std::map<double, std::pair<double, SDL_Texture*>> wallTextures;

	SDL_FPoint getStandardPoint(double);
	double getDistance(const SDL_FPoint&);
	void renderLines() const;
	bool isPointValid(const SDL_FPoint&, double) const;

	void getPoints(const Walls&);
	bool checkCollision(const Walls&);
	double getPercentage(const Wall&, const SDL_FPoint&);

	int getColor(double);
	float getPosition(double, SDL_FRect);
	float getHeight(double, SDL_FRect);

public:
	Player(SDL_Renderer* _renderer);
	~Player() = default;

	void walkW(const Walls&);
	void walkA(const Walls&);
	void walkS(const Walls&);
	void walkD(const Walls&);

	void walkWnew(const Walls&);
	void walkAnew(const Walls&);
	void walkSnew(const Walls&);
	void walkDnew(const Walls&);

	void turnRight(const Walls&);
	void turnLeft(const Walls&);

	void render() const;

	void to3D(SDL_FRect);
};

