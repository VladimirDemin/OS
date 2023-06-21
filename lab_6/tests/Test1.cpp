//������������ ������ ����������� ������ :

TEST(CriticalSectionTest, EnterAndLeave) {
    CRITICAL_SECTION cs;
    InitializeCriticalSection(&cs);
    // ������ � ����������� ������
    EnterCriticalSection(&cs);
    // ���������, ��� �� ������ ����������� ������
    EXPECT_TRUE(TryEnterCriticalSection(&cs) == 0);
    // ������� �� ����������� ������
    LeaveCriticalSection(&cs);
    // ���������, ��� �� ����� �� ����������� ������
    EXPECT_TRUE(TryEnterCriticalSection(&cs) != 0);
    DeleteCriticalSection(&cs);
}