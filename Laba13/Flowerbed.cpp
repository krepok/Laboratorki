#include "Flowerbed.h"

bool compareFlowerbed(const Flowerbed& fl1, const Flowerbed& fl2)
{
	if (fl1.shape != fl2.shape)
	{
		return fl1.shape > fl2.shape;
	}
	if (fl1.idFlowerbed != fl2.idFlowerbed)
	{
		return fl1.idFlowerbed < fl2.idFlowerbed;
	}
	return false;
}

Flowerbed::Flowerbed(int _id, std::string _shape, std::list<std::string> _flowers)
	: idFlowerbed{ _id }, shape{ _shape }, flowers{ _flowers }
{
}

Flowerbed::Flowerbed(const Flowerbed& other)
	: idFlowerbed{ other.idFlowerbed }, shape{ other.shape }, flowers{ other.flowers }
{
}

Flowerbed::Flowerbed(Flowerbed&& other) noexcept
	: idFlowerbed{ other.idFlowerbed }, shape{ other.shape }, flowers{ std::move(other.flowers) }
{
	other.flowers.clear();
	other.idFlowerbed = 0;
	other.shape.clear();
}

bool Flowerbed::hasFlower(std::string_view flower) const
{
	return std::find(flowers.begin(), flowers.end(), flower) != flowers.end();
}

Flowerbed Flowerbed::operator=(const Flowerbed& other)
{
	this->flowers = other.flowers;
	this->idFlowerbed = other.idFlowerbed;
	this->shape = other.shape;
	return *this;
}

std::ostream& operator<<(std::ostream& in, const Flowerbed& other)
{
	in << "shape: " << other.shape << ", id: " << other.idFlowerbed << '\n';
	in << "flowers: ";
	for (auto p : other.flowers)
	{
		in << p << ", ";
	}
	in << "\b \b" << "\b \b";
	in << '\n';
	return in;
}

Ridge::Ridge(const std::vector<Flowerbed>& _flowerbeds)
	: flowerbeds{ _flowerbeds }
{
}

Ridge::Ridge(const Ridge& other)
	: flowerbeds{ other.flowerbeds }
{
}

Ridge::Ridge(Ridge&& other) noexcept
	: flowerbeds{ std::move(other.flowerbeds) }
{
	other.flowerbeds.clear();
}

std::vector<Flowerbed> Ridge::getFlowerbeds() const
{
	return flowerbeds;
}

void Ridge::add(const Flowerbed& flowerbed)
{
	flowerbeds.push_back(flowerbed);
}

bool Ridge::empty() const
{
	return flowerbeds.empty();
}

Ridge Ridge::getRidgeWithoutFlower(std::string_view target) const
{
	Ridge result;
	for (auto& flowerbed : flowerbeds)
	{
		if (!flowerbed.hasFlower(target))
		{
			result.flowerbeds.push_back(flowerbed);
		}
	}
	return result;
}

void Ridge::replaceFlower(std::string_view find, std::string replace)
{
	for (auto& flowerbed : flowerbeds)
	{
		for (auto& flower : flowerbed.flowers)
		{
			if (flower == find)
			{
				flower = replace;
			}
		}
	}
}

Ridge Ridge::getRidgeWithNumber(int size) const
{
	Ridge beds{};
	for (auto& flowerbed : flowerbeds)
	{
		std::set<std::string> flowers{};
		for (auto flower : flowerbed.flowers)
		{
			flowers.insert(flower);
		}
		if (flowers.size() == size)
		{
			beds.flowerbeds.push_back(flowerbed);
		}
	}
	return beds;
}

std::set<std::string> Ridge::getSetCommonFlowers() const
{
	std::set<std::string> allFlowers{ getSetAllFlowers() };
	std::set<std::string> toDelete{};
	for (auto& flower : allFlowers)
	{
		for (auto& flowerbed : flowerbeds)
		{
			if (!flowerbed.hasFlower(flower))
			{
				toDelete.insert(flower);
				break;
			}
		}
	}
	for (auto& flower : toDelete)
	{
		allFlowers.erase(flower);
	}
	return allFlowers;
}

std::set<std::string> Ridge::getSetAllFlowers() const
{
	std::set<std::string> allFlowers{};
	for (auto& flowerbed : flowerbeds)
	{
		for (auto flower : flowerbed.flowers)
		{
			allFlowers.insert(flower);
		}
	}
	return allFlowers;
}

void sort(Ridge& ridge)
{
	std::sort(ridge.flowerbeds.begin(), ridge.flowerbeds.end(), compareFlowerbed);
}