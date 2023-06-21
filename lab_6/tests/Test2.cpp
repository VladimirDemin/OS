//Тестирование работы события :

TEST(EventTest, SetAndReset) {
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    // Проверяем, что событие не поднято
    EXPECT_TRUE(WaitForSingleObject(hEvent, 0) == WAIT_TIMEOUT);
    // Поднимаем событие
    SetEvent(hEvent);
    // Проверяем, что событие поднято
    EXPECT_TRUE(WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0);
    // Сбрасываем событие
    ResetEvent(hEvent);
    // Проверяем, что событие не поднято
    EXPECT_TRUE(WaitForSingleObject(hEvent, 0) == WAIT_TIMEOUT);
    CloseHandle(hEvent);
}