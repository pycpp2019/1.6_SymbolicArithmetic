#include <string>
#include "Expressions.h"
#include "Common.h"


int Number::Evaluate() const {
	return this->value;
}

std::string Number::ToString() const {
	return "(" + std::to_string(this->value) + ")";
}

int Addition::Evaluate() const {
	return this->first->Evaluate() + this->second->Evaluate();
}

std::string Addition::ToString() const {
	return "(" + this->first->ToString() + "+" + this->second->ToString() + ")";
}

int Multiplication::Evaluate() const {
	return this->first->Evaluate() * this->second->Evaluate();
}

std::string Multiplication::ToString() const {
	return "(" + this->first->ToString() + "*" + this->second->ToString() + ")";
}