#include <algorithm>
#include <execution>
#include <iostream>
#include <future>
#include <functional>
#include <omp.h>
#include "Stopwatch.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
// Explicit computation
static int64_t sum(const int64_t n) {
	return n * (n + 1) / 2;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Sequential summation
static int64_t sumSerial(const int arr[], const int n) {
	int64_t sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int64_t sumPar1(const int arr[], const int n) {
	int64_t sum = 0;

#pragma omp parallel for default(none) shared(arr, n) reduction(+: sum)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int64_t sumPar2(const int arr[], const int n) {
	int64_t sum = 0;

#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int64_t sumPar3(const int arr[], const int n) {
	int64_t sum = 0;

#pragma omp parallel for default(shared) reduction(+: sum)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int64_t sumPar4(const int arr[], const int n) {
	int64_t sum = 0;

#pragma omp parallel for default(shared) reduction(+: sum) schedule(dynamic)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int64_t sumPar5(const int arr[], const int n) {
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static int64_t sumPar6(const int arr[], const int n) {
	int64_t sum = 0;

#pragma omp parallel for num_threads(1) reduction(+: sum) schedule(guided)
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Different summation tests
void summation() {
	cout << "\nSummation Tests" << endl;

	const int64_t N = 10000000;
	int* arr = new int[N];

	for (int i = 1, j = 0; i <= N; i++, j++) arr[j] = i;

	Stopwatch sw;

	sw.Start();
	int64_t sum0 = sum(N);
	sw.Stop();
	cout << "Explicit:                      " << sum0 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl << endl;

	sw.Start();
	int64_t sumS = sumSerial(arr, N);
	sw.Stop();
	cout << "Sequential:              sumS: " << sumS << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sumS == sum0) << endl << endl;

	sw.Start();
	int64_t sum1 = sumPar1(arr, N);
	sw.Stop();
	cout << "                         sum1: " << sum1 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sum1 == sum0) << endl << endl;

	sw.Start();
	int64_t sum2 = sumPar2(arr, N);
	sw.Stop();
	cout << "                         sum2: " << sum2 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sum2 == sum0) << endl << endl;

	sw.Start();
	int64_t sum3 = sumPar3(arr, N);
	sw.Stop();
	cout << "                         sum3: " << sum3 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sum3 == sum0) << endl << endl;

	sw.Start();
	int64_t sum4 = sumPar4(arr, N);
	sw.Stop();
	cout << "                         sum4: " << sum4 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sum4 == sum0) << endl << endl;

	sw.Start();
	int64_t sum5 = sumPar5(arr, N);
	sw.Stop();
	cout << "                         sum5: " << sum5 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sum5 == sum0) << endl << endl;

	sw.Start();
	int64_t sum6 = sumPar6(arr, N);
	sw.Stop();
	cout << "                         sum6: " << sum6 << " in " << sw.GetElapsedTimeMilliseconds() << " ms" << endl;
	cout << boolalpha << "The two operations produce the same results: " << (sum6 == sum0) << endl << endl;

	delete[] arr;
}
