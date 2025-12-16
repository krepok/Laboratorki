#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>

struct SMark
{
	std::string subject{};
	int mark{};
};

struct SStudData
{
	std::string name{};
	int id{};
	std::vector<SMark> marks{};

	friend std::ostream& operator<<(std::ostream& in, const SStudData& other)
	{
		in << "Name: " << other.name << ", id: " << other.id << '\n';
		for (auto p : other.marks)
		{
			in << p.subject << ' ' << p.mark << ", ";
		}
		in << "\b \b" << "\b \b";
		in << '\n';
		return in;
	}

	bool operator>(const SStudData& other) const
	{
		return this->name > other.name;
	}

	bool operator<(const SStudData& other) const
	{
		return this->name < other.name;
	}

	bool operator==(const SStudData& other) const
	{
		return this->name == other.name;
	}

	bool operator>=(const SStudData& other) const
	{
		return *this > other || *this == other;
	}

	bool operator<=(const SStudData& other) const
	{
		return *this < other || *this == other;
	}
};

using MapStudents = std::map<int, SStudData>;
using MultimapStudents = std::multimap<SStudData, double>;
using MultimapAverage = std::multimap<double, SStudData, std::greater<double>>;

MapStudents getInfo(std::ifstream& fin);
void printStudents(const MapStudents& students);
void printStudentsAverages(const MapStudents& students);
void printStudentsAverages(const MultimapStudents& studentsAv);
void printInRange(const MapStudents& students);
MapStudents getStudentsSubject(const MapStudents& students, std::string_view subject);
void printStudentsSubject(const MapStudents& students);
void printAverageSubject(const MapStudents& students);
MultimapStudents getStudentsMaxAv(MapStudents students);
MapStudents getStudentsFailed(MapStudents students);
std::string getSubject();

