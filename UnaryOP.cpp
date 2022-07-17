#include "UnaryOP.h"

#include <cmath>

#include "BinaryOP.h"

BaseExpr* UnaryOP::getDerivative() const {
    return mul(operand->getDerivative(), getDerivativeOuter());
}

std::string Sin::toString() const {
    return "sin(" + operand->toString() + ")";
}
double Sin::evaluate() const { return sin(operand->evaluate()); }
double Sin::evaluate(double x) const { return sin(operand->evaluate(x)); }
BaseExpr* Sin::getDerivativeOuter() const { return cos(operand); }
BaseExpr* Sin::clone() const { return new Sin(operand->clone()); }

std::string Cos::toString() const {
    return "cos(" + operand->toString() + ")";
}
double Cos::evaluate() const { return cos(operand->evaluate()); }
double Cos::evaluate(double x) const { return cos(operand->evaluate(x)); }
BaseExpr* Cos::getDerivativeOuter() const { return minus(sin(operand)); }
BaseExpr* Cos::clone() const { return new Cos(operand->clone()); }

double Minus::evaluate() const { return -1 * operand->evaluate(); }
double Minus::evaluate(double x) const { return -1 * operand->evaluate(x); }
std::string Minus::toString() const {
    return "(-" + operand->toString() + ")";
}
BaseExpr* Minus::getDerivativeOuter() const { return new Constant(-1); }
BaseExpr* Minus::clone() const { return new Minus(operand->clone()); }

double Tan::evaluate() const { return tan(operand->evaluate());}
double Tan::evaluate(double x) const { return tan(operand->evaluate(x));}
BaseExpr* Tan::getDerivativeOuter() const { return div(new Constant(1),power(cos(operand),new Constant(2)));}
BaseExpr* Tan::clone() const { return new Tan(operand->clone());}
std::string Tan::toString() const {
    return "tan(" + operand->toString() + ")";
}

double Exp::evaluate() const {return exp(operand->evaluate());}
double Exp::evaluate(double x) const { return exp(operand->evaluate(x));}
BaseExpr* Exp::getDerivativeOuter() const { return exp(operand);}
BaseExpr* Exp::clone() const { return new Exp(operand->clone());}
std::string Exp::toString() const{
    return "exp(" + operand->toString() + ")";
}

double Ln::evaluate() const {return log(operand->evaluate());}
double Ln::evaluate(double x) const { return log(operand->evaluate(x));}
BaseExpr* Ln::getDerivativeOuter() const { return div(new Constant(1), operand);}
BaseExpr* Ln::clone() const { return new Ln(operand->clone());}
std::string Ln::toString() const {
    return "ln(" + operand->toString() + ")";
}