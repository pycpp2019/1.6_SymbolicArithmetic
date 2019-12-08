#include <string.h>
#include <memory>
#include <string>
#include <iostream>
#include "Common.h"
using namespace std;

class ClassValue: public Expression{
protected:
int value;
public:
    ClassValue(int value){
    this->value = value;
    }
    int Evaluate() const override{
    return value;
    }
    string ToString() const override{
        return('('+ to_string(value)+')');
    }
    ~ClassValue() override = default;
};


class ClassOperation: public Expression{
protected:
    ExpressionPtr left;
    ExpressionPtr right;
public:
    ClassOperation(ExpressionPtr left_, ExpressionPtr right_){
    left = move(left_);
    right = move(right_);
    };
    virtual ~ClassOperation() override = default;
    virtual int Evaluate() const override = 0;
    virtual std::string ToString() const override = 0;
};

class ClassSum: public ClassOperation{

public:
    ClassSum(ExpressionPtr left_, ExpressionPtr right_) : ClassOperation(move(left_), move(right_)) {};
    int Evaluate() const override{
    return (left->Evaluate()+right->Evaluate());
    }
    string ToString() const override{
        return('('+ (left->ToString())+'+'+(right->ToString())+')');
    }
    ~ClassSum() override = default;
};

class ClassProduct: public ClassOperation{

public:
    ClassProduct(ExpressionPtr left_, ExpressionPtr right_) : ClassOperation(move(left_), move(right_)) {};
    int Evaluate() const override{
    return (left->Evaluate()*right->Evaluate());
    }
    string ToString() const override{
        return('('+ (left->ToString())+'*'+(right->ToString())+')');
    }
    ~ClassProduct() override = default;
};

// Функции для формирования выражения

ExpressionPtr Value(int value){
unique_ptr<ClassValue> ptr (new ClassValue(value));
return ptr;
};


ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
std::unique_ptr<ClassSum> ptr (new ClassSum(move(left), move(right)));
return ptr;
};

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
std::unique_ptr<ClassProduct> ptr (new ClassProduct(move(left), move(right)));
return ptr;
};
/*int main(){
ExpressionPtr ptr = Product(Sum(Value(9),Value(9)),Product(Value(5),Sum(Value(0),Value(5))));
cout<<ptr->Evaluate()<< endl;
cout<<ptr->ToString()<< endl;
return 0;
}*/
