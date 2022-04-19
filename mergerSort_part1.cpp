#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Library_card.h"

using namespace std;

//Перегрузка записи в файлы
ifstream& operator>>(ifstream& is, Library_card& en);
ofstream& operator<<(ofstream& os, const Library_card& en);

//Работа с файлами
void initFiles(int size);
void clearFiles();
void printFiles();

//Методы алгоритма сортировки
void mergerSort(int n, int size);
void mergeInA(int n, int size, int len_B, int len_C);

//Компаратор
bool comp(Library_card first, Library_card second);

int main()
{
	setlocale(LC_ALL, "ru");

	clearFiles();

	int len = 15;
	initFiles(len);

	printFiles();

	for (int i = 0; pow(2, i) < len; i++)
	{
		//cout << "\n\n" << pow(2, i) << "\n\n";
		mergerSort((int)pow(2, i), len);
		//printFiles();
	}
	//mergerSort(1, len);
	//cout << "\n\n1111111111111111\n";
	//printFiles();
	//mergerSort(2, len);
	//cout << "\n\n2222222222222222\n";
	//printFiles();
	//cout << "\n\n";
	//mergerSort(4, len);
	//cout << "\n\n3333333333333333\n";
	printFiles();

	return 0;
}

//Работа с файлами
void initFiles(int size)
{
	ofstream outA;
	outA.open("A.txt");

	string arr_autors[] = { "В.А.Голубев", "Г.В.Александров", "В.С.Киров", "К.С.Андропов", "У.Е.Куницын" };
	string arr_books[] = { "Высшая_математика", "Физика", "Правоведение", "Программирование", "Аналитическая_геометрия_и_алгебра" };
	string arr_date_start[] = { "14.09.2021", "04.10.2021", "03.11.2021", "14.09.2021", "01.10.2021" };
	string arr_date_end[] = { "15.05.2022", "04.04.2022", "03.06.2022", "14.05.2022", "01.05.2022" };

	if (outA)
	{
		//Инициализация файла A
		for (int i = 0; i < size; i++)
		{
			/*outA << rand() % size + 1 << '\t'
							<< rand() % 10 + 1 << '\t'
							<< arr_autors[rand() % 5 + 0] << '\t'
							<< arr_books[rand() % 5 + 0] << '\t'
							<< arr_date_start[rand() % 5 + 0] << '\t'
							<< arr_date_end[rand() % 5 + 0] << '\n';*/

			Library_card lb(
				//rand() % size + 1,
				size - i,
				i + 1,
				arr_autors[rand() % 5 + 0],
				arr_books[rand() % 5 + 0],
				arr_date_start[rand() % 5 + 0],
				arr_date_end[rand() % 5 + 0]
			);

			outA << lb;
		}

		outA.close();
	}
}
void clearFiles()
{
	ofstream outA, outB, outC;
	outA.open("A.txt");
	if (outA)
	{
		outB.open("B.txt");
		if (outB)
		{
			outC.open("C.txt");
			if (outC)
			{
				outC.close();
			}
			outB.close();
		}
		outA.close();
	}
}
void printFiles()
{
	Library_card p_l;
	//Содержимое файла A
	cout << "\n\nСодержимое файла A\n";
	ifstream inA;
	inA.open("A.txt");

	if (inA)
	{
		Library_card t;
		while (!inA.eof())
		{
			inA >> t;
			t.print_inf();
		}
		inA.close();
	}

	//Содержимое файла B
	cout << "\n\nСодержимое файла B\n";
	ifstream inB;
	inB.open("B.txt");

	if (inB)
	{
		Library_card t;
		while (!inB.eof())
		{
			inB >> t;
			t.print_inf();
		}
		inB.close();
	}

	//Содержимое файла C
	cout << "\n\nСодержимое файла C\n";
	ifstream inC;
	inC.open("C.txt");

	if (inC)
	{
		Library_card t;
		while (!inC.eof())
		{
			inC >> t;
			cout << t.toString() << '\n';
		}
		inC.close();
	}
}

