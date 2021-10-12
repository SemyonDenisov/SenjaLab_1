#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <locale>
#include <string>
#include<windows.h>
class MyString
{
private:
	char* data;
	int size;
public:
	MyString()
	{
		data = NULL;
		size = 0;
	}
	MyString(const char* str)
	{
		size = 0;
		const char* temp = str;
		while(*temp)
		{
			size++;
			temp++;
		}
		data = new char[size+1];
		for (int i = 0; i < size; i++)
		{
			data[i] = str[i];
		}
		data[size] = '\0';
	}
	MyString(const MyString& other)
	{
		this->size = other.size;
		data = new char[size + 1];
		for (int i = 0; i < size; i++)
		{
			data[i] = other.data[i];
		}
		if (data)
		{
			data[size] = '\0';
		}
	}
	~MyString()
	{
		if (data)
		{
			delete[] data;
		}
	}

	char& operator [] (int index)
	{
		if (index < 0 || index >= size)
		{
			throw "Invalid index";
		}
		return data[index];
	}

	friend MyString operator + (const MyString& str,const MyString& s) 
	{
		MyString result;
		result.size = str.size + s.size;
		result.data = new char[result.size + 1];
		strcpy(result.data, str.data);
		strcpy(result.data + str.size, s.data);
		return result;
	}

	friend MyString operator * (MyString& str,int count)
	{
		if (count < 0)
		{
			throw "Multiplying a string by negative number";
		}
		MyString result;
		result.size = count * str.size;
		result.data = new char[count * str.size+2];
		for (int k = 0; k < result.size; k++)
		{
			result.data[k] = str.data[k % str.size];
		}
		result.data[result.size] = '\0';
		return result;
	}

	friend MyString operator * (int count, MyString& str)
	{
		return operator * (str, count);
	}

	MyString substring(int index,int lenght)
	{
		if (index < 0 || index > size)
		{
			throw "Invalid index";
		}
		if (index+lenght > size)
		{
			throw "Incorrect substring parameters";
		}
		MyString str;
		str.data = new char[lenght+1];
		for (int i = index; i < lenght+index; i++)
		{
			str.data[str.size] = data[i];
			str.size++;
		}
		str.data[str.size] = '\0';
		return str;
	}

	bool operator == (MyString &str)
	{
		if (size != str.size)
		{
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (data[i] != str.data[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator !=(MyString& str)
	{
		return !(operator ==(str));
	}

	friend std::ostream& operator << (std::ostream& out, const MyString& str)
	{
		out << "MyString:  ";
		for (int i = 0; i < str.size; i++)
		{
			out << str.data[i];
		}
		return out;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	bool ex = true;
	char* string_1 = new char;
	char* string_2 = new char;
	std::cout <<"Enter the first string:";
	std::cin >> string_1;
	MyString A(string_1);
	std::cout << "Enter the second string:";
	std::cin >> string_2;
	MyString B(string_2);
	while (ex)
	{
		std::cout <<"1)"<< A << std::endl;
		std::cout <<"2)"<< B << std::endl;
		std::cout << "\n";
		std::cout << "Выберите пункт:" << std::endl;
		std::cout << "1)Изменение элемента по индексу" << std::endl;
		std::cout << "2)Проверка на равенство строк" << std::endl;
		std::cout << "3)Конкатенация строк" << std::endl;
		std::cout << "4)Получение подстроки" << std::endl;
		std::cout << "5)Умножение строки на число" << std::endl;
		std::cout << "6)Выход" << std::endl;
		std::cin >> n;
		system("cls");
		std::cout <<"1)"<< A << std::endl;
		std::cout <<"2)"<< B << std::endl;
		switch (n)
		{

			case 1://Изменение элемента по индексу
			{
				int number;
				std::cout << "Какую строку хотите изменить:" << std::endl;
				std::cin >> number;
				int index;
				char character;
				std::cout << "Введите индекс элемента:" << std::endl;
				std::cin >> index;
				std::cout << "Введите элемент:" << std::endl;
				std::cin >> character;
				system("cls");
				if (number == 1)
				{
					try
					{
						A[index] = character;
					}
					catch(const char*err)
					{
						std::cout << err << std::endl;
					}
				}
				if (number == 2)
				{
					try
					{
						B[index] = character;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
					}
				}
				break;
			}

			case 2:
				{//Проверка на равенство строк
					system("cls");
					if (A == B)
					{
						std::cout << "Строки равны" << std::endl;
					}
					else
						std::cout << "Строки не равны" << std::endl;
					break;
				}

				case 3://Конкатенация строк
				{
					system("cls");
					MyString Result = A + B;
					std::cout << Result << " - Строка-результат"<< std::endl;
					break;
				}

			case 4://Получение подстроки
			{
				int number;
				std::cout << "У какой строки хотите получить подстроку:" << std::endl;
				std::cin >> number;
				int index;
				int lenght;
				std::cout << "Введите индекс, с котрого будет начинаться подстрока" << std::endl;
				std::cin >> index;
				std::cout << "Введите длину подстроки" << std::endl;
				std::cin >> lenght;
				system("cls");
				if (number == 1)
				{
					try
					{
						MyString D = A.substring(index, lenght);
						std::cout << D << " - Строка-результат" << std::endl;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
					}
				}
				if (number == 2)
				{
					try
					{
						MyString D = B.substring(index, lenght);
						std::cout << D << " - Строка-результат"<<std::endl;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
					}
				}
				break;
			}

			case 5://Умножение строки на число
			{
				int number;
				int count;
				std::cout << "Какую строку хотите умножить:" << std::endl;
				std::cin >> number;
				std::cout << "На какое число хотите умножить:" << std::endl;
				std::cin >> count;
				system("cls");
				if (number == 1)
				{
					try
					{
						MyString D = A * count;
						std::cout << D << " - Строка-результат" << std::endl;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
					}
				}
				if (number == 2)
				{
					try
					{
						MyString D = B * count;
						std::cout << D << " - Строка-результат" << std::endl;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
					}
				}
				break;
			}

			case 6://Выход
			{
				system("cls");	
				ex = false;
			}
		}
	}
	return 0;
};