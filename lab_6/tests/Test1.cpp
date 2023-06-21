//Тестирование работы мьютекса:

TEST(MutexTest, LockAndUnlock) {
    mutex mtx;
    // Блокируем мьютекс
    mtx.lock();
    // Проверяем, что другой поток не может заблокировать мьютекс
    EXPECT_TRUE(mtx.try_lock() == false);
    // Разблокируем мьютекс
    mtx.unlock();
    // Проверяем, что мьютекс разблокирован
    EXPECT_TRUE(mtx.try_lock() == true);
}
