#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "iostream"
class MyString
{
private:
	char* data = NULL;
	int size = 0;
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
		if (size != other.size)
		{
			size = other.size;
			delete[] data;
			data = new char[size + 1];
		}
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
		if (index < 0 || index > size)
		{
			throw "Invalid index";
		}
		return data[index];
	}
	friend MyString operator + (const MyString str,const MyString s) 
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
	int GetSize() { return size; }
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

	bool operator == (MyString str)
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
	friend std::ostream& operator << (std::ostream& out, const MyString& str)
	{
		out << "MyString  ";
		for (int i = 0; i < str.size; i++)
		{
			out << str.data[i];
		}
		return out;
	}
};
int main()
{
	MyString A("gaaaaan");
	MyString B("guuuun");
	std::cout << A;
	std::cout << "\n";
	try
	{
		A[-1] = 'q';
	}
	catch (const char*err)
	{
		std::cout << err;
		std::cout << "\n";
		A[0] = 'g';
	}
	if (A == B)
	{
		printf("Yeah");
	}
	else
		printf("NoNo");
	std::cout << "\n";
	MyString C = A + B;
	std::cout << C;
	std::cout << " - +";
	std::cout << "\n";
	try
	{
		MyString D = A.substring(1, 6);
		std::cout << D;
	}
	catch(const char* err)
	{
		std::cout << err;
		std::cout << "\n";
		MyString D = A.substring(0, 1);
		std::cout << D;
	}
	std::cout << " - Sub";
	std::cout << "\n";
	try
	{
		MyString X = A * -1;
	}
	catch (const char* err)
	{
		std::cout << err;
		std::cout << "\n";
		MyString X = A * 3;
		std::cout << X;
	}
	MyString Y = 4 * A;
	std::cout << " - *";
	std::cout << "\n";
	std::cout << Y;
	std::cout << " - *";
	return 0;
};