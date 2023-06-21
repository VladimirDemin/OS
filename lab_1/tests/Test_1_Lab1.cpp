TEST_CLASS(MainTest)
{
public:
    TEST_METHOD(ArrayTest)
    {
        // ������������� stdout
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        // ������ ������ � �������
        std::istringstream input("5\n1\n2\n3\n4\n5\n5\n");
        std::cin.rdbuf(input.rdbuf());

        // ��������� �������
        int result = main();

        // ��������� �����
        std::string output = buffer.str();
        Assert::AreEqual(output, "Enter the size of array: Enter the element of the array: Enter the element of the array: Enter the element of the array: Enter the element of the array: Enter the element of the array: Array: 1 2 3 4 5 \nMax element in array is 5\nEnter time you want to stop the thread:");

        // ��������� ��������� ���������� �������
        Assert::AreEqual(result, 0);
    }
};