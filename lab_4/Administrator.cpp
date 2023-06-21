#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
// Объявление глобальных переменных
HANDLE A, B, endWriter, endReader; // дескрипторы событий
HANDLE hMutex; // дескриптор мьютекса
HANDLE hSemaphore; // дескриптор семафора
int main()
{
	setlocale(LC_ALL, "ru");
	// Создание объектов событий
	A = CreateEvent(NULL, TRUE, FALSE, "A");
	if (A == NULL)
		return GetLastError();
	B = CreateEvent(NULL, TRUE, FALSE, "B");
	if (B == NULL)
		return GetLastError();
	endWriter = CreateEvent(NULL, FALSE, FALSE, "endW");
	if (endWriter == NULL)
		return GetLastError();
	endReader = CreateEvent(NULL, FALSE, FALSE, "endR");
	if (endReader == NULL)
		return GetLastError();

	// Создание мьютекса
	hMutex = CreateMutex(NULL, FALSE, "MutexW");
	if (hMutex == NULL)
	{
		cout << "Мьютекс не создан" << endl;
		cin.get();
		return GetLastError();
	}

	// Создание семафора
	hSemaphore = CreateSemaphore(NULL, 2, 2, "SemaphoreR");
	if (hSemaphore == NULL)
	{
		cout << "Семафор не создан" << endl;
		cin.get();
		return GetLastError();
	}

	// Запрос у пользователя значения k и m_count
	int k, m_count;
	cout << "Введите k - количество процессов Writer:" << endl;
	cin >> k;
	cout << "Введите количество cообщений, принятых Writer и прочитанных Reader:" << endl;
	cin >> m_count;

	// Создание объектов процессов Writer и Reader
	char lpszAppNameR[] = "C:\\Users\\HP Pavilion\\source\\repos\\OS_Lab4\\Debug\\Reader.exe";
	char lpszAppNameW[] = "C:\\Users\\HP Pavilion\\source\\repos\\OS_Lab4\\Debug\\Writer.exe";
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	HANDLE* H = new HANDLE[k * 3];
	PROCESS_INFORMATION piApp;
	for (int i = 0; i < k * 3; i++)
	{
		char* ch = new char[1];
		char* lpCommLine = new char[1];
		lpCommLine = strcpy(lpCommLine, "");
		ch = _itoa((i + 1), ch, 10);
		lpCommLine = strcat(lpCommLine, ch);
		ch = _itoa(m_count, ch, 10);
		lpCommLine = strcat(lpCommLine, " ");
		lpCommLine = strcat(lpCommLine, ch);
		if (i < k)
		{
			if (!CreateProcess(lpszAppNameW, lpCommLine, NULL, NULL, FALSE,
				CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
			{
				_cputs("Новый процесс не создан.\n");
				_getch();
				return 0;
			}
		}
		if (i >= k)
		{
			if (!CreateProcess(lpszAppNameR, lpCommLine, NULL, NULL, FALSE,
				CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
			{
				_cputs("Новый процесс не создан.\n");
				_getch();
				return 0;
			}
		}
		H[i] = piApp.hProcess;
	}

	// Ожидание завершения всех процессов
	WaitForMultipleObjects(3 * k, H, true, INFINITE);

	// Закрытие дескрипторов процессов Writer и Reader
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);

	// Сигнализование событий endWriter и endReader
	SetEvent(endWriter);
	SetEvent(endReader);

	// Закрытие дескрипторов объектов событий
	CloseHandle(endWriter);
	CloseHandle(endReader);
	CloseHandle(A);
	CloseHandle(B);

	// Закрытие дескрипторов мьютекса и семафора
	CloseHandle(hMutex);
	CloseHandle(hSemaphore);

	// Освобождение памяти, выделенной для массива дескрипторов процессов
	for (int i = 0; i < k * 3; i++)
	{
		CloseHandle(H[i]);
	}

	return 0;
}


