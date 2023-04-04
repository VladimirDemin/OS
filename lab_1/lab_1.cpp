#include <windows.h>
#include <iostream>
#include <time.h>
#include <process.h>

using namespace std;
UINT WINAPI Worker(LPVOID arr)
{
    int max = 0;
    int* array = (int*)arr;
    int count = array[0];

    for (int i = 1; i <= count; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    cout << "Max element in array is " << max << endl;
    return 0;
}
int main() 
{
    HANDLE	hWorker;
    UINT	IDWorker;

    int element;
    cout << "Enter the size of array: ";
    int n;
   
    cin >> n;
    int* arr = new int[n+1];
    for (int i = 1; i <= n; i++) 
    {
        cout << "Enter the element of the array: ";
        cin >> element;
        arr[i] = element;
    }
    arr[0] = n;
    cout << "Array: ";
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    hWorker = (HANDLE)_beginthreadex(NULL, 0, Worker, (void*)arr, 0, &IDWorker);
    cout << "Enter time you want to stop the thread:";
    SuspendThread(hWorker);
    int time;
    cin >> time;
    Sleep(time * 1000);
    ResumeThread(hWorker);

    WaitForSingleObject(hWorker, INFINITE);
    CloseHandle(hWorker);
    return 0;
}
