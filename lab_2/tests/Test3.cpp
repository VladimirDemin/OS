//������������ ������ ����� �� ������ � ������ �� ����� � Reader :

TEST(ReaderTest, BufferReadingAndOutput) {
    Reader reader;
    std::vector<int> buffer = { 1, 2, 3 };
    std::mutex mutex;
    std::condition_variable cv;

    // ������ ����� �� ������ � ������� �� �����
    reader.readFromBuffer(buffer, mutex, cv);
    // ���������, ��� ����� ���� ��������� � �������� �� �����
    EXPECT_EQ(reader.getLastReadNumber(), 1);
}