//Сортировка
void mergerSort(int n, int size)
{
	ifstream inA;
	ofstream outB, outC;

	int len_B = 0;
	int len_C = 0;

	inA.open("A.txt");

	if (inA)
	{
		outB.open("B.txt");
		if (outB)
		{
			outC.open("C.txt");
			if (outC)
			{
				Library_card lb;

				bool b = true;
				int count = 0;

				while (!inA.eof())
				{
					//Переключение записи между A и B
					if (b)
					{
						if (count == n)
						{
							b = false;
							count = 0;
						}
						else
						{
							inA >> lb;
							outB << lb;
							count++;
						}
					}
					else
					{
						if (count == n)
						{
							b = true;
							count = 0;
						}
						else
						{
							inA >> lb;
							outC << lb;
							count++;
						}
					}
				}
				outC.close();
			}
			outB.close();
		}
		inA.close();
	}
	mergeInA(n, size, len_B, len_C);
}

void mergeInA(int n, int size, int len_B, int len_C)
{
	ofstream outA;
	ifstream inB, inC;


	outA.open("A.txt");

	if (outA)
	{
		inB.open("B.txt");
		if (inB)
		{
			inC.open("C.txt");
			if (inC)
			{
				Library_card t1;
				Library_card t2;

				vector<Library_card> vec1;
				vector<Library_card> vec2;
				vector<Library_card> vec;

				bool b = true;
				int count = 0;

				while (!inB.eof() || !inC.eof())
				{
					for (int i = 0; i < n; i++)
					{
						if (!inB.eof())
						{
							inB >> t1;
							vec1.push_back(t1);
						}
					}

					for (int i = 0; i < n; i++)
					{
						if (!inC.eof())
						{
							inC >> t2;
							vec2.push_back(t2);
						}
					}
					if (vec1.size() > 0 && vec2.size() > 0)
					{
						if (vec1.back().get_num_ticket() < vec2.back().get_num_ticket())
						{
							vec.insert(vec.end(), vec1.begin(), vec1.end());
							vec.insert(vec.end(), vec2.begin(), vec2.end());
						}
						/*else if (vec1.back().get_num_ticket() == vec2.back().get_num_ticket())
						{
							int ind1 = vec1.size() - 2;
							int ind2 = vec2.size() - 2;
							if (ind1 <= 0)
								ind1 = vec1.size() - 1;
							if (ind2 <= 0)
								ind2 = vec2.size() - 1;

							if (vec1[ind1].get_num_ticket() < vec2[ind2].get_num_ticket())
							{
								vec.insert(vec.end(), vec1.begin(), vec1.end());
								vec.insert(vec.end(), vec2.begin(), vec2.end());
							}
							else
							{
								vec.insert(vec.end(), vec2.begin(), vec2.end());
								vec.insert(vec.end(), vec1.begin(), vec1.end());
							}
						}*/
						else
						{
							vec.insert(vec.end(), vec2.begin(), vec2.end());
							vec.insert(vec.end(), vec1.begin(), vec1.end());
						}
						for (vector<Library_card>::iterator it = vec.begin(); it < vec.end(); it++)
							outA << *it;
					}
					else
					{
						if (vec1.size() == 0)
						{
							for (vector<Library_card>::iterator it = vec2.begin(); it < vec2.end(); it++)
								outA << *it;
						}
						else if (vec2.size() == 0)
						{
							for (vector<Library_card>::iterator it = vec1.begin(); it < vec1.end(); it++)
								outA << *it;
						}
					}
					vec.clear();
					vec1.clear();
					vec2.clear();
				}
				/*if (b)
				{
					while (!inC.eof())
					{
						inC >> t1;
						outA << t1;
					}
				}
				else
				{
					while (!inB.eof())
					{
						inB >> t1;
						outA << t1;
					}
				}*/


				inC.close();
			}
			inB.close();
		}
		outA.close();
	}
}

bool comp(Library_card first, Library_card second) { return first.get_num_ticket() < second.get_num_ticket(); }

ifstream& operator>>(ifstream& is, Library_card& en)
{
	is >> en.num_ticket;
	is >> en.num_inventory;
	is >> en.author;
	is >> en.title;
	is >> en.date_start;
	is >> en.date_end;
	return is;
}

ofstream& operator<<(ofstream& os, const Library_card& en)
{
	os << '\t' << en.num_ticket << '\t' <<
		en.num_inventory << '\t' <<
		en.author << '\t' <<
		en.title << '\t' <<
		en.date_start << '\t' <<
		en.date_end;
	return os;
}