int main()
{
	try
	{
		std::ifstream fin("data.txt");
		MapStudents students{ getInfo(fin) };

		printStudentsAverages(students);
		std::cout << '\n';

		printInRange(students);
		std::cout << '\n';

		try
		{
			std::string subject{ getSubject() };
			MapStudents temp{ getStudentsSubject(students, subject) };
			if (temp.empty())
			{
				throw std::invalid_argument("There is no such subject!");
			}
			printStudents(temp);
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << '\n';
		}

		printStudentsSubject(students);
		std::cout << '\n';

		printAverageSubject(students);
		std::cout << '\n';

		MultimapStudents temp1{ getStudentsMaxAv(students) };
		std::cout << "Students with max average:\n";
		printStudentsAverages(temp1);
		std::cout << '\n';

		MapStudents temp2{ getStudentsFailed(students) };
		std::cout << "Students who failed:\n";
		printStudentsAverages(temp2);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}

void checkFile(std::ifstream& fin)
{
	if (!fin.is_open())
	{
		throw std::invalid_argument("Couldn't open a file!");
	}
	if (fin.peek() == EOF)
	{
		throw std::invalid_argument("File is empty!");
	}
}

std::vector<SMark> getVectorMark(std::string& info) // возвращает вектор с оценками
{
	std::vector<SMark> infoStr{};

	for (size_t place = info.find(','); place != std::string::npos; place = info.find(','))
	{
		std::string temp{ info.substr(0, place) };
		auto pos{ temp.find(' ') };

		infoStr.push_back({ temp.substr(0, pos), stoi(temp.substr(pos + 1)) });
		info.erase(0, place + 1);
		place = info.find(',');
	}
	auto pos{ info.find(' ') };
	infoStr.push_back({ info.substr(0, pos), stoi(info.substr(pos + 1)) });

	return infoStr;
}

std::vector<std::string> getVectorInfo(std::string& info) // возвращает вектор строк с разделенной информацией
{
	std::vector<std::string> infoStr{};

	for (size_t place = info.find(';'); place != std::string::npos; place = info.find(';'))
	{
		infoStr.push_back(info.substr(0, place));
		info.erase(0, place + 1);
		place = info.find(';');
	}
	infoStr.push_back(info);

	return infoStr;
}

MapStudents getInfo(std::ifstream& fin) // получает информацию из файла
{
	checkFile(fin);
	std::string info{};
	MapStudents infoMap{};

	while (std::getline(fin, info))
	{
		std::vector<std::string> infoVector{ getVectorInfo(info) };  // 0 - имя, 1 - зачетка, 2 - оценки

		infoMap[stoi(infoVector.at(1))] = SStudData{ infoVector.at(0), stoi(infoVector.at(1)), getVectorMark(infoVector.at(2)) };
	}

	return infoMap;
}

double getAverage(const SStudData& student)
{
	int average{};
	for (const auto& mark : student.marks)
	{
		average += mark.mark;
	}
	return static_cast<double>(average) / student.marks.size();
}

std::map<int, double> getAllAverages(const MapStudents students)
{
	std::map<int, double> averages{};
	for (const auto& [id, student] : students)
	{
		averages[id] = getAverage(student);
	}
	return averages;
}

void printStudents(const MapStudents& students)
{
	if (students.empty())
	{
		std::cout << "There are no such students!\n";
		return;
	}
	for (const auto& [left, right] : students)
	{
		std::cout << right;
	}
	std::cout << '\n';
}

MultimapStudents getVectorStAv(MapStudents students)
{
	MultimapStudents studentsAverages{};
	for (const auto& [id, student] : students)
	{
		studentsAverages.insert(std::pair<SStudData, double>{ student, getAverage(student) });
	}
	return studentsAverages;
}

void printStudentsAverages(const MapStudents& students)
{
	if (students.empty())
	{
		std::cout << "There are no such students!\n";
		return;
	}
	MultimapStudents studentsAv{ getVectorStAv(students) };
	int counter{ 1 };
	for (const auto& [student, average] : studentsAv)
	{
		std::cout << counter++ << ". " << student.name << ", " << student.id << ", average grade: " << average << '\n';
	}
}

void printStudentsAverages(const MultimapStudents& studentsAv)
{
	if (studentsAv.empty())
	{
		std::cout << "There are no such students!\n";
		return;
	}
	int counter{ 1 };
	for (const auto& [student, average] : studentsAv)
	{
		std::cout << counter++ << ". " << student.name << ", " << student.id << ", average grade: " << average << '\n';
	}
}

void printStudentsAverages(const MultimapAverage& studentsAv)
{
	if (studentsAv.empty())
	{
		std::cout << "There are no such students!\n";
		return;
	}
	int counter{ 1 };
	for (const auto& [average, student] : studentsAv)
	{
		std::cout << counter++ << ". " << student.name << ", " << student.id << ", average grade: " << average << '\n';
	}
}

MultimapAverage getStudentsRange(const MapStudents& students, double lower, double higher)
{
	MultimapStudents studentsAv{ getVectorStAv(students) };
	MultimapAverage inRange{};

	for (const auto& [student, average] : studentsAv)
	{
		if (average >= lower && average <= higher)
		{
			inRange.insert(std::pair<double, SStudData>{ average, student });
		}
	}

	return inRange;
}

void printInRange(const MapStudents& students)
{
	double lower{};
	double higher{};
	std::cout << "Enter range of average grade( lowest - highest ): ";
	if (!(std::cin >> lower >> higher) || lower > higher)
	{
		throw std::invalid_argument("You entered something wrong!");
	}
	if (lower < 0 || lower > 10 || higher < 0 || higher > 10)
	{
		throw std::invalid_argument("You can't have this grade!");
	}

	std::cout << "Students with average grade in range " << lower << " - " << higher << ":\n";
	printStudentsAverages(getStudentsRange(students, lower, higher));
}

MapStudents getStudentsSubject(const MapStudents& students, std::string_view subject)
{
	MapStudents studentsSubject{};

	for (const auto& [id, student] : students)
	{
		for (const auto& mark : student.marks)
		{
			if (mark.subject == subject)
			{
				studentsSubject[id] = student;
				break;
			}
		}
	}

	return studentsSubject;
}

std::set<std::string> getAllSubjects(const MapStudents& students)
{
	std::set<std::string> allSubjects{};
	for (const auto& [id, student] : students)
	{
		for (const auto& mark : student.marks)
		{
			allSubjects.insert(mark.subject);
		}
	}
	return allSubjects;
}

int getNumOfStudents(const MapStudents& students, std::string_view subject)
{
	int counter{};
	for (const auto& [id, student] : students)
	{
		for (const auto& mark : student.marks)
		{
			if (mark.subject == subject)
			{
				++counter;
				break;
			}
		}
	}
	return counter;
}

void printStudentsSubject(const MapStudents& students)
{
	std::set<std::string> allSubjects{ getAllSubjects(students) };

	std::cout << "Subjects/number of students who has marks:\n";
	for (auto& subject : allSubjects)
	{
		std::cout << subject << ": " << getNumOfStudents(students, subject) << '\n';
	}
}

double averageSubject(const MapStudents& students, std::string_view subject)
{
	int sum{};
	int counter{};
	for (const auto& [id, student] : students)
	{
		for (const auto& mark : student.marks)
		{
			if (mark.subject == subject)
			{
				sum += mark.mark;
				++counter;
			}
		}
	}
	return static_cast<double>(sum) / counter;
}

void printAverageSubject(const MapStudents& students)
{
	std::set<std::string> allSubjects{ getAllSubjects(students) };

	std::cout << "Subjects/average grade:\n";
	for (const auto& subject : allSubjects)
	{
		std::cout << subject << ": " << averageSubject(students, subject) << '\n';
	}
}

MultimapStudents getStudentsMaxAv(MapStudents students)
{
	MultimapStudents studentsAverages{ getVectorStAv(students) };
	double max{ -1 };
	MultimapStudents studentsMax{};

	for (const auto& [student, av] : studentsAverages)
	{
		if (av == max)
		{
			studentsMax.insert({ student, av });
		}
		if (av > max)
		{
			studentsMax.clear();
			studentsMax.insert({ student, av });
			max = av;
		}
	}

	return studentsMax;
}


MapStudents getStudentsFailed(MapStudents students)
{
	MapStudents studentsFailed{};

	for (const auto& [id, student] : students)
	{
		for (const auto& mark : student.marks)
		{
			if (mark.mark < 4)
			{
				studentsFailed[id] = student;
			}
		}
	}

	return studentsFailed;
}

std::string getSubject()
{
	std::string subject;
	std::cout << "Enter subject you want to find ( enter 'no' if you don't need it ): ";
	std::cin.ignore();
	if (!std::getline(std::cin, subject))
	{
		throw std::invalid_argument("You entered something wrong!\n");
	}
	if (subject.empty())
	{
		throw std::invalid_argument("You didn't enter anything!\n");
	}
	if (subject == "no")
	{
		throw std::invalid_argument("Ok!\n");
	}
	return subject;
}