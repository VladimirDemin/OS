#include <windows.h>
#include <iostream>
#include <time.h>
#include <process.h>
using namespace std;


CRITICAL_SECTION cs;
HANDLE hCountBegin, hCountEnd;

UINT WINAPI threadCountElement(LPVOID array)
{
	WaitForSingleObject(hCountBegin, INFINITE);
	EnterCriticalSection(&cs);
	short** new_array = (short**)array;
	for (short i = 0; i < new_array[0][0]; i++)
		{
			if (new_array[1][i] == new_array[0][1])
			{
				new_array[0][2]++;
			}
		}
	array = new_array;
	LeaveCriticalSection(&cs);
	SetEvent(hCountEnd);
	return 0;
}
UINT WINAPI threadWorker(LPVOID array)
{
	cout << "Введите количество секунд, на которые поток будет останавливаться после подготовки однонго элемента в массиве:" << endl;
		int seconds;
		cin >> seconds;
		short** new_array = (short**)array;

		short left = 0, right = new_array[0][0];
		while (left < right)
		{
			if (new_array[1][left] % 5 == 0 && new_array[1][left] > 0)
			{
				left++;
			}
			else if (new_array[1][right] % 5 == 0 && new_array[1][right] > 0) 
			{
				swap(new_array[1][left], new_array[1][right]);
				left++;
				right--;
			}
			else 
			{
				right--;
			}
			Sleep(seconds*1000);
		}
		array = new_array;
		SetEvent(hCountBegin);
		WaitForSingleObject(hCountEnd, INFINITE);
		return 0;
}

DWORD WINAPI threadMain(LPVOID size)
{
	InitializeCriticalSection(&cs);
	hCountBegin = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hCountBegin == NULL)
		return GetLastError();
	InitializeCriticalSection(&cs);
	hCountEnd = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hCountEnd == NULL)
		return GetLastError();


	short* array;
	array = new short[short(size)];
	cout << "Введите элементы массива:" << endl;
	for (short i = 0; i<short(size); i++)
	{
		cin >> array[i];
	}
	cout << "Введённый массив: " << endl;
	for (int i = 0; i<short(size); i++)
	{
		cout << array[i] << endl;
	}
	cout << "Введите X:" << endl ;
	int X;
	cin >> X;
	
	short** temp_array = new short* [2];
	temp_array[0] = new short[5];
	temp_array[0][0] = int(size);
	temp_array[0][1] = X;
	temp_array[0][2] = 0;

	temp_array[1] = new short[temp_array[0][0]];
	for (int i = 0; i < temp_array[0][0]; i++)
	{
		temp_array[1][i] = array[i];
	}
	HANDLE	hThreadWorker;
	UINT	IDThreadWorker;
	HANDLE	hThreadSummElement;
	UINT	IDThreadSummElement;


	hThreadWorker = (HANDLE)_beginthreadex(NULL, 0, threadWorker, (void*)temp_array, 0, &IDThreadWorker);
	hThreadSummElement = (HANDLE)_beginthreadex(NULL, 0, threadCountElement, (void*)temp_array, 0, &IDThreadWorker);
	WaitForSingleObject(hCountBegin, INFINITE);
	EnterCriticalSection(&cs);
	cout << "Поток CountElement закончил работу. Кол-во элементов, равных X: " << temp_array[0][2] << endl;
	LeaveCriticalSection(&cs);
	WaitForSingleObject(hThreadWorker, INFINITE);
	cout << "Поток Work закончил работу. Итоговый массив:" << endl;
	for (int i = 0; i < temp_array[0][0]; i++)
	{
		cout << temp_array[1][i] << endl;
	}

	CloseHandle(hThreadWorker);
	WaitForSingleObject(hThreadSummElement, INFINITE);
	CloseHandle(hThreadSummElement);

	DeleteCriticalSection(&cs);
	CloseHandle(hCountBegin);
	CloseHandle(hCountEnd);



	return 0;
}



int main()
{
	setlocale(LC_ALL, "ru");
	HANDLE	hThreadMain;
	DWORD	IDThreadMain;
	int size;
	cout << "Введите размер массива: " << endl;
	cin >> size;

	hThreadMain = CreateThread(NULL, 0, threadMain, (void*)size, 0, &IDThreadMain);
	if (hThreadMain == NULL)
		return GetLastError();


	WaitForSingleObject(hThreadMain, INFINITE);

	CloseHandle(hThreadMain);

	return 0;
}