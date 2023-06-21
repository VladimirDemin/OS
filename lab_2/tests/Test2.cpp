//������������ ������ ����� � ����� � ���������� Reader � Writer :

TEST(WriterTest, BufferWritingAndNotification) {
    Writer writer;
    Reader reader;
    std::vector<int> buffer;
    std::mutex mutex;
    std::condition_variable cv;

    // ���������� ����� � ����� � ��������� Reader
    writer.writeToBuffer(buffer, 5, mutex, cv);
    // �������, ���� Reader ��������� �����
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock);
    // ���������, ��� ����� ���� � Reader �������� �����
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(reader.getLastReadNumber(), 5);
}