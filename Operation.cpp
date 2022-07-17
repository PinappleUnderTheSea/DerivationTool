#include "Operation.h"

#include <cmath>

#include "BinaryOP.h"
#include "UnaryOP.h"

BaseExpr* constant(double value) { return new Constant(value); }

BaseExpr* ln(BaseExpr* op){
    if(!op->hasVariable()){
        return constant(log(op->evaluate()));
    }
    return new Ln(op->clone());
}

BaseExpr* exp(BaseExpr* op){
    if(!op->hasVariable()){
        return constant(exp(op->evaluate()));
    }
    return new Exp(op->clone());
}

BaseExpr* sin(BaseExpr* op) {
    if (!op->hasVariable()) {
        return constant(sin(op->evaluate()));
    }
    return new Sin(op->clone());
}

BaseExpr* cos(BaseExpr* op) {
    if (!op->hasVariable()) {
        return constant(cos(op->evaluate()));
    }
    return new Cos(op->clone());
}

BaseExpr* tan(BaseExpr* op) {
    if (!op->hasVariable()) {
        return constant(tan(op->evaluate()));
    }
    return new Tan(op->clone());
}
BaseExpr* minus(BaseExpr* op) {
    if (!op->hasVariable()) {
        return constant(-1 * op->evaluate());
    }
    return new Minus(op->clone());
}

BaseExpr* add(BaseExpr* left, BaseExpr* right) {
    if (!left->hasVariable() && !right->hasVariable()) {
        return constant(left->evaluate() + right->evaluate());
    }
    if (!left->alwaysZero() && right->alwaysZero()) {
        return left->clone();
    }
    if (left->alwaysZero() && !right->alwaysZero()) {
        return right->clone();
    }
    return new Addition(left->clone(), right->clone());
}

BaseExpr* sub(BaseExpr* left, BaseExpr* right) {
    if (!left->hasVariable() && !right->hasVariable()) {
        return constant(left->evaluate() - right->evaluate());
    }
    if (!left->alwaysZero() && right->alwaysZero()) {
        return left->clone();
    }
    if (left->alwaysZero() && !right->alwaysZero()) {
        return minus(right->clone());
    }
    return new Subtraction(left->clone(), right->clone());
}
BaseExpr* mul(BaseExpr* left, BaseExpr* right) {
    if (!left->hasVariable() && !right->hasVariable()) {
        return constant(left->evaluate() * right->evaluate());
    }
    if (left->alwaysZero() || right->alwaysZero()) {
        return constant(0);
    }
    if (!left->hasVariable() && left->evaluate() == 1) {
        return right->clone();
    }
    if (!right->hasVariable() && right->evaluate() == 1) {
        return left->clone();
    }
    return new Multiplication(left->clone(), right->clone());
}
BaseExpr* div(BaseExpr* left, BaseExpr* right) {
    if (right->alwaysZero()) {
        throw std::runtime_error("Divided by zero error");
    }
    if (left->alwaysZero()) {
        return new Constant(0);
    }
    if (!left->hasVariable() && !right->hasVariable()) {
        return constant(left->evaluate() / right->evaluate());
    }
    return new Division(left->clone(), right->clone());
}
BaseExpr* power(BaseExpr* left, BaseExpr* right) {
    if (right->alwaysZero()) {
        return new Constant(1);
    }
    if (left->alwaysZero()) {
        return new Constant(0);
    }
    if (!left->hasVariable() && !right->hasVariable()) {
        return constant(pow(left->evaluate() , right->evaluate()));
    }
    return new Power(left->clone(), right->clone());
}
