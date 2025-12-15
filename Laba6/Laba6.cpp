#include "Laba6.h"
#include "Get Functions.h"
#include "Get Array Functions.h"

int main()
{
	try
	{
		Way way{ getWay() };
		DataType type{ getDataType() };
		if (way == Way::RandomToFile && type == DataType::String)
		{
			throw std::exception("You can't generate random array of strings!");
		}

		switch (type)
		{
		case DataType::Int:
		{
			std::vector<int> infoInt;
			getAndOutputArray(infoInt, way);
			break;
		}
		case DataType::Double:
		{
			std::vector<double> infoDouble;
			getAndOutputArray(infoDouble, way);
			break;
		}
		case DataType::String:
		{
			std::vector<std::string> infoString;
			getAndOutputArray(infoString, way);
			break;
		}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}