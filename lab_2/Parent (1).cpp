#define _CRT_SECURE_NO_WARNING

#pragma warning(disable:4996)

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    char lpApplicationName[] = "C:\\Users\\HP Pavilion\\source\\repos\\test\\Debug\\Child.exe";
    char* ch = new char[1];
    char* lpCommandLine = new char[1];

    lpCommandLine = strcpy(lpCommandLine, "");
    cout << "Enter size of array: " << endl;
    int size;
    cin >> size;
    ch = _itoa(size, ch, 10);
    lpCommandLine = strcat(lpCommandLine, ch);
    lpCommandLine = strcat(lpCommandLine, " ");
    unsigned int array_element;
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < size; i++)
    {
        cin >> array_element;
        ch = _itoa(array_element, ch, 10);
        lpCommandLine = strcat(lpCommandLine, ch);
        lpCommandLine = strcat(lpCommandLine, " ");
    }
    cout << "Enter A:" << endl;
    unsigned int A;
    cin >> A;
    ch = _itoa(A, ch, 10);
    lpCommandLine = strcat(lpCommandLine, ch);
    lpCommandLine = strcat(lpCommandLine, " ");

    cout << "Enter B:" << endl;
    unsigned int B;
    cin >> B;
    ch = _itoa(B, ch, 10);
    lpCommandLine = strcat(lpCommandLine, ch);

    cout << "Enter X:" << endl;
    int X;
    cin >> X;

    STARTUPINFO lpStartUpInfo;
    ZeroMemory(&lpStartUpInfo, sizeof(STARTUPINFO));
    lpStartUpInfo.cb = sizeof(STARTUPINFO);
    lpStartUpInfo.dwFlags = STARTF_USEPOSITION;
    lpStartUpInfo.dwX = X;

    PROCESS_INFORMATION lpProcessInformation;
    if (!CreateProcess(lpApplicationName, lpCommandLine, NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE, NULL, NULL, &lpStartUpInfo, &lpProcessInformation))
    {
        _cputs("Press any key.");
        _getch();
    }

    WaitForSingleObject(lpProcessInformation.hProcess, INFINITE);
    CloseHandle(lpProcessInformation.hProcess);
    CloseHandle(lpProcessInformation.hThread);

    return 0;
}