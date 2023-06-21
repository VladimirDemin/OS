//Тестирование записи чисел в буфер и оповещения Reader в Writer :

TEST(WriterTest, BufferWritingAndNotification) {
    Writer writer;
    Reader reader;
    std::vector<int> buffer;
    std::mutex mutex;
    std::condition_variable cv;

    // Записываем число в буфер и оповещаем Reader
    writer.writeToBuffer(buffer, 5, mutex, cv);
    // Ожидаем, пока Reader прочитает число
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock);
    // Проверяем, что буфер пуст и Reader прочитал число
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(reader.getLastReadNumber(), 5);
}
