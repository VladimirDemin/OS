//Тестирование работы потока Worker:

TEST(WorkerTest, ChangingArray) {
    short array_data[5] = { 5, 2, 0, 2, 4 };
    short* array = new short[5];
    for (int i = 0; i < 5; i++) {
        array[i] = array_data[i];
    }
    short** temp_array = new short* [2];
    temp_array[0] = new short[3];
    temp_array[0][0] = 5;
    temp_array[0][1] = 2;
    temp_array[0][2] = 0;
    temp_array[1] = array;

    thread t(threadWorker, temp_array, 1);
    t.join();

    // Проверяем, что массив был изменен правильно
    EXPECT_EQ(temp_array[1][0], 2);
    EXPECT_EQ(temp_array[1][1], 4);
    EXPECT_EQ(temp_array[1][2], 2);
    EXPECT_EQ(temp_array[1][3], 2);
    EXPECT_EQ(temp_array[1][4], 0);

    delete[] array;
    delete[] temp_array[0];
    delete[] temp_array[1];
    delete[] temp_array;
}
