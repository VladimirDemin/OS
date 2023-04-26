//����������� ������ Settings, ������� ����� �������������� ��� ���������
//� ��������� ��������� ��������� ������� �������.
#pragma once
#include "taxCalculationStrategy.h"
class Settings {
private:
    static Settings* instance;
    TaxCalculationStrategy* strategy;
    Settings();
public:
    static Settings* getInstance();
    void setStrategy(TaxCalculationStrategy* strategy);
    TaxCalculationStrategy* getStrategy();
};