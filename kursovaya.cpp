/*Студент потока характеризуется следующими данными:
-ФИО(до 50 символов);
-номер группы;
-набор из пяти оценок за последнюю сессию(без указания предметов);
-размер стипендии.
Необходимо:
1) разработать(и программно реализовать) динамические структуры данных и
алгоритмы их обработки, позволяющие поддерживать выполнение следующих функций :
-консольный ввод / вывод данных о всех студентах потока;
-файловый ввод / вывод данных о потоке;
-редактирование данных о студентах и группах потока, включающее операции
добавления / удаления групп и студентов;
2) разработать и программно реализовать алгоритмы обработки базы данных,
предусмотренные персональным заданием
ИДЗ:
1)Вывести перечень номеров групп, упорядоченный по значению показателя
«число двоечников» / «списочная численность группы»
2)Вывести в порядке следования номеров групп фамилии тех студентов, у 
которых личный средний балл не превышает заданного значения*/
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <vector>

using namespace std;
struct students
{
	char FIO[200];//ФИО	
	int mark1=0;//Набор оценок
	int mark2=0;
	int mark3=0;
	int mark4=0;
	int mark5=0;
	float middle_mark = 0;
	int stip=0;//стипендия
	students* next_student;
	int flag = 0;
	int group_number;
};
struct group_numbers 
{
	int number = 0;//Номер группы
	group_numbers* next_group;//следующая группа
	int flag = 0;//для заполнения
	students* info;//информация о студентах
	float  ratio;//отношение двоечников к общему количеству студентов
	group_numbers* sort;
};
group_numbers* h=nullptr, * buf=0, * hsort=nullptr,*bufsort1,*bufsort2;
students* k=nullptr, * bufs=0;

//Меню
int menu() {
	setlocale(LC_ALL, "RUS");
	system("cls");
	cout << "1)Добавить группу." << endl;
	cout << "2)Добавить студента." << endl;
	cout << "3)Выставить оценки." << endl;
	cout << "4)Назначить стипендию." << endl;
	cout << "5)Ввести с файла." << endl;
	cout << "6)Вывести в файл." << endl;
	cout << "7)Вывести в консоль." << endl;
	cout << "8)Удалить группу." << endl;
	cout << "9)Удалить студента" << endl;
	cout << "10)ИДЗ №1: Вывести перечень номеров групп, упорядоченный по значению показателя «число двоечников» / «списочная численность группы»" << endl;
	cout << "11)ИДЗ №2: Вывести в порядке следования номеров групп фамилии тех студентов, у которых личный средний балл не превышает заданного значения" << endl;
	cout << "12)Выйти из программы." << endl;
	return 0;
}
//Добавить группу
void group_add()
{
	cout << "Введите номер группы" << endl;
	if (h == nullptr) 
	{
		h = new group_numbers;
		
		cin >> h->number;		
		buf = h;
		buf->next_group = new group_numbers;
	}
	else 
	{		
		while (true) 
		{
			
			
			if (buf->number == 0) 
			{
				cin >> buf->number;		
				buf->next_group = new group_numbers;
				buf = h;
				break;
			}	
			buf = buf->next_group;
		}	
		buf = h;
	}
}
//Файловый ввод
void file_input(students*& k,group_numbers*& h) 
{
	int i;
	group_numbers* n;
	students* c;
	ifstream fin;
	fin.open("List1.txt");	
	fin >> h->number;
	if (h->number == 0)
	{
		delete h;
		cout << "Файл пустой";		
	}
	h->info = new students;
	k = h->info;
	cin.getline(k->FIO, 50);
	fin >> k->mark1 >> k->mark2 >> k->mark3 >> k->mark4 >> k->mark5;
	fin >> k->stip;
	n = h;
	c = k;
	
	while (!fin.eof())
	{
		c->next_student = new students;
		fin.ignore(32767, '\n');
		cin.getline(c->next_student->FIO,50 );		
		fin >> c->next_student->mark1 >> c->next_student->mark2 >>c->next_student->mark3 >> c->next_student->mark4 >> c->next_student->mark5;
		fin >> c->next_student->stip;
		c = c->next_student;
	}
	c->next_student = NULL;
	fin.close();	
}

