//����������� ������ FlatTaxStrategy, ������� ��������� ��������� ������� �������
// � ������������� �������.
#pragma once
#include "taxCalculationStrategy.h"

class FlatTaxStrategy : public TaxCalculationStrategy {
public:
    double calculateTax(double income);
};
