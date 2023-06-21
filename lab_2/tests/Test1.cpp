//Тестирование генерации случайных чисел в Writer :

TEST(WriterTest, RandomNumberGeneration) {
    Writer writer;
    int num1 = writer.generateRandomNumber();
    int num2 = writer.generateRandomNumber();
    EXPECT_NE(num1, num2);
}
