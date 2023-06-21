#define _CRT_SECURE_NO_WARNING

#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    char lpApplicationName[] = "C:\\Users\\HP Pavilion\\source\\repos\\test\\Debug\\Child.exe"; // путь к исполняемому файлу второй программы
    char* ch = new char[1];
    char* lpCommandLine = new char[1];

    lpCommandLine = strcpy(lpCommandLine, ""); // копирование строки в строку
    cout << "Enter size of array: " << endl;
    int size;
    cin >> size;
    ch = _itoa(size, ch, 10); // преобразование числа в строку
    lpCommandLine = strcat(lpCommandLine, ch); // добавление размера массива в командную строку
    lpCommandLine = strcat(lpCommandLine, " ");
    unsigned int array_element;
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < size; i++) // цикл для ввода элементов массива
    {
        cin >> array_element;
        ch = _itoa(array_element, ch, 10); // преобразование числа в строку
        lpCommandLine = strcat(lpCommandLine, ch); // добавление элемента массива в командную строку
        lpCommandLine = strcat(lpCommandLine, " ");
    }
    cout << "Enter A:" << endl;
    unsigned int A;
    cin >> A;
    ch = _itoa(A, ch, 10);
    lpCommandLine = strcat(lpCommandLine, ch); // добавление значения A в командную строку
    lpCommandLine = strcat(lpCommandLine, " ");

    cout << "Enter B:" << endl;
    unsigned int B;
    cin >> B;
    ch = _itoa(B, ch, 10);
    lpCommandLine = strcat(lpCommandLine, ch); // добавление значения B в командную строку

    cout << "Enter X:" << endl;
    int X;
    cin >> X;

    STARTUPINFO lpStartUpInfo;
    ZeroMemory(&lpStartUpInfo, sizeof(STARTUPINFO)); // обнуление структуры STARTUPINFO
    lpStartUpInfo.cb = sizeof(STARTUPINFO); // установка размера структуры STARTUPINFO
    lpStartUpInfo.dwFlags = STARTF_USEPOSITION; // установка флага STARTF_USEPOSITION
    lpStartUpInfo.dwX = X; // установка координаты X для нового окна

    PROCESS_INFORMATION lpProcessInformation;
    if (!CreateProcess(lpApplicationName, lpCommandLine, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &lpStartUpInfo, &lpProcessInformation)) // создание нового процесса с новым окном
    {
        _cputs("Press any key.");
        _getch();
    }

    WaitForSingleObject(lpProcessInformation.hProcess, INFINITE); // ожидание завершения процесса
    CloseHandle(lpProcessInformation.hProcess); // закрытие дескриптора процесса
    CloseHandle(lpProcessInformation.hThread); // закрытие дескриптора потока

    return 0;
}
