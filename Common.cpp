#include "Common.h"
#include <memory>

class Number : public Expression
{
    private:
    int value;
    public:
    ~Number() override = default;
    int Evaluate() const override
    {
        return this->value;
    }
    std::string ToString() const override
    {
        return "(" + std::to_string(this->value) + ")";
    }
    friend ExpressionPtr Value(int value);

};
class Add : public Expression
{
    private:
    ExpressionPtr x1;
	ExpressionPtr x2;
     public:
    ~Add() override = default;
    int Evaluate() const override
    {
        return this->x1->Evaluate()+this->x2->Evaluate();
    }
    std::string ToString() const override
    {
        return "("+this->x1->ToString()+"+"+this->x2->ToString()+")";
    }
    friend ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);

};
class Mul : public Expression
{
    private:
    ExpressionPtr x1;
	ExpressionPtr x2;
     public:
    ~Mul() override = default;
    int Evaluate() const override
    {
        return this->x1->Evaluate()*this->x2->Evaluate();
    }
    std::string ToString() const override
    {
        return "("+this->x1->ToString()+"*"+this->x2->ToString()+")";
    }
    friend ExpressionPtr Product(ExpressionPtr x1, ExpressionPtr x2);

};

ExpressionPtr Value(int value)
{
    std::unique_ptr<Number> N = std::make_unique<Number>();
    N->value = value;
    return N;

}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right)
{
    std::unique_ptr<Add> A = std::make_unique<Add>();
    A->x1 = std::move(left);
    A->x2 = std::move(right);
    return A;
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right)
{
    std::unique_ptr<Mul> M = std::make_unique<Mul>();
    M->x1 = std::move(left);
    M->x2 = std::move(right);
    return M;
}
