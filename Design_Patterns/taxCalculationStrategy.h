//����������� ������������ ������ TaxCalculationStrategy, 
//������� ����� �������������� ��� ����������� ��������� ��������� ������� �������.
#pragma once
class TaxCalculationStrategy {
public:
    virtual double calculateTax(double income) = 0;
};
