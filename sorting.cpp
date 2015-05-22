#include <iostream>
#include <cstdlib>     // Enables use of rand()
#include <ctime>       // Enables use of time()
#include <vector>
#include <string>
using namespace std;

const unsigned int SIZE = 1000000;
const unsigned int LIM = 10000;

static unsigned int  r[SIZE];

static unsigned int  temp1[LIM];
static unsigned int  temp2[LIM];

static unsigned int pick[SIZE];
long int mswap = 0, mcomparison = 0;
long int qswap = 0, qcomparison = 0;

void insertionSort(unsigned int input[], unsigned int size, unsigned int *swap_in, unsigned int *comp_in)
{
	unsigned int curr, i, temp;
	unsigned long swap = 0, comparison = 0;
	for (curr = 1; curr < size; curr++)
	{
		i = curr;
		while (input[i]<input[i - 1])
		{
			temp = input[i];
			input[i] = input[i - 1];
			input[i - 1] = temp;
			i--;
			swap++;
		}
		comparison++; 
	}
	*swap_in = swap;
	*comp_in = comparison+swap;

//	cout << "(" << swap << "," << comparison + swap << ")";
}

void bubbleSort(unsigned int input[], unsigned int size, unsigned int *swap_in, unsigned int *comp_in)
{
	unsigned int curr, i, temp;
	unsigned int swap = 0, comparison = 0;
	for (curr = size; curr > 0; curr--)
	{
		i = 0;
		while (i < curr - 1)
		{
			if (input[i] > input[i + 1])
			{
				temp = input[i];
				input[i] = input[i + 1];
				input[i + 1] = temp;
				swap++;
			}
			else
			{
				comparison++;
			}
			i++;
		}
	}	
	*swap_in = swap;
	*comp_in = comparison + swap;
	//	cout << "(" << swap << "," << comparison + swap << ")";
}

void selectionSort(unsigned int input[], unsigned int size, unsigned int *swap_in, unsigned int *comp_in)
{
	unsigned curr, i, temp, min;
	unsigned int swap = 0, comparison = 0;
	for (curr = 0; curr < size; curr++)
	{
		min = curr;
		for (int i = curr + 1; i < size; i++)
		{
			if (input[min]>input[i])
			{
				min = i;
			}
			comparison++;
		}
		if (min != curr)
		{
			temp = input[min];
			input[min] = input[curr];
			input[curr] = temp;
			swap++;
		}
	}
	*swap_in = swap;
	*comp_in = comparison;
	//	cout << "(" << swap << "," << comparison << ")";
}

