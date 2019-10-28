#include <memory>
#include "Common.h"
#include "Expressions.h"


ExpressionPtr Value(int value) {
	std::unique_ptr<Number> val_ptr(new Number);
	val_ptr->value = value;
	return val_ptr;
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
	std::unique_ptr<Addition> add_op(new Addition);
	add_op->first.reset(left.release());
	add_op->second.reset(right.release());
	return add_op;
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
	std::unique_ptr<Multiplication> mul_op(new Multiplication);
	mul_op->first.reset(left.release());
	mul_op->second.reset(right.release());
	return mul_op;
}