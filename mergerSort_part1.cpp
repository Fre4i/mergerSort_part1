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
void mergeInA(int n, int size);

//Компаратор
bool comp(Library_card first, Library_card second);

int main()
{
	setlocale(LC_ALL, "ru");

	clearFiles();

	int len = 15;
	initFiles(len);

	printFiles();

	//for (int i = 0; pow(2, i) < len; i++)
	//	mergerSort((int)pow(2, i), len);

	mergerSort(2, len);

	printFiles();

    return 0;
}

//Работа с файлами
void initFiles(int size)
{
	ofstream outA;
	outA.open("A.txt");

	string arr_autors[] = { "В.А. Голубев", "Г.В. Александров", "В.С. Киров", "К.С. Андропов", "У.Е. Куницын" };
	string arr_books[] = { "Высшая математика", "Физика", "Правоведение", "Программирование", "Аналитическая геометрия и алгебра" };
	string arr_date_start[] = { "14.09.2021", "04.10.2021", "03.11.2021", "14.09.2021", "01.10.2021" };
	string arr_date_end[] = { "15.05.2022", "04.04.2022", "03.06.2022", "14.05.2022", "01.05.2022" };

	if (outA)
	{
		//Инициализация файла A
		for (int i = 0; i < size; i++)
		{
			outA << rand() % size + 1 << '\t'
							<< rand() % 10 + 1 << '\t'
							<< arr_autors[rand() % 5 + 0] << '\t'
							<< arr_books[rand() % 5 + 0] << '\t'
							<< arr_date_start[rand() % 5 + 0] << '\t'
							<< arr_date_end[rand() % 5 + 0] << '\n';
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
		while (!inA.eof())
		{
			string t;
			getline(inA, t, '\n');
			cout << t << endl;
		}
	}
	inA.close();

	//Содержимое файла B
	cout << "\n\nСодержимое файла B\n";
	ifstream inB;
	inB.open("B.txt");

	if (inB)
	{
		while (!inB.eof())
		{
			string t;
			getline(inB, t, '\n');
			cout << t << endl;
		}
	}
	inB.close();

	//Содержимое файла C
	cout << "\n\nСодержимое файла C\n";
	ifstream inC;
	inC.open("C.txt");

	if (inC)
	{
		while (!inC.eof())
		{
			string t;
			getline(inC, t, '\n');
			cout << t << endl;
		}
	}
	inC.close();
}

//Сортировка
void mergerSort(int n, int size)
{
	ifstream inA;
	ofstream outB, outC;

	inA.open("A.txt");

	if (inA)
	{
		outB.open("B.txt");
		if (outB)
		{
			outC.open("C.txt");
			if (outC)
			{
				/*int count = 0;
				bool b = true;

				string t;
				while (!inA.eof())
				{
					getline(inA, t, '\n');
					if (b)
					{
						if (count == n)
						{
							b = false;
							count = 0;
							outC << t << '\n';
						}
						else
						{
							count++;
							outB << t << '\n';
						}
					}
					else
					{
						if (count == n)
						{
							b = true;
							count = 0;
							outB << t << '\n';
						}
						else
						{
							count++;
							outC << t << '\n';
						}
					}
				}*/

				int count = 0;
				bool b = true;
				Library_card t;

				while (!inA.eof())
				{
					if (b)
					{
						if (count == n)
						{
							b = false;
							count = 0;
							outC << t;
						}
						else
						{
							count++;
							outB << t;
						}
					}
					else
					{
						if (count == n)
						{
							b = true;
							count = 0;
							outB << t;
						}
						else
						{
							count++;
							outC << t;
						}
					}
				}

				outC.close();
			}
			outB.close();
		}
		inA.close();
	}
	//mergeInA(n, size);
}

void mergeInA(int n, int size)
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
				string s;
				int num;
				bool b = false;
				if (size % 2 != 0)
				{
					size -= 1;
					b = true;
				}
				/*size = size / 2;*/

				vector<Library_card> vec;

				int t1, t2;
				string s1, s2, s3, s4;

				int count = 0;
				for (int i = 0; i < size;)
				{
					for (int j = 0; j < n; j+=2)
					{
						inB >> t1;
						inB >> t2;
						getline(inB, s1, '\t');
						getline(inB, s2, '\t');
						getline(inB, s3, '\t');
						getline(inB, s4, '\n');
						Library_card lbB(t1, t2, s1, s2, s3, s4);
						vec.push_back(lbB);

						inC >> t1;
						inC >> t2;
						getline(inC, s1, '\t');
						getline(inC, s2, '\t');
						getline(inC, s3, '\t');
						getline(inC, s4, '\n');
						Library_card lbC(t1, t2, s1, s2, s3, s4);
						vec.push_back(lbC);
						i+=2;
					}
					sort(vec.begin(), vec.end(), comp);
					for (vector<Library_card>::iterator it = vec.begin(); it < vec.end(); it++)
					{
						outA << (*it).toString() << '\n';
					}
					vec.clear();
				}

				if (b)
				{
					getline(inB, s, '\n');
					outA << s << '\n';
				}

				/*for (int i = 0; i < size;)
				{

				}
				if (b)
				{
					getline(inB, s, '\n');
					outA << s << '\n';
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
	os << en.num_ticket << ' ' <<
		en.num_inventory << ' ' <<
		en.author << ' ' <<
		en.title << ' ' <<
		en.date_start << ' ' <<
		en.date_end << '\n';
	return os;
}