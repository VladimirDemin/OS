#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int main(int argc, char* argv[])
{
	int size = atof(argv[0]);
	unsigned int* array = new unsigned int[size];
	unsigned int array_element;
	unsigned int A = atof(argv[argc - 2]);
	unsigned int B = atof(argv[argc - 1]);
	int j = 0;
	for (int i = 2; i < argc - 2; i++)
	{
		array_element = atof(argv[i]);
		if (array_element >= A && array_element <= B)
		{
			array[j] = atof(argv[i]);
			j++;
		}
	}
	for (; j < size; j++)
	{
		array[j] = 0;
	}
	cout << "new Array:";
	for (int i = 0; i < size; i++)
	{
		cout << array[i]<<" ";
	}
	_cputs("Press any key.");
	_getch();

	delete[] array;

	return 0;
}