//Консольный вывод
void output(){
	
	buf = h;
	while (buf->number != 0) {
		cout << buf->number << endl;
		bufs = buf->info;
		while (bufs->flag != 0) {
			cout << bufs->FIO << "|" << bufs->mark1 << " " << bufs->mark2 << " " << bufs->mark3 << " " << bufs->mark4 << " " << bufs->mark5 << "|" << bufs->stip << "|" << endl;
			bufs = bufs->next_student;
		}
		buf = buf->next_group;
	}
}
//Добавить студента
void student_add()
{
	
	int a;
	cout << "Введите номер группы" << endl;
	cin >> a;
	buf = h;
	while (buf->number != 0) {
		if (buf->number == a) {
			cout << "Введите ФИО студента" <<  endl;
			if (buf->flag == 0) {
				buf->info = new students;
				buf->flag = 1;
				k = buf->info;
				bufs = k;				
				cin.ignore();
				cin.getline(bufs->FIO, 50);
				bufs->next_student = new students;
				bufs->flag = 1;
				break;	
			}
			else
			{
				bufs = buf->info;
				while (true)
				{
					if (bufs->flag == 0)
					{
						cin.ignore();
						cin.getline(bufs->FIO, 50);
						bufs->flag = 1;
						bufs->next_student = new students;						
						break;
					}
					bufs = bufs->next_student;
				}	
				break;
			}
			
		}
		buf = buf->next_group;
	}	
	
}
//Назначит стипендию
void scholarship_add() {
	cout << "Введите номер группы" << endl;
	int a;
	cin >> a;
	buf = h;
	while (buf->number != 0) {
		if (buf->number == a) {
			cout << "Введите ФИО студента" << endl;
			char name[200];
			cin.ignore();
			cin.getline(name, 50);
			bufs = k;
			while (bufs->flag != 0) {
				if (_stricmp(name, bufs->FIO) == 0) {
					cout << "Введите размер стипендии" << endl;
					cin >> bufs->stip;
					break;
				}
				bufs = bufs->next_student;
			}
			break;
		}
		buf = buf->next_group;
	}
}
//Выставить оценки
void marks_add() {
	cout << "Введите номер группы" << endl;
	int a;
	cin >> a;
	buf = h;
	while (buf->number != 0) {
		if (buf->number == a) {
			cout << "Введите ФИО студента" << endl;
			char name[200];
			cin.ignore();
			cin.getline(name, 50);
			bufs = k;
			while (bufs->flag != 0) {
				if (_stricmp(name,bufs->FIO)==0) {
					cout << "Введите оценки студента через пробел" << endl;
					cin >> bufs->mark1 >> bufs->mark2 >> bufs->mark3 >> bufs->mark4 >> bufs->mark5;
					bufs->middle_mark = (bufs->mark1 + bufs->mark2 + bufs->mark3 + bufs->mark4 + bufs->mark5) / 5 * 1.0;
					break;
				}
				bufs = bufs->next_student;
			}
			break;
		}
		buf = buf->next_group;
	}
}
//Файловый вывод
void file_output()
{
	ofstream outf("List.txt");
	if (!outf)
	{

		cout << "Эх,файл List.txt не может быть открыт для записи!" << endl;
		exit(1);
	}
	buf = h;
	while (buf->number != 0) {
		outf << buf->number << endl;
		bufs = buf->info;
		while (bufs->flag != 0) {
			outf << bufs->FIO << "|" << bufs->mark1 << " " << bufs->mark2 << " " << bufs->mark3 << " " << bufs->mark4 << " " << bufs->mark5 << "|" << bufs->stip << "|" << endl;
			bufs = bufs->next_student;
		}
		buf = buf->next_group;
	}
}

