#include <sstream>

#include <string>
#include <memory>

#include "Common.h"


class ValueExpr : public Expression {
public:
    int value;
    ValueExpr(int v) : value(v) {}
    virtual int Evaluate() const {
        return this->value;
    }
    virtual std::string ToString() const {
        std::stringstream ss;
        ss << "(" << this->value << ")";
        return ss.str();
    }
};

class SumExpr : public Expression {
public:
    ExpressionPtr left, right;
    SumExpr(ExpressionPtr l, ExpressionPtr r) : left(std::move(l)), right(std::move(r)) {}
    virtual int Evaluate() const {
        return this->left->Evaluate() + this->right->Evaluate();
    }
    virtual std::string ToString() const {
        std::stringstream ss;
        ss << "(" << this->left->ToString() << "+" << this->right->ToString() << ")";
        return ss.str();
    }
};

class ProductExpr : public Expression {
public:
    ExpressionPtr left, right;
    ProductExpr(ExpressionPtr l, ExpressionPtr r) : left(std::move(l)), right(std::move(r)) {}
    virtual int Evaluate() const {
        return this->left->Evaluate()*this->right->Evaluate();
    }
    virtual std::string ToString() const {
        std::stringstream ss;
        ss << "(" << this->left->ToString() << "*" << this->right->ToString() << ")";
        return ss.str();
    }
};

ExpressionPtr Value(int value) {
    return std::unique_ptr<Expression>(new ValueExpr(value));
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return std::unique_ptr<Expression>(new SumExpr(std::move(left), std::move(right)));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return std::unique_ptr<Expression>(new ProductExpr(std::move(left), std::move(right)));
}
