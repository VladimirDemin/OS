//������������ ������ ������� :

TEST(EventTest, SetAndReset) {
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    // ���������, ��� ������� �� �������
    EXPECT_TRUE(WaitForSingleObject(hEvent, 0) == WAIT_TIMEOUT);
    // ��������� �������
    SetEvent(hEvent);
    // ���������, ��� ������� �������
    EXPECT_TRUE(WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0);
    // ���������� �������
    ResetEvent(hEvent);
    // ���������, ��� ������� �� �������
    EXPECT_TRUE(WaitForSingleObject(hEvent, 0) == WAIT_TIMEOUT);
    CloseHandle(hEvent);
}