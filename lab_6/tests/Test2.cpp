//Тестирование работы условной переменной:

TEST(ConditionVariableTest, WaitAndNotify) {
    mutex mtx;
    condition_variable_any cv;
    bool flag = false;

    thread t([&]() {
        unique_lock<mutex> lock(mtx);
        // Задержка потока на 1 секунду
        this_thread::sleep_for(chrono::seconds(1));
        flag = true;
        // Уведомление ожидающего потока
        cv.notify_one();
    });

    unique_lock<mutex> lock(mtx);
    // Ожидание уведомления от другого потока
    cv.wait(lock, [&]() {return flag; });
    // Проверяем, что флаг установлен в true
    EXPECT_TRUE(flag == true);
    t.join();
}
