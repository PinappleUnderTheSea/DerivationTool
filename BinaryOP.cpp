#include "UnaryOP.h"
#include "BinaryOP.h"
#include "Operation.h"
#include <cmath>
double Addition::evaluate() const {
    return left->evaluate() + right->evaluate();
}

double Addition::evaluate(double x) const {
    return left->evaluate(x) + right->evaluate(x);
}

BaseExpr *Addition::getDerivative() const {
    return add(left->getDerivative(), right->getDerivative());
}

std::string Addition::toString() const {
    if(left->type()==0&&left->evaluate()==0){
        return right->toString();
    }
    else if(right->type()==0&&right->evaluate()==0){
        return left->toString();
    }
    else if(left->type()==0&&right->type()==0){
        return (new Constant(left->evaluate()+right->evaluate()))->toString();
    }
    return "("+left->toString()+"+"+right->toString()+")";
}
BaseExpr *Addition::clone() const {
    return new Addition(left->clone(), right->clone());
}

double Subtraction::evaluate() const {
    return left->evaluate() - right->evaluate();
}

double Subtraction::evaluate(double x) const {
    return left->evaluate(x) - right->evaluate(x);
}

BaseExpr *Subtraction::getDerivative() const {
    return sub(left->getDerivative(),right->getDerivative());
}

std::string Subtraction::toString() const {
    if(right->type()==0&&right->evaluate()==0){
        return left->toString();
    }
    else if(left->type()==0&&left->evaluate()==0){
        return "(-" + right->toString() + ")";
    }
    else if(left->type()==0&&right->type()==0){
        return (new Constant(left->evaluate()-right->evaluate()))->toString();
    }    
    return "("+left->toString()+"-"+right->toString()+")";
}
BaseExpr *Subtraction::clone() const {
    return new Subtraction(left->clone(), right->clone());
}

double Multiplication::evaluate() const {
    return left->evaluate() * right->evaluate();
}

double Multiplication::evaluate(double x) const {
    return left->evaluate(x) * right->evaluate(x);
}

BaseExpr *Multiplication::getDerivative() const {
    auto l = mul(left->getDerivative(),right);
    auto r = mul(left,right->getDerivative());
    return add(l,r);
}

std::string Multiplication::toString() const {
    if(left->type()==0&&left->evaluate()==1){
        return right->toString();
    }
    else if(right->type()==0&&right->evaluate()==1){
        return left->toString();
    }
    else if(right->type()==0&&right->evaluate()==0){
        return (new Constant(0))->toString();
    }
    else if(left->type()==0&&left->evaluate()==0){
        return (new Constant(0))->toString();
    }
    else if(left->type()==0&&right->type()==0){
        return (new Constant(left->evaluate()*right->evaluate()))->toString();
    }
    return "("+left->toString()+"*"+right->toString()+")";
}

BaseExpr *Multiplication::clone() const {
    return new Multiplication(left->clone(), right->clone());
}

double Division::evaluate() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    return left->evaluate() / right->evaluate();
}

double Division::evaluate(double x) const {
    if(right->evaluate(x) == 0){
        throw std::runtime_error("Divided by zero error");
    }
    return left->evaluate(x) / right->evaluate(x);
}

BaseExpr *Division::getDerivative() const {
    auto numerator = new Subtraction(new Multiplication(left->getDerivative(),right), new Multiplication(left, right->getDerivative()));
    auto denominator = new Multiplication(right,right);
    return div(numerator, denominator);
}

std::string Division::toString() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    else if(right->type()==0&&right->evaluate()==1){
        return left->toString();
    }
    else if(left->type()==0&&left->evaluate()==0){
        return (new Constant(0))->toString();
    }
    else if(left->type()==0&&right->type()==0){
        return (new Constant(left->evaluate()/right->evaluate()))->toString();
    }

    return "("+left->toString()+"/"+right->toString()+")";
}

BaseExpr *Division::clone() const {
    return new Division(left->clone(), right->clone());
}

double Power::evaluate() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    return pow(left->evaluate() , right->evaluate());
}

double Power::evaluate(double x) const {
    if(right->evaluate(x) == 0){
        throw std::runtime_error("Divided by zero error");
    }
    return pow(left->evaluate(x) , right->evaluate(x));
}

BaseExpr *Power::getDerivative() const {

    return mul(mul(new Constant(right->evaluate()), new Power(left,new Constant(right->evaluate()-1))),left->getDerivative());
}

std::string Power::toString() const {
    if(left->type()==0&&right->type()==0){
        return (new Constant(pow(left->evaluate(),right->evaluate())))->toString();
    }
    else if(left->type()==0&&left->evaluate()==0){
        return (new Constant(0))->toString();
    }
    else if(right->type()==0&&right->evaluate()==0){
        return (new Constant(1))->toString();
    }
    return "("+left->toString()+"^"+right->toString()+")";
}

BaseExpr *Power::clone() const {
    return new Power(left->clone(), right->clone());
}

double Log::evaluate() const {
    if(right->alwaysZero()){
        throw std::runtime_error("Divided by zero error");
    }
    return log(left->evaluate())/log(right->evaluate());
}

double Log::evaluate(double x) const {
    if(right->evaluate(x) == 0){
        throw std::runtime_error("Divided by zero error");
    }
    return log(left->evaluate(x)) / log(right->evaluate(x));
}

BaseExpr *Log::getDerivative() const {

    return (div(new Ln(left), new Ln(right)))->getDerivative();
}

std::string Log::toString() const {

    return "log("+left->toString()+","+right->toString()+")";
}

BaseExpr *Log::clone() const {
    return new Log(left->clone(), right->clone());
}