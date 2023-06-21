#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

// Объявление глобальных переменных
HANDLE A, B, endReader; // дескрипторы событий
HANDLE hSemaphore; // дескриптор семафора

int main(int argc, char* argv[])
{           
	setlocale(LC_ALL, "ru");
	// Создание объектов событий
	wchar_t A_event[20];
	MultiByteToWideChar(CP_ACP, 0, "A", -1, A_event, 20);
	A = CreateEvent(NULL, TRUE, FALSE, A_event);
	if (A == NULL)
		return GetLastError();

	wchar_t B_event[20];
	MultiByteToWideChar(CP_ACP, 0, "B", -1, B_event, 20);
	B = CreateEvent(NULL, TRUE, FALSE, B_event);
	if (B == NULL)
		return GetLastError();

	wchar_t Endr_event[20];
	MultiByteToWideChar(CP_ACP, 0, "endR", -1, Endr_event, 20);
	endReader = CreateEvent(NULL, TRUE, FALSE, Endr_event);
	if (endReader == NULL)
		return GetLastError();

	// Создание семафора
	wchar_t Semaphore_R[20];
	MultiByteToWideChar(CP_ACP, 0, "SemaphoreR", -1, Semaphore_R, 20);
	hSemaphore = CreateSemaphore(NULL, 2, 2, Semaphore_R);
	if (hSemaphore == NULL)
	{
		cout << "Семафор не создан" << endl;
		cin.get();
		return GetLastError();
	}

	// Получение номера Reader и количества сообщений
	int n = atoi(argv[0]);
	int m_count = atoi(argv[1]);
	cout << "Reader #" << n << endl;

	// Ожидание доступа к семафору
	WaitForSingleObject(hSemaphore, INFINITE);
	cout << "active";

	// Создание массива объектов событий и получение сообщений
	HANDLE array[] = { A, B };
	m_count /= 2;
	for (int i = 0; i < m_count; i++)
	{
		int ind = WaitForMultipleObjects(2, array, FALSE, INFINITE) - WAIT_OBJECT_0;
		if (ind == 0)
		{
			cout << "Получено сообщение A от Writer" << endl;
			ResetEvent(A);
		}
		else if (ind == 1)
		{
			cout << "Получено сообщение B от Writer" << endl;
			ResetEvent(B);
		}
	}

	// Освобождение семафора и закрытие дескрипторов событий
	cout << "Завершение работы..." << endl;
	ReleaseSemaphore(hSemaphore, 1, NULL);
	CloseHandle(A);
	CloseHandle(B);

	// Ожидание события endReader
	WaitForSingleObject(endReader, INFINITE);

	return 0;
}


