//Тестирование работы потока Worker :

TEST(WorkerTest, ChangingArray) {
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    short array_data[3][5] = { {5, 2, 0}, {2, 4, 2, 1, 2}, {0} };
    short** array = new short* [3];
    for (int i = 0; i < 3; i++) {
        array[i] = array_data[i];
    }
    HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, threadWorker, array, 0, NULL);
    // Ожидаем, пока поток Worker завершит работу
    while (!started) {
        Sleep(100);
    }
    // Проверяем, что массив был изменен правильно
    EXPECT_EQ(array[1][0], 2);
    EXPECT_EQ(array[1][1], 4);
    EXPECT_EQ(array[1][2], 2);
    EXPECT_EQ(array[1][3], 2);
    EXPECT_EQ(array[1][4], 1);
    CloseHandle(hThread);
    CloseHandle(hEvent);
    DeleteCriticalSection(&cs);
    delete[] array;
}
