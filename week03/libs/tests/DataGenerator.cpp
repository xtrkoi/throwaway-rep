#include "DataGenerator.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

const int data_sizes[] = { 10'000, 30'000, 50'000, 100'000, 200'000, 500'000, 1'000'000, 2'000'000, 5'000'000, 10'000'000, 20'000'000};
const char * data_props[] = { "random", "sorted", "reversed", "nearly", "repeated" };

//-------------------------------------------------
// Random number generator

#include <chrono>
#include <random>
#include <cassert>

// Random seed
const int SEED = std::chrono::steady_clock::now().time_since_epoch().count();

// Set seed
// const int SEED = 1;

std::mt19937 mt_engine(SEED);

int rng(int lo, int hi)
{
	assert(lo <= hi);
	return lo + mt_engine() % (hi - lo + 1);
}

//-------------------------------------------------

template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));
	std::uniform_int_distribution<int> rand_int(0, n - 1);

	for (int i = 0; i < n; i++)
	{
		// a[i] = rand()%n;
		a[i] = rand_int(mt_engine);
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	std::uniform_int_distribution<int> rand_int(0, n - 1);
	int distance = (int)ceil(pow((double)n, 0.9));
	for (int i = 0; i < distance; i++)
	{
		// int r1 = rand()%n;
		// int r2 = rand()%n;
		int r1 = rand_int(mt_engine);
		int r2 = rand_int(mt_engine);
		HoanVi(a[r1], a[r2]);
	}
}

// Ham phat sinh mang du lieu gom nhieu du lieu trung nhau
void GenerateFewDistinctData(int a[], int n)
{
	int num_of_unique_values = max(1, (int)(pow((double)n, 0.2)));
	assert(num_of_unique_values > 0);

	std::uniform_int_distribution<int> rand_int(0, n - 1);
	for (int i = 0; i < num_of_unique_values; i++)
	{
		a[i] = rand_int(mt_engine);
	}

	for (int i = num_of_unique_values; i < n; i++)
	{
		a[i] = a[rng(0, i - 1)];
	}

	// Knuth Shuffle
	for (int i = n - 1; i > 0; i--)
	{
		int j = rng(0, i);
		HoanVi(a[j], a[i]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	case 4:
		GenerateFewDistinctData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}