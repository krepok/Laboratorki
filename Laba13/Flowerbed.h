#pragma once
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

struct Flowerbed
{
	int idFlowerbed{};
	std::string shape{};
	std::list<std::string> flowers{};

	Flowerbed(int = -1, std::string = "None", std::list<std::string> = { "None" });
	Flowerbed(const Flowerbed&);
	Flowerbed(Flowerbed&&) noexcept;

	bool hasFlower(std::string_view) const;
	friend std::ostream& operator<<(std::ostream&, const Flowerbed&);
	Flowerbed& operator=(const Flowerbed&);
};

class Ridge
{
private:
	std::vector<Flowerbed> flowerbeds;

public:
	Ridge() = default;
	Ridge(const std::vector<Flowerbed>&);
	Ridge(const Ridge&);
	Ridge(Ridge&&) noexcept;

	std::vector<Flowerbed> getFlowerbeds() const;

	void add(const Flowerbed&);
	bool empty() const;

	std::set<std::string> getSetCommonFlowers() const;
	std::set<std::string> getSetAllFlowers() const;
	Ridge getRidgeWithoutFlower(std::string_view) const;
	Ridge getRidgeWithNumber(int) const;
	void replaceFlower(std::string_view, std::string);
	friend void sort(Ridge&);
};

bool compareFlowerbed(const Flowerbed& fl1, const Flowerbed& fl2);
