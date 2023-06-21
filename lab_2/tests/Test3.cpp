//Тестирование чтения чисел из буфера и вывода на экран в Reader :

TEST(ReaderTest, BufferReadingAndOutput) {
    Reader reader;
    std::vector<int> buffer = { 1, 2, 3 };
    std::mutex mutex;
    std::condition_variable cv;

    // Читаем число из буфера и выводим на экран
    reader.readFromBuffer(buffer, mutex, cv);
    // Проверяем, что число было прочитано и выведено на экран
    EXPECT_EQ(reader.getLastReadNumber(), 1);
}