#pragma once
#include <string.h>
#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
public:
  virtual ~Expression() = default;

  // Вычисляет значение выражения
  virtual int Evaluate() const = 0;

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

class ClassValue:: public Expression{
int value;
public:
    ClassValue(int value){
    this->value;
    }
    int Evaluate() const override{
    return value;
    }
    string ToString() const override{
        return('('+ to_string(value)+')');
    }
};


class ClassOperation::public Expression{
ExpressionPtr left;
ExpressionPtr right;

};

class ClassSum::public Operation{

public:
    int Valuate() const override{
    return (left.Evaluate()+right.Evaluate());
    }
    string ToString() const override{
        return('('+ (left->ToSrting())+'+'+(right->ToString())+')');
    }

};

class ClassProduct::public Operation{

public:
    int Valuate() const override{
    return (left.Evaluate()*right.Evaluate());
    }
    string ToString() const override{
        return('('+ (left->ToSrting())+'*'+(right->ToString())+')');
    }

};

// Функции для формирования выражения

ExpressionPtr Value(int value){
ExpressionPtr ptr = make_unique(new ClassValue(value));
return ptr;
};


ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
ExpressionPtr ptr = make_unique(new ClassOperation);
return ptr;
};

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
ExpressionPtr ptr = make_unique(new ClassOPeration);
return ptr;
};
