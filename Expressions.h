#pragma once

#include <string>
#include "Common.h"


class Number : public Expression {
private:
	int value;
public:
	~Number() override = default;

	int Evaluate() const override;

	std::string ToString() const override;

	friend ExpressionPtr Value(int value);
};


class BinaryOperation : public Expression {
protected:
	ExpressionPtr first;
	ExpressionPtr second;
public:
	virtual ~BinaryOperation() override = default;

	virtual int Evaluate() const override = 0;

	virtual std::string ToString() const override = 0;
};


class Addition : public BinaryOperation {
public:
	~Addition() override = default;

	int Evaluate() const override;

	std::string ToString() const override;

	friend ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
};


class Multiplication : public BinaryOperation {
public:
	~Multiplication() override = default;

	int Evaluate() const override;

	std::string ToString() const override;

	friend ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);
};