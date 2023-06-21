#include <windows.h>
#include <iostream>
#include <time.h>
#include <process.h>
using namespace std;
CRITICAL_SECTION cs; // объявление глобальной критической секции, используемой для синхронизации потоков
HANDLE hEvent; // объявление события, используемого для синхронизации потоков
bool started = false; // флаг, используемый для проверки того, что поток CountElement запущен после завершения потока Worker

// функция threadCountElement считает количество элементов в массиве, равных заданному числу X
UINT WINAPI threadCountElement(LPVOID array)
{
    EnterCriticalSection(&cs); // вход в критическую секцию
    if (started) { // если поток Worker уже завершил работу
        cout << "Поток CountElement начал работу" << endl;
        short** new_array = (short**)array;
        for (short i = 0; i < new_array[0][0]; i++)
        {
            if (new_array[1][i] == new_array[0][1])
            {
                new_array[0][2]++;
            }
        }
        array = new_array;
        SetEvent(hEvent); // установка события, указывающего на то, что поток CountElement завершил работу
    }
    LeaveCriticalSection(&cs); // выход из критической секции
    return 0;
}

// функция threadWorker изменяет порядок элементов в массиве в соответствии с определенными правилами
UINT WINAPI threadWorker(LPVOID array)
{
    EnterCriticalSection(&cs); // вход в критическую секцию
    cout << "Введите количество секунд, на которые поток будет останавливаться после подготовки одного элемента в массиве:" << endl;
    int seconds;
    cin >> seconds;
    short** new_array = (short**)array;
    short left = 0, right = new_array[0][0];
    while (left < right){
        if (new_array[1][left] % 5 == 0 && new_array[1][left] > 0){
            left++;
        }
        else if (new_array[1][right] % 5 == 0 && new_array[1][right] > 0)
        {
            swap(new_array[1][left], new_array[1][right]);
            left++;
            right--;
        }else {right--;}
        Sleep(seconds*1000); // приостановка работы потока на указанное количество секунд
    }
    array = new_array;
    cout << "Поток Work закончил работу. Итоговый массив:" << endl;
    for (int i = 0; i < new_array[0][0]; i++){
        cout << new_array[1][i] << endl;}
    started = true; // установка флага, указывающего на то, что поток Worker завершил работу
    LeaveCriticalSection(&cs); // выход из критической секции
    return 0;
}

int main()
{
    InitializeCriticalSection(&cs); // инициализация критической секции
    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); // создание события
    setlocale(LC_ALL, "ru"); // установка локали
    int size;
    cout << "Введите размер массива: " << endl;
    cin >> size;
    short* array;
    array = new short[short(size)];
    cout << "Введите элементы массива:" << endl;
    for (short i = 0; i<short(size); i++)
    {
        cin >> array[i];
    }
    cout << "Введённый массив: " << endl;
    for (int i = 0; i<short(size); i++){
        cout << array[i] << endl;
    }
    short** temp_array = new short* [2]; // объявление двумерного массива
    temp_array[0] = new short[5]; // инициализация первого элемента массива
    temp_array[0][0] = int(size); // задание размера массива
    temp_array[0][2] = 0; // инициализация счетчика элементов, равных X
    temp_array[1] = new short[temp_array[0][0]]; // инициализация второго элемента массива
    for (int i = 0; i < temp_array[0][0]; i++)
    {
        temp_array[1][i] = array[i]; // копирование элементов из входного массива
    }
    HANDLE hThreadWorker;
    UINT IDThreadWorker;
    HANDLE hThreadCountElement;
    UINT IDThreadCountElement;
    hThreadWorker = (HANDLE)_beginthreadex(NULL, 0, threadWorker, (void*)temp_array, CREATE_SUSPENDED, &IDThreadWorker); // создание потока Worker
    hThreadCountElement = (HANDLE)_beginthreadex(NULL, 0, threadCountElement, (void*)temp_array, CREATE_SUSPENDED, &IDThreadCountElement); // создание потока CountElement
    cout << "Введите X:" << endl;
    int X;
    cin >> X;
    temp_array[0][1] = X; // задание значения X
    ResumeThread(hThreadWorker); // запуск потока Worker
    ResumeThread(hThreadCountElement); // запуск потока CountElement
    WaitForSingleObject(hThreadWorker, INFINITE); // ожидание завершения работы потока Worker
    WaitForSingleObject(hEvent, INFINITE); // ожидание установки события, указывающего на завершение работы потока CountElement
    WaitForSingleObject(hThreadCountElement, INFINITE); // ожидание завершения работы потока CountElement
    cout << "Кол-во элементов, равных X:" << temp_array[0][2] << endl; // вывод количества элементов, равных X
    CloseHandle(hThreadWorker); // закрытие дескриптора потока Worker
    CloseHandle(hThreadCountElement); // закрытие дескриптора потока CountElement
    DeleteCriticalSection(&cs); // удаление критической секции
    CloseHandle(hEvent); // закрытие дескриптора события
    return 0;
}
