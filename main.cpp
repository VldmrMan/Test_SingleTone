
#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class SingleToneAccount
{
private:

	SingleToneAccount(string way = "Accounts.txt") //приватный конструктор
	{ 
		//setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы при наличии кирилицы в файлах
		char buff[50]; // буфер промежуточного хранения считываемого из файла текста, сделано допущение
					   // при котором ни одна строка не привышает 50 символов
		ifstream Accounts(way); // открыли файл для чтения	

		while (!Accounts.eof())
		{
			OneAccount buffclass = OneAccount(); // буфферная структура для добавления в вектор
			Accounts.getline(buff, 50);			 // первая строка отвечает за имя аккаунта
			buffclass.name = buff;				 // имя аккакунт присваивается в соответсвующий параметр структуры

			Accounts.getline(buff, 50);			 // аналогично для последующей строки
			buffclass.type = buff;

			accounts.push_back(buffclass);	     // добавление в структуру класса буфферной структуры
		}
		Accounts.close(); // закрываем файл
	};
	   	  
	~SingleToneAccount() = default; //приватный диструктор


	SingleToneAccount(const SingleToneAccount&) = delete;			     //отмена копирования 
	SingleToneAccount& operator = (const SingleToneAccount&) = delete;   // отмена равенства


	void* operator new(size_t) = delete;	//отмена создания с помощью new
	void* operator new[](size_t) = delete;  //отмена создания с помощью new


	void operator delete(void*) = delete;	//так как new удален удаляем и delete
	void operator delete[](void*) = delete; //так как new удален удаляем и delete


public:

	// была выбрана структура а не вектор либо мап по причине расширяемости 
	// данные о аккаунте могут быть дополнены добавлением  других полей
	// если имя станет не уникальным, можно добавить уникльный id 

	struct OneAccount
	{
		string name; //имя аккаунт
		string type; //тип(должность)
	};

	vector <OneAccount> accounts;		// создание вектора из структуры< опсианной выше
	
	static SingleToneAccount& getInst() //публичный метод для получение ссылки на статичный объект
	{
		static SingleToneAccount object;
		return object;
	}

};

class SingleToneSetting
{

private:

	SingleToneSetting(string way = "Settings.txt")  //приватный конструктор
	{
						// данные из слоя даты укомплектованы по 3 и принимают вид:
						// должность \n ЗП \n прмеия
		char buff1[50]; // буфер промежуточного хранения считываемого из файла текста
		char buff2[50]; // буфер промежуточного хранения считываемого из файла текста
		char buff3[50]; // буфер промежуточного хранения считываемого из файла текста

		ifstream Settings(way); // открыли файл для чтения		
		//cout << "////////////////////////////////" << endl;
		while (!Settings.eof())
		{
			Settings.getline(buff1, 50); // 1 строка отвечает за наименование должности
			Settings.getline(buff2, 50); // 2 строка отвечает за значение ЗП
			Settings.getline(buff3, 50); // 3 строка отвечает за значение премии

			string frombuff1(buff1);		//преобразование к строке
			int frombuff2 = atoi(buff2);	//преобразование к целочисленному значению
			int frombuff3 = atoi(buff3);	//преобразование к целочисленному значению

			settings_value[frombuff1] = frombuff2; //добавление на карты значений
			settings_bonus[frombuff1] = frombuff3; //добавление на карты значений
		}
		Settings.close(); //закрыть файл

	}

	~SingleToneSetting() = default; //приватный диструктор

	SingleToneSetting(const SingleToneSetting&) = delete;			     //отмена копирования 
	SingleToneSetting& operator = (const SingleToneSetting&) = delete;   // отмена равенства

	void* operator new(size_t) = delete;	//отмена создания с помощью new
	void* operator new[](size_t) = delete;  //отмена создания с помощью new

	void operator delete(void*) = delete;	//так как new удален удаляем и delete
	void operator delete[](void*) = delete; //так как new удален удаляем и delete

public:
	//выбранна коллекция map из - за удобства последующего поиска с помощью встроенных 
	//средств
	map <string, int> settings_value; //карта ключ(должность) - значение (ЗП)
	map <string, int> settings_bonus; //карта ключ(должность) - значение (премия)


	static SingleToneSetting& getInst() //публичный метод для поулчения ссылки на статичный объект
	{
		static SingleToneSetting object;
		return object;
	}

};

class SingleToneCalculate
{
private:
	//входящие данные : слой с датой (данные о аккаунте, данные о настройках)
	SingleToneCalculate(SingleToneAccount& acc = SingleToneAccount::getInst(),
						SingleToneSetting& set = SingleToneSetting::getInst())
	{
		//обход всех позиций в списке аккаунтов
		for (int i = 0; i< acc.accounts.size(); i++)
		{
			// вывод результата расчета в форме таблицы
			// имя и должность берутся из файла аккакунтов
			// ЗП и Премия берется из файла с настройками
			// поиск проводится по должности из файла аккаунтов
			cout <<"name  : "<< acc.accounts.at(i).name<<endl;
			cout <<"post  : "<< acc.accounts.at(i).type << endl;
			cout <<"price : "<< set.settings_value[acc.accounts.at(i).type] <<" $"<< endl;
			cout <<"bonus : "<< set.settings_bonus[acc.accounts.at(i).type] <<" %"<< endl;

			cout <<"total : "<<
						
				set.settings_value[acc.accounts.at(i).type] * 
				(
				1 + set.settings_bonus[acc.accounts.at(i).type] * 0.01
				)			
							<<" $"<< endl;
			cout << "***********************" << endl;
		}
	}
	   	  
	~SingleToneCalculate() = default; //приватный диструктор


	SingleToneCalculate(const SingleToneCalculate&) = delete;			     //отмена копирования 
	SingleToneCalculate& operator = (const SingleToneCalculate&) = delete;   // отмена равенства


	void* operator new(size_t) = delete;	//отмена создания с помощью new
	void* operator new[](size_t) = delete;  //отмена создания с помощью new


	void operator delete(void*) = delete;	//так как new удален удаляем и delete
	void operator delete[](void*) = delete; //так как new удален удаляем и delete


public:

	static SingleToneCalculate& getInst() //публичный метод для поулчения ссылки на статичный объект
	{
		static SingleToneCalculate object;
		return object;
	}

};

int main()
{
	SingleToneCalculate& x = SingleToneCalculate::getInst();
	system("pause");
	return 0;
}



