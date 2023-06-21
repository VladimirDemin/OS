#include <windows.h>
#include <iostream>
#include <time.h>
#include <process.h>

using namespace std;
UINT WINAPI Worker(LPVOID arr) // объявление функции Worker, которая будет выполняться в отдельном потоке
{
    int max = 0; // переменная для хранения максимального значения в массиве
    int* array = (int*)arr; // приведение типа указателя на void к типу указателя на int
    int count = array[0]; // первый элемент массива содержит количество элементов

    for (int i = 1; i <= count; i++) // цикл для нахождения максимального значения в массиве
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    cout << "Max element in array is " << max << endl; // вывод на экран максимального значения
    return 0; // возвращение значения 0 для указания успешного завершения функции
}
int main() // объявление главной функции программы
{
    HANDLE	hWorker; // идентификатор второго потока
    UINT	IDWorker; // идентификатор второго потока

    int element; // переменная для хранения элементов массива
    cout << "Enter the size of array: "; // вывод на экран приглашения ввести размер массива
    int n; // переменная для хранения размера массива
    cin >> n; // ввод размера массива с консоли
    int* arr = new int[n+1]; // выделение памяти для массива целых чисел
    for (int i = 1; i <= n; i++) // цикл для ввода элементов массива
    {
        cout << "Enter the element of the array: "; // вывод на экран приглашения ввести элемент массива
        cin >> element; // ввод элемента с консоли
        arr[i] = element; // запись элемента в массив
    }
    arr[0] = n; // запись количества элементов в первый элемент массива
    cout << "Array: ";
    for (int i = 1; i <= n; i++) // цикл для вывода элементов массива на экран
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    hWorker = (HANDLE)_beginthreadex(NULL, 0, Worker, (void*)arr, 0, &IDWorker); // создание второго потока и передача ему указателя на массив arr
    cout << "Enter time you want to stop the thread:"; // вывод на экран приглашения ввести время для приостановки второго потока
    SuspendThread(hWorker); // приостановка второго потока
    int time; // переменная для хранения времени
    cin >> time; // ввод времени с консоли
    Sleep(time * 1000); // задержка на указанное количество секунд
    ResumeThread(hWorker); // возобновление второго потока
    WaitForSingleObject(hWorker, INFINITE); // ожидание завершения второго потока
    CloseHandle(hWorker); // освобождение ресурсов, связанных с вторым потоком
    return 0;
}
