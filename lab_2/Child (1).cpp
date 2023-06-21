#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int main(int argc, char* argv[])
{
    int size = atof(argv[0]); // получение размера массива из первого аргумента командной строки
    unsigned int* array = new unsigned int[size]; // создание динамического массива
    unsigned int array_element;
    unsigned int A = atof(argv[argc - 2]); // получение значения A из предпоследнего аргумента командной строки
    unsigned int B = atof(argv[argc - 1]); // получение значения B из последнего аргумента командной строки
    int j = 0;
    for (int i = 2; i < argc - 2; i++) // цикл для заполнения массива
    {
        array_element = atof(argv[i]); // получение очередного элемента из аргументов командной строки
        if (array_element >= A && array_element <= B) // проверка, попадает ли элемент в интервал [A, B]
        {
            array[j] = atof(argv[i]); // добавление элемента в массив
            j++;
        }
    }
    for (; j < size; j++) // заполнение оставшейся части массива нулями
    {
        array[j] = 0;
    }
    cout << "new Array:";
    for (int i = 0; i < size; i++) // вывод элементов массива на экран
    {
        cout << array[i]<<" ";
    }
    _cputs("Press any key."); // вывод на экран приглашения нажать любую клавишу
    _getch(); // ожидание нажатия любой клавиши на клавиатуре

    delete[] array; // освобождение памяти, выделенной под массив

    return 0;
}
