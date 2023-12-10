#include "TTests.h"

void start(VecSeg* s, ofstream& file, double n)
{
	if (file.is_open())
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		cout << s->intersecNaive() << endl;
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		
		file << n << " " << duration.count();
		
		start_time = std::chrono::high_resolution_clock::now();
		s->sortPoints(0, s->getPointLength() - 1);
		end_time = std::chrono::high_resolution_clock::now();
		auto sortTime = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
		
		start_time = std::chrono::high_resolution_clock::now();
		cout << s->intersecEf();
		end_time = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		file << " " << sortTime.count() << " " << duration.count() << endl;
	}
}

void Test1()
{
	VecSeg* s = new VecSeg;
	ofstream f;
	f.open("../1_1.txt");
	for (int i = 1; i <= 10001; i += 100)
	{
		cout << "i = " << i << endl;
		s->createRSByPoints(i);
		start(s, f, i);
		s->clear();
	}
	f.close();
	delete s;
}

void Test2()
{
	VecSeg* s = new VecSeg;
	ofstream f;
	f.open("../2_.txt");
	for (int i = 1901; i <= 10001; i += 100)
	{
		cout << "i = " << i << endl;
		s->createRSByPoints(10003, i);
		start(s, f, i);
		s->clear();
	}
	f.close();
	delete s;
}

void Test3()
{
	VecSeg* s = new VecSeg;
	ofstream f;
	f.open("../3.txt");
	for (int i = 1; i <= 10001; i += 100)
	{
		cout << "i = " << i << endl;
		s->createRSByLength(0.001, i);
		start(s, f, i);
		s->clear();
	}
	f.close();
	delete s;
}

void Test4()
{
	VecSeg* s = new VecSeg;
	ofstream f;
	f.open("../4.txt");
	double r = 0.001;
	while (r <= 0.01)
	{
		cout << "r = " << r << endl;
		s->createRSByLength(r, 10000);
		start(s, f, r);
		s->clear();
		r += 0.0001;
	}
	f.close();
	delete s;
}

