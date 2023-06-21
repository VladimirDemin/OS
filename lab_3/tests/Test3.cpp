//Тестирование работы потока CountElement :

TEST(CountElementTest, CountingElements) {
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    short array_data[3][5] = { {5, 2, 0}, {2, 4, 2, 1, 2}, {0} };
    short** array = new short* [3];
    for (int i = 0; i < 3; i++) {
        array[i] = array_data[i];
    }
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, threadCountElement, array, 0, NULL);
    // Ожидаем, пока поток CountElement завершит работу
    WaitForSingleObject(hEvent, INFINITE);
    // Проверяем, что количество элементов было посчитано правильно
    EXPECT_EQ(array[0][2], 2);
    CloseHandle(hThread);
    CloseHandle(hEvent);
    DeleteCriticalSection(&cs);
    delete[] array;
}