void merge(unsigned int *a, unsigned int *b, int start, int mid, int end) {
	int h, i, j, k;
	//	long int swap = 0, comparison = 0;
	h = start;
	i = start;
	j = mid + 1;

	while ((h <= mid) && (j <= end))
	{
		if (a[h] <= a[j])
		{
			b[i] = a[h];
			h++;
		}
		else
		{
			b[i] = a[j];
			j++;
		}
		i++;
		mswap++;
		mcomparison++;
	}
	if (h > mid)
	{
		for (k = j; k <= end; k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	else
	{
		for (k = h; k <= mid; k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	mswap++;

	// Write the final sorted array to our original one
	for (k = start; k <= end; k++)
	{
		a[k] = b[k];
	}
	//	cout << endl<<comparison;
}

void mergesort(unsigned int *a, unsigned int*b, int start, int end)
{
	int mid;
	if (start < end)
	{
		mid = (start + end) / 2;
		mergesort(a, b, start, mid);
		mergesort(a, b, mid + 1, end);
		merge(a, b, start, mid, end);
		//		cout << endl << start << "  " << mid << "  " << end;
	}
}

int partition(unsigned int* input, int p, int r)
{
	int pivot = input[p];
	while (p < r)
	{
		while (input[p] < pivot)
		{
			p++;
			qcomparison++;
		}
		while (input[r] > pivot)
		{
			r--;
			qcomparison++;
		}
		if (input[p] == input[r])
		{
			p++;
		}
		else if (p < r)
		{
			int tmp = input[p];
			input[p] = input[r];
			input[r] = tmp;
			qswap++;
		}
	}
	return r;
}

// The quicksort recursive function
void quicksort(unsigned int* input, int p, int r)//p = 0 r = 9
{
	if (p < r)
	{
		int j = partition(input, p, r);
		quicksort(input, p, j - 1);
		quicksort(input, j + 1, r);
	}
}

unsigned int * getRandom()
{
	srand(time(NULL));
	for (unsigned int i = 0; i < SIZE; ++i)
	{
		r[i] = rand();
		//		cout << r[i] << "  ";
	}

	return r;
}

int main()
{
	unsigned int swap, comp;
	

	string algorighem[5];
	algorighem[0] = "Insertion";
	algorighem[1] = "Bubble\t";
	algorighem[2] = "Selection";
	algorighem[3] = "Merge";
	algorighem[4] = "Quick";

	for (int i = 1; i <= 6; i++)
	{
		cout << "\t\t" << pow(10, i);
		if (i==4)
		{
			cout << "\t\t";
		}
	}
	cout << "\t\t" << "10K Up" << "\t\t" << "10K Down";
	cout << endl;



//	unsigned long int num;
	

	cout << algorighem[0];
	int j = 1;
	int x = 6;
	while (j <= x)
	{
		getRandom();
		int temp = pow(10, j);
		insertionSort(r, temp, &swap, &comp);
		cout << "\t(" << swap << "," << comp << ")";
		if (j==4)
		{
			for (int i = 0; i < temp; i++)
			{
				temp1[i] = r[i] ;
			}
			cout << "\t";
		}
		j++;
	}
	insertionSort(temp1, LIM, &swap, &comp);
	cout << "\t(" << swap << "," << comp << ")";
	for (int i = 0; i < LIM; i++)
	{
		temp2[LIM - 1 - i] = temp1[i];
	}
	insertionSort(temp2, LIM, &swap, &comp);
	cout << "\t(" << swap << "," << comp << ")";


	cout << endl<<algorighem[1];
	 j = 1;
	while (j <= x)
	{
		getRandom();
		int temp = pow(10, j);
		bubbleSort(r, temp, &swap, &comp);
		cout << "\t(" << swap << "," << comp << ")";
		if (j == 4)
		{
			for (int i = 0; i < temp; i++)
			{
				temp1[i] = r[i];
			}
		}
		j++;
		cout << "\t";
	}
	bubbleSort(temp1, LIM, &swap, &comp);
	cout << "\t(" << swap << "," << comp << ")";
	for (int i = 0; i < LIM; i++)
	{
		temp2[LIM - 1 - i] = temp1[i];
	}
	bubbleSort(temp2, LIM, &swap, &comp);
	cout << "\t(" << swap << "," << comp << ")";







	cout << endl << algorighem[2];
	j = 1;
	while (j <= x)
	{
		getRandom();
		int temp = pow(10, j);
		selectionSort(r, temp, &swap, &comp);
		cout << "\t(" << swap << "," << comp << ")";
		if (j == 4)
		{
			for (int i = 0; i < temp; i++)
			{
				temp1[i] = r[i];
			}
		}
		j++;
		cout << "\t";
	}
	selectionSort(temp1, LIM, &swap, &comp);
	cout << "\t(" << swap << "," << comp << ")";
	for (int i = 0; i < LIM; i++)
	{
		temp2[LIM - 1 - i] = temp1[i];
	}
	selectionSort(temp2, LIM, &swap, &comp);
	cout << "\t(" << swap << "," << comp << ")";








	cout << endl << algorighem[3]<<"\t";
	j = 1;
	while (j <= x)
	{
		getRandom();
		int temp = pow(10, j);
		mergesort(r, pick, 0, temp - 1);
//		mergeSort(r, temp, &swap, &comp);
		cout << "\t(" << mswap << "," << mcomparison << ")";
		if (j == 4)
		{
			for (int i = 0; i < temp; i++)
			{
				temp1[i] = r[i];
			}
		}
		j++;
		cout << "\t";
		mswap = 0;
		mcomparison = 0;
	}
	mergesort(r, pick, 0, LIM - 1);
	cout << "\t(" << mswap << "," << mcomparison << ")";
	mswap = 0;
	mcomparison = 0;

	for (int i = 0; i < LIM; i++)
	{
		temp2[LIM - 1 - i] = temp1[i];
	}
	mergesort(r, pick, 0, LIM - 1);
	cout << "\t(" << mswap << "," << mcomparison << ")";
	cout << endl << algorighem[4] << "\t";
	j = 1;
	while (j <= x)
	{
		getRandom();
		int temp = pow(10, j);
		quicksort(r, 0, temp - 1); 
		cout << "\t(" << qswap << "," << qcomparison << ")";
		if (j == 4)
		{
			for (int i = 0; i < temp; i++)
			{
				temp1[i] = r[i];
			}
		}
		j++;
		cout << "\t";
		qswap = 0;
		qcomparison = 0;
	}
	quicksort(temp1, 0, LIM - 1);
	cout << "\t(" << qswap << "," << qcomparison << ")";

	qswap = 0;
	qcomparison = 0;

	for (int i = 0; i < LIM; i++)
	{
		temp2[10 - 1 - i] = temp1[i];
	}
	quicksort(temp2, 0, LIM - 1);
	cout << "\t(" << qswap << "," << qcomparison << ")";


	cout << "endl";
}
