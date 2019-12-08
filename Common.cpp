#include <string.h>
#include <memory>
#include <string>
#include <iostream>
#include "Common.h"
using namespace std;
/*

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
};*/

/*
int main(){

ExpressionPtr ptr = Product(Sum(Value(9),Value(9)),Product(Value(5),Sum(Value(0),Value(5))));
cout<<ptr->Evaluate()<< endl;
cout<<ptr->ToString()<< endl;
return 0;
}*/
