// ����������� ������ ProgressiveTaxStrategy, ������� ���������
// ������������� ��������� ������� �������.
#pragma once
#include "taxCalculationStrategy.h"

class ProgressiveTaxStrategy : public TaxCalculationStrategy {
public:
    double calculateTax(double income);
};