//Удаление студента/группы
void delete_group() {
	int number;
	cout << "Введите номер группы";
	cin >> number;
	buf = h;
	if (h->number == number) {
		h = h->next_group;
	}
	else {
		while (buf->number != 0) {
			if (buf->next_group->number == number) {
				buf->next_group = buf->next_group->next_group;
			}
			buf = buf->next_group;
		}
	}
}
void delete_student() {
	int number;
	char name[200];	
	cout << "Введите номер группы" << endl;
	cin >> number;
	buf = h;
	while (buf->number != 0) {
		if (buf->number == number) {
			cout << "Введите ФИО студента" << endl;
			cin >> name;
			bufs = k;
			while (bufs->flag != 0) {
				if ((_stricmp(name, k->FIO) == 0)) {
					buf->info = k->next_student;
					k = buf->info;
					bufs = k;
					break;
				}
				if ((_stricmp(name, bufs->FIO) == 0) && (bufs->next_student == nullptr)) {
					bufs = nullptr;
					break;
				}
				if(_stricmp(name, bufs->next_student->FIO) == 0) {
					bufs->next_student = bufs->next_student->next_student;
					break;
				}
				bufs = bufs->next_student;
			}
			break;
		}
		buf = buf->next_group;
		
	}

}

//ИДЗ №1
void idz1() {
	int worst = 0, all = 0;
	buf = h;
	while (buf->number != 0) {
		bufs = buf->info;
		while (bufs->flag != 0) {
			all++;
			if (bufs->mark1 == 2 || bufs->mark2 == 2 || bufs->mark3 == 2 || bufs->mark4 == 2 || bufs->mark5 == 2) {
				worst++;
			}
			bufs = bufs->next_student;
		}
		buf->ratio = worst * 1.0 / all;
		worst = 0;
		all = 0;
		buf = buf->next_group;
	}
	buf = h;
	while (buf->number != 0) {
		if (h->ratio > h->next_group->ratio) {
			bufsort1 = h;
			bufsort2 = h->next_group->next_group;
			h = h->next_group;
			h->next_group = bufsort1;
			buf = h->next_group;
			h->next_group->next_group = bufsort2;
		}
		if (buf->ratio > buf->next_group->ratio) {
			bufsort1 = buf;
			bufsort2 = buf->next_group->next_group;
			buf = buf->next_group;
			buf->next_group = bufsort1;
			buf = buf->next_group;
			buf->next_group->next_group = bufsort2;
		}
		buf = buf->next_group;
	}
	
	buf = h;
	while (buf->number != 0) {
		cout << buf->number << " " << buf->ratio << endl;
		buf = buf->next_group;
	}
}
//ИДЗ №2
void idz2() {
	int value=0;
	cout << "Введите средний балл";
	cin >> value;
	buf = h;
	while (buf->number != 0) {
		bufs = k;
		while (bufs->flag != 0) {
			if (bufs->middle_mark <= value) {
				cout << bufs->FIO << endl;
			}
			bufs = bufs->next_student;
		}
		buf = buf->next_group;
	}
}
//Вывод меню после функций
int menu_functions() {	
		menu();
		int a;
		int m;
		cin >> a;
		switch (a) {
		case 1:
			group_add();			
			cout << "Чтобы продолжить нажмите любую клавишу"<<endl;			
			cin >> m;
			menu_functions();
		case 2:
			student_add();

			cout << "Чтобы продолжить нажмите любую клавишу";			
			cin >> m;
			menu_functions();
		case 3:
			marks_add();
			cout << "Чтобы продолжить нажмите любую клавишу";						
			cin >> m;
			menu_functions();
		case 4:
			scholarship_add();
			cout << "Чтобы продолжить нажмите любую клавишу";			
			cin >> m;
			menu_functions();
		case 5:		
			h = new group_numbers;
			file_input(k,h);
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 6:		
			file_output();
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 7:
			output();
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 8:
			delete_group();
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 9:
			delete_student();
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 10:
			idz1();
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 11:
			idz2();
			cout << "Чтобы продолжить нажмите любую клавишу";
			cin >> m;
			menu_functions();
		case 12:
			return 0;
		default:;
		}	
	_getch();
	return 0;
}

int main()
{
	menu_functions();
}
