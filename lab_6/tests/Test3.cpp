//Тестирование работы потока CountElement:

TEST(CountElementTest, CountingElements) {
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

    thread t(threadCountElement, temp_array);
    t.join();

    // Проверяем, что количество элементов было посчитано правильно
    EXPECT_EQ(temp_array[0][2], 2);

    delete[] array;
    delete[] temp_array[0];
    delete[] temp_array[1];
    delete[] temp_array;
}
