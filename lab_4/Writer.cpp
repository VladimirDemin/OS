#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

// Объявление глобальных переменных
HANDLE A, B, endWriter; // дескрипторы событий
HANDLE hMutex; // дескриптор мьютекса

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");
	// Создание объектов событий
	wchar_t A_event[20];
	MultiByteToWideChar(CP_ACP, 0, "A", -1, A_event, 20);
	A = CreateEvent(NULL, FALSE, FALSE, A_event);
	if (A == NULL)
		return GetLastError();

	wchar_t B_event[20];
	MultiByteToWideChar(CP_ACP, 0, "B", -1, B_event, 20);
	B = CreateEvent(NULL, FALSE, FALSE, B_event);
	if (B == NULL)
		return GetLastError();

	wchar_t Endr_event[20];
	MultiByteToWideChar(CP_ACP, 0, "endR", -1, Endr_event, 20);
	endWriter = CreateEvent(NULL, FALSE, FALSE, Endr_event);
	if (endWriter == NULL)
		return GetLastError();

	// Создание мьютекса
	wchar_t Mutex_1_W[20];
	MultiByteToWideChar(CP_ACP, 0, "MutexW1", -1, Mutex_1_W, 20);
	hMutex = CreateMutex(NULL, FALSE, Mutex_1_W);
	if (hMutex == NULL)
	{
		cout << "Мьютекс не создан" << endl;
		cin.get();
		return GetLastError();
	}

	// Получение номера Writer и количества сообщений
	int n = atoi(argv[0]);
	cout << "Writer #" << n << endl;
	int m_count = atoi(argv[1]);

	// Захват мьютекса
	char mess;
	HANDLE mass[] = { hMutex };
	int mutex_num = WaitForSingleObject(mass, INFINITE) - WAIT_OBJECT_0;

	// Ввод и отправка сообщений
	cout << "Введите сообщения A или В (всего " << m_count << " сообщений):" << endl;
	for (int i = 0; i < m_count; i++)
	{
		cin >> mess;
		if (mess == 'A') SetEvent(A);
		else if (mess == 'B') SetEvent(B);
		else i--;
	}

	// Освобождение мьютекса и закрытие дескрипторов событий
	cout << "Завершение работы..." << endl;
	if (mutex_num == 0) ReleaseMutex(hMutex);
	CloseHandle(A);
	CloseHandle(B);

	// Ожидание события endWriter
	WaitForSingleObject(endWriter, INFINITE);

	return 0;
}