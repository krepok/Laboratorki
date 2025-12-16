#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

struct Student
{
	std::string name{};
	int course{};
	int group{};
};

void checkFile(std::ifstream& fin)
{
	if (!fin.is_open())
	{
		throw std::exception("Couldn't open a file!");
	}
	if (fin.peek() == EOF)
	{
		throw std::exception("File is empty!");
	}
}

std::vector<std::string> getVectorInfo(std::string info)
{
	std::vector<std::string> infoStr{};

	for (auto place = info.find(';'); place != std::string::npos; place = info.find(';'))
	{
		infoStr.push_back(info.substr(0, place));
		info.erase(0, place + 1);
	}
	infoStr.push_back(info);

	return infoStr;
}

std::vector<Student> getStudents(std::ifstream& fin)
{
	checkFile(fin);
	std::string info{};
	std::vector<Student> students;

	while (std::getline(fin, info))
	{
		std::vector<std::string> vector{ getVectorInfo(info) };
		students.push_back({ vector.at(0), stoi(vector.at(1)), stoi(vector.at(2)) });
	}

	return students;
}

bool compareNames(const Student& st1, const Student& st2)
{
	if (st1.name != st2.name)
	{
		return st1.name < st2.name;
	}
	return false;
}

bool compareCourseGroupsNames(const Student& st1, const Student& st2)
{
	if (st1.course != st2.course)
	{
		return st1.course < st2.course;
	}
	if (st1.group != st2.group)
	{
		return st1.group < st2.group;
	}
	return compareNames(st1, st2);
}

void getFioTxt(std::vector<Student> students, std::ofstream& fout)
{
	std::sort(students.begin(), students.end(), compareNames);

	fout << "Students sorted by name:\n";
	for (const auto& student : students)
	{
		fout << student.name << ", course: " << student.course << ", group: " << student.group << '\n';
	}
}

void getGroupsTxt(std::vector<Student> students, std::ofstream& fout)
{
	std::sort(students.begin(), students.end(), compareCourseGroupsNames);

	fout << "Students sorted by course -> group -> name:\n";
	for (const auto& student : students)
	{
		fout << "course: " << student.course << ", group: " << student.group << "  " << student.name << '\n';
	}
}

int main()
{
	try
	{
		std::ifstream fin("Students.txt");
		std::vector<Student> students{ getStudents(fin) };
		fin.close();

		std::ofstream foutFio("Fio.txt");
		getFioTxt(students, foutFio);
		foutFio.close();

		std::ofstream foutGroups("Groups.txt");
		getGroupsTxt(students, foutGroups);
		foutGroups.close();

		std::cout << "Done!\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}