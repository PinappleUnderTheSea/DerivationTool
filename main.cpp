#include <iostream>
#include "Expression.h"

int main() {
    auto expr = sin(5.23333 * X()) + 5 * X() * X() - cos(X()) + 1/X();
    std::cout << expr.toString() << std::endl;
    auto diff = expr.getDerivative();
    std::cout << diff.toString() << std::endl;
    std::cout << diff.evaluate(1.0) << std::endl;

    //auto expr1 = tan(exp(X()))+log(ln(X()),(5*X())^3);
    //auto expr1 = 5*X()+2*X();
    auto expr1 = X() ^ 0.0;
    std::cout << expr1.toString() << std::endl;
    auto diff1 = expr1.getDerivative();
    std::cout << diff1.toString() << std::endl;
    std::cout << diff1.evaluate(1.1) << std::endl;
}