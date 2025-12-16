#pragma once
#include <vector>

template<typename T>
int partition(std::vector<T>& arr, int low, int high)
{
	size_t size{ arr.size() };
	int i{ low - 1 };
	for (int j = low; j < high; j++) // берем за основу последний элемент массива и ставим его так
	{								 // чтобы все элементы меньше него стояли слева, а больше него - справа
		if (arr[j] < arr[high])
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[high], arr[i + 1]); // ставим основу на правильное место
	return i + 1;
}

template<typename T>
void quickSort(std::vector<T>& arr, int low, int high)
{
	if (high > low)
	{
		int pivot{ partition(arr, low, high) }; // функция которая находит позицию основы
		quickSort(arr, low, pivot - 1);			// разбиваем массив на 2 под массива и сортируем их
		quickSort(arr, pivot + 1, high);
	}
}