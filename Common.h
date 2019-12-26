#pragma once

#include <memory>
#include <string>

// ������� ����� ��������������� ���������
class Expression {
public:
  virtual ~Expression() = default;

  // ��������� �������� ���������
  virtual int Evaluate() const = 0;

  // ����������� ��������� ��� ������
  // ������ ���� ������ � ������, ���������� �� ����������
  virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

// ������� ��� ������������ ���������
ExpressionPtr Value(int val);
ExpressionPtr Sum(ExpressionPtr e1, ExpressionPtr e2);
ExpressionPtr Product(ExpressionPtr e1, ExpressionPtr e2);
