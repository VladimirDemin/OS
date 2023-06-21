//Тестирование работы критической секции :

TEST(CriticalSectionTest, EnterAndLeave) {
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);
    // Входим в критическую секцию
    EnterCriticalSection(&cs);
    // Проверяем, что мы внутри критической секции
    EXPECT_TRUE(TryEnterCriticalSection(&cs) == 0);
    // Выходим из критической секции
    LeaveCriticalSection(&cs);
    // Проверяем, что мы вышли из критической секции
    EXPECT_TRUE(TryEnterCriticalSection(&cs) != 0);
    DeleteCriticalSection(&cs);
}