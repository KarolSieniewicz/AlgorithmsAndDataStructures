#include <iostream>
#include <list>
#include <iterator>
#include <cmath>
using namespace std;


void printArray(int* arr, int size, int maximum)
{
	cout << maximum;
	for (int i = 0; i < size; i++)
	{
		cout << '+' << arr[i];
	}
	cout << endl;
}

void sieveOfEratosthenes(bool prime[], int n)
{
	// Initial two numbers are not prime (0 and 1)
	prime[0] = false;
	prime[1] = false;
	// Set the initial (2 to n element is prime)
	for (int i = 2; i <= n; ++i)
	{
		prime[i] = true;
	}
	// We start to 2
	for (int i = 2; i * i <= n; ++i)
	{
		if (prime[i] == true)
		{
			// When i is prime number
			// Modify the prime status of all
			// next multiplier of location i
			for (int j = i * i; j <= n; j += i)
			{
				prime[j] = false;
			}
		}
	}
}

bool doesSumGiveNumber(int *numbers, int size, int wanted)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += numbers[i];
	}
	if (sum == wanted) return true;
	else return false;
}

void resetArray(int *numbers, int size)
{	
	for (int i = 1; i < size; i++)
	{
		numbers[i] = 2;
	}
}

int findNextPrime(int x, bool primes[])
{
	do
	{
		x++;
	} while (!primes[x]);
	return x;
}

void partition(int n, int *toPrint, int size, bool primes[], int maximum)
{	
	for (int i = 0; i < size; i++)
	{
		toPrint[i] = 2;
	}
	if (doesSumGiveNumber(toPrint, size, n))
	{
		printArray(toPrint, size, maximum);
		return;
	}
	while (toPrint[0] <= maximum)
	{
		toPrint[0] = findNextPrime(toPrint[0], primes);
		for (int i = 1; i < size; i++)
		{
			if (doesSumGiveNumber(toPrint, size, n))
			{
				printArray(toPrint, size, maximum);
				resetArray(toPrint, size);
			}
			while (toPrint[i] < toPrint[i - 1])
			{
				toPrint[i] = findNextPrime(toPrint[i], primes);
				if (doesSumGiveNumber(toPrint, size, n))
				{
					printArray(toPrint, size, maximum);
					resetArray(toPrint, size);
				}
			}
		}
	}	
}


int main()
{
	bool primes[256];
	sieveOfEratosthenes(primes, 256);
	int howMany;
	cin >> howMany;
	for (int partitions = 0; partitions < howMany; partitions++)
	{
		int main, start;
		cin >> main >> start;		
		int n = main - start;
		int main_k = n / 2;
		for (int i = main_k; i >= 1; i--)
		{
			int *toPrint = new int[i];
			partition(n, toPrint, i, primes, start);
			delete[] toPrint;
		}
	}
}


/*

// ADVANCED VERSION

// function for printing the elements in a list
void printSubList(list<int> g)
{
	list<int>::iterator it = g.begin();
	cout << *it;
	++it;
	for (;it != g.end(); ++it)
	{
		cout << '+' << *it;
	}
	cout << endl;
}

void printMainList(list<list<int>> g, int main)
{
	list<list<int>>::iterator it;
	for (it = g.begin(); it != g.end(); ++it)
	{
		cout << main << '=';
		printSubList(*it);
	}
}



void partition(int n, int k, list<int> currentList, list<list<int>>& mainList, bool primes[])
{
	if (k > 1)
	{
		int tmax = n;
		for (int i = 0, j = 3; i < k - 1; j++)
		{
			if (primes[j] && j>0)
			{
				tmax -= j;
				i++;
			}
		}
		tmax = abs(tmax);
		int tmin = n / k;
		if (tmax < tmin)
		{
			currentList.push_back(2);
			partition(n - 2, k - 1, currentList, mainList, primes);
		}
		else
		{
			for (int i = tmin; i <= tmax; i++)
			{
				if (primes[i] && i>0)
				{
					currentList.push_back(i);
					n = n - i;
					k--;
					partition(n, k, currentList, mainList, primes);
				}
			}
		}
	}
	else
	{
		if (primes[n] && n>0)
		{
			currentList.push_back(n);
			mainList.push_back(currentList);
			return;
		}
		else
		{
			currentList.clear();
			return;
		}
	}
}



//done
int main()
{
	bool primeNumbers[256]; // max number in the size of a byte
	sieveOfEratosthenes(primeNumbers, 256);
	int howMany;
	cin >> howMany;
	for (int partitions = 0; partitions < howMany; partitions++)
	{
		int main, start;
		cin >> main >> start;
		list<list<int>> mainPartitionsToPrint;
		int n = main - start;
		int main_k = n / 2;
		for (int i = main_k; i >= 1; i--)
		{
			list<int> currentList;
			currentList.push_back(start);
			partition(n, main_k, currentList, mainPartitionsToPrint, primeNumbers);
		}
		printMainList(mainPartitionsToPrint, main);
	}
}

*/
