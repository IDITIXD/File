#include <fstream>
#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;
class STREAM : public fstream
{
public:
	STREAM(const char* fn) :
		fstream(fn, ios::out | ios::in | ios::binary) {}
	void doneOurDate(const void* Ptr, int len, int sign)
	{
		if (!Ptr) return;
		if (len <= 0) return;
		if (sign == 0) write((char*)Ptr, len);
		else read((char*)Ptr, len);
	};
	STREAM& operator<< (int d)
	{
		doneOurDate(&d, sizeof(d), 0);
		return *this;
	}
	STREAM& operator>> (int& d)
	{
		doneOurDate(&d, sizeof(d), 1);
		return *this;
	}
};
class OUTSTREAM : public ofstream
{
public:
	OUTSTREAM(const char* fn) :
		ofstream(fn, ios::out | ios::binary) {}
	void writeOurDate(const void* Ptr, int len)
	{
		if (!Ptr) return;
		if (len <= 0) return;
		write((char*)Ptr, len);
	}
	ofstream& operator<< (int d)
	{
		writeOurDate(&d, sizeof(d));
		return *this;
	}
};
int main()
{
	setlocale(LC_ALL, "");
	int i, d, max, sum1 = 0, sum2 = 0;
	time_t t;
	srand((int)time(&t));
	OUTSTREAM bin_out("Bin.dat"); // создание файла
	if (!bin_out)
		cout << "ДАННЫЕ:\n";
	for (i = 0; i < 5; i++)
	{
		d = rand() % 100;
		bin_out << d;
		cout << d << ' ';
		sum1 += d;
	}

	for (i = 5; i < 10; i++)
	{
		d = rand() % 100;
		bin_out << d;
		cout << d << ' ';
		sum2 += d;
	}

	cout << endl;
	cout << "СУММА ПЕРВОЙ ЧАСТИ:" << sum1 << endl;
	cout << "СУММА ВТОРОЙ ЧАСТИ:" << sum2 << endl;
	bin_out.close();

	STREAM bin("Bin.dat");

	bin >> max;


	if (sum1 > sum2) cout << "В ПЕРВОЙ ПОЛОВИНЕ СУММА БОЛЬШЕ И РАВНА: " << sum1;
	else cout << "ВО ВТОРОЙ ПОЛОВИНЕ СУММА БОЛЬШЕ И РАВНА: " << sum2;

	cout << endl;
	bin.seekp(0, ios::beg);
	bin.close();
	_getch();
}
