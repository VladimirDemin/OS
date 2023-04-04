#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

const int MAX_MESSAGES = 100; // максимальное количество сообщений для каждого процесса Writer и Reader

HANDLE hMutex; // мьютекс для синхронизации работы процессов Writer
HANDLE hSemaphore; // семафор для синхронизации работы процессов Reader
HANDLE hEventA; // событие для передачи сообщения "A" от Writer к Reader
HANDLE hEventB; // событие для передачи сообщения "B" от Writer к Reader
HANDLE hEndSession; // событие для передачи сообщения о завершении сеанса

int k; // количество процессов Writer
int numMessages; // количество отправленных и принятых сообщений для каждого процесса Writer и Reader

DWORD WINAPI WriterThread(LPVOID lpParam)
{
    int id = *((int*)lpParam);

    for (int i = 0; i < numMessages; i++)
    {
        string message;
        cout << "Writer " << id << " enter message: ";
        cin >> message;

        WaitForSingleObject(hMutex, INFINITE);

        if (message == "A")
        {
            SetEvent(hEventA);
            cout << "Writer " << id << " sent message A" << endl;
        }
        else if (message == "B")
        {
            SetEvent(hEventB);
            cout << "Writer " << id << " sent message B" << endl;
        }
        else
        {
            cout << "Invalid message" << endl;
            i--;
        }

        ReleaseMutex(hMutex);
    }

    SetEvent(hEndSession);
    cout << "Writer " << id << " end session" << endl;

    return 0;
}

DWORD WINAPI ReaderThread(LPVOID lpParam)
{
    int id = *((int*)lpParam);

    for (int i = 0; i < numMessages; i++)
    {
        WaitForSingleObject(hSemaphore, INFINITE);

        WaitForSingleObject(hEventA, INFINITE);
        cout << "Reader " << id << " received message A" << endl;
        ResetEvent(hEventA);

        WaitForSingleObject(hEventB, INFINITE);
        cout << "Reader " << id << " received message B" << endl;
        ResetEvent(hEventB);

        ReleaseSemaphore(hSemaphore, 1, NULL);
    }

    SetEvent(hEndSession);
    cout << "Reader " << id << " end session" << endl;

    return 0;
}

int main()
{
    // Инициализация объектов синхронизации
    hMutex = CreateMutex(NULL, FALSE, NULL);
    hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);
    hEventA = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEventB = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEndSession = CreateEvent(NULL, FALSE, FALSE, NULL);

    // Запрос у пользователя k-количество процессов Writer
    cout << "Enter k: ";
    cin >> k;

    // Запрос у пользователя кол-во отправленных и принятых сообщений для процессов Writer и Reader
    cout << "Enter num messages: ";
    cin >> numMessages;

    // Запуск заданного количества процессов Reader и Writer
    HANDLE* hWriterThreads = new HANDLE[k];
    HANDLE* hReaderThreads = new HANDLE[2 * k];
    int* writerIds = new int[k];
    int* readerIds = new int[2 * k];

    for (int i = 0; i < k; i++)
    {
        writerIds[i] = i + 1;
        hWriterThreads[i] = CreateThread(NULL, 0, WriterThread, &writerIds[i], 0, NULL);
    }

    for (int i = 0; i < 2 * k; i++)
    {
        readerIds[i] = i + 1;
        hReaderThreads[i] = CreateThread(NULL, 0, ReaderThread, &readerIds[i], 0, NULL);
    }

    // Принимает от каждого процесса Reader и Writer сообщение о завершении сеанса и выводит его на консоль в одной строке
    WaitForMultipleObjects(k, hWriterThreads, TRUE, INFINITE);
    WaitForMultipleObjects(2 * k, hReaderThreads, TRUE, INFINITE);

    cout << "All sessions are finished" << endl;

    // Освобождение ресурсов
    CloseHandle(hMutex);
    CloseHandle(hSemaphore);
    CloseHandle(hEventA);
    CloseHandle(hEventB);
    CloseHandle(hEndSession);

    delete[] hWriterThreads;
    delete[] hReaderThreads;
    delete[] writerIds;
    delete[] readerIds;

    return 0;
}