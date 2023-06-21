#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

// Объявление глобальных переменных
mutex mtx; // мьютекс для синхронизации потоков
mutex cv_mtx; // мьютекс для условной переменной
condition_variable_any cv; // условная переменная
bool started = false; // флаг, указывающий на запуск потока Worker

// Функция потока, считающего элементы массива, равные X
void threadCountElement(short** array)
{
    // Блокировка мьютекса
    unique_lock<mutex> lock(mtx);
    // Перебор элементов массива
    for (short i = 0; i < array[0][0]; i++)
    {
        if (array[1][i] == array[0][1])
        {
            array[0][2]++;
        }
    }

    // Разблокировка мьютекса и уведомление ожидающего потока
    lock.unlock();
    cv.notify_one();
}

// Функция потока Worker, сортирующего элементы массива
void threadWorker(short** array, int seconds)
{
    // Блокировка мьютекса
    unique_lock<mutex> lock(mtx);

    // Запрос на ввод времени задержки
    cout << "Введите количество секунд, на которые поток будет останавливаться после подготовки одного элемента в массиве:" << endl;
    cin >> seconds;

    // Инициализация указателей на начало и конец массива
    short left = 0, right = array[0][0] - 1;

    // Сортировка массива
    while (left < right)
    {
        if (array[1][left] % 5 == 0 && array[1][left] > 0)
        {
            left++;
        }
        else if (array[1][right] % 5 == 0 && array[1][right] > 0)
        {
            swap(array[1][left], array[1][right]);
            left++;
            right--;
        }
        else
        {
            right--;
        }

        // Задержка на указанное количество секунд
        this_thread::sleep_for(chrono::seconds(seconds));
    }

    // Вывод отсортированного массива
    cout << "Поток Work закончил работу. Итоговый массив:" << endl;
    for (int i = 0; i < array[0][0]; i++)
    {
        cout << array[1][i] << endl;
    }

    // Установка флага о завершении работы потока
    started = true;

    // Разблокировка мьютекса и уведомление ожидающего потока
    lock.unlock();
    cv.notify_one();                                                                                                                                                                                                                                cv.notify_one();
}

int main()
{
    setlocale(LC_ALL, "ru");

    // Ввод размера массива
    int size;
    cout << "Введите размер массива: " << endl;
    cin >> size;

    // Создание массива и его заполнение
    short* array;
    array = new short[short(size)];
    cout << "Введите элементы массива:" << endl;
    for (short i = 0; i < short(size); i++)
    {
        cin >> array[i];
    }

    // Вывод введенного массива
    cout << "Введённый массив: " << endl;
    for (int i = 0; i < short(size); i++)
    {
        cout << array[i] << endl;
    }

    // Создание временного массива и его заполнение
    short** temp_array = new short* [2];
    temp_array[0] = new short[3];
    temp_array[0][0] = int(size);
    temp_array[0][1] = 0;
    temp_array[0][2] = 0;

    temp_array[1] = new short[temp_array[0][0]];
    for (int i = 0; i < temp_array[0][0]; i++)
    {
        temp_array[1][i] = array[i];
    }

    // Ввод значения X
    cout << "Введите X:" << endl;
    int X;
    cin >> X;
    temp_array[0][1] = X;

    // Создание и запуск потоков
    thread tWorker(threadWorker, temp_array, 0);
    thread tCountElement(threadCountElement, temp_array);

    // Ожидание завершения работы потока Worker
    unique_lock<mutex> lock(cv_mtx);
    cv.wait(lock, [] {return started; });
    lock.unlock();

    // Ожидание завершения работы потоков
    tWorker.join();
    tCountElement.join();

    // Вывод количества элементов, равных X
    cout << "Кол-во элементов, равных X: " << temp_array[0][2] << endl;

    // Освобождение памяти
    delete[] array;
    delete[] temp_array[0];
    delete[] temp_array[1];
    delete[] temp_array;

    return 0;
}