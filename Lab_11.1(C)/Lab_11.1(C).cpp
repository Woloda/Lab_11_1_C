#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>

using namespace std;

int operation(const char* fname, const char* gname, const int N);
void print(const char* gname, const int l);

int main()
{
	srand((unsigned)time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fname[101], gname[101];
	cout << "Введіть назву фізичного файлу компонентами якого є дійсні числа: "; cin >> fname; cout << endl;
	cout << "Введіть назву фізичного файлу компонентами, якого не можуть бути значеннями функції 'sinx': "; cin >> gname; cout << endl;

	FILE* file;

	file = fopen(fname, "wb");

	int N;
	cout << "Введіть кількість дійсних чисел: "; cin >> N; cout << endl;

	double x;
	for (int i = 0; i < N; i++)
	{
		x = (200.0 - rand() % 400 * 1.0) * 0.01;
		cout << x << endl;
		fwrite(&x, sizeof(double), N, file);
	}

	fclose(file);

	int l = operation(fname, gname, N);
	print(gname, l);

	return 0;
}

int operation(const char* fname, const char* gname, const int N)
{
	FILE* file_l;
	FILE* file_s;

	file_s = fopen(gname, "wb");
	file_l = fopen(fname, "rb");

	int l = 0;
	double y;
	double x;
	for (int g = 0; g < N; g++)
	{
		fread(&y, sizeof(double), N, file_l);
		if (!(y <= 1 && y >= -1))
		{
			x = y;
			l++;
			fwrite(&x, sizeof(double), l, file_s);
		}
	}
	fclose(file_s);
	fclose(file_l);
	return l;
}

void print(const char* gname, const int l)
{
	FILE* file_l;

	file_l = fopen(gname, "rb");

	cout << endl;
	cout << "Компоненти даного файла '" << gname << "' які не можуть бути значеннями функції 'sinx': " << endl << endl;
	double x;
	for (int g = 0; g < l; g++)
	{
		fread(&x, sizeof(double), l, file_l);
		cout << x << endl;
	}
	fclose(file_l);
}