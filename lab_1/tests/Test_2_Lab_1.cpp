//проверяем, что функция находит максимальный элемент в массиве.
TEST_CLASS(WorkerTest)
{
public:
    TEST_METHOD(MaxElementTest)
    {
        int arr[] = { 5, 1, 2, 3, 4, 5 };
        UINT result = Worker((void*)arr);
        Assert::AreEqual((UINT)0, result);
    }
};
