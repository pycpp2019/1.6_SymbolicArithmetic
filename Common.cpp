#include "Common.h"

class ValueExp : public Expression{
public:
	ValueExp(int n): val(n){}
	int Evaluate() const override {
		return val;
	}
	std::string ToString() const override {
		return std::string("(")+std::to_string(val)+std::string(")");
	}
private:
	int val;
};

class SumExp : public Expression{
public:
	SumExp(ExpressionPtr e1, ExpressionPtr e2): e1(move(e1)),e2(move(e2)){}
	int Evaluate() const override {
		return e1->Evaluate()+e2->Evaluate();
	}
	std::string ToString() const override {
		return std::string("(")+e1->ToString()+std::string("+")+e2->ToString()+std::string(")");
	}
private:
	ExpressionPtr e1,e2;
};

class ProdExp : public Expression{
public:
	ProdExp(ExpressionPtr e1, ExpressionPtr e2): e1(move(e1)),e2(move(e2)){}
	int Evaluate() const override {
		return e1->Evaluate()*e2->Evaluate();
	}
	std::string ToString() const override {
		return std::string("(")+e1->ToString()+std::string("*")+e2->ToString()+std::string(")");
	}
private:
	ExpressionPtr e1,e2;
};

ExpressionPtr Value(int val){
	return std::make_unique<ValueExp>(val);
}

ExpressionPtr Sum(ExpressionPtr e1, ExpressionPtr e2){
	return std::make_unique<SumExp>(std::move(e1), std::move(e2));
}

ExpressionPtr Product(ExpressionPtr e1, ExpressionPtr e2){
	return std::make_unique<ProdExp>(std::move(e1), std::move(e2));
}

