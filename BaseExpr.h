#ifndef BASE_EXPR_H
#define BASE_EXPR_H
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

const int PRECISION = 3;
/**
 * @brief BaseExpr是抽象表达式基类，定义了表达式的接口。
 * 所有的表达式都必须继承自BaseExpr，共有四类：
 * 1. 常量表达式：Constant，是double型的常数，如1, 2.3
 * 2. 变量表达式：Variable，我们仅支持单变量求导，表达式中为x
 * 3. 一元操作符表达式：Unary，是一元操作符，如sin, cos, ln
 * 4. 二元操作符表达式：Binary，是二元操作符，如+，-，*，/, ^
 * 而每一种表达式需要实现如下六种接口：
 * 1. hasVariable()，判断表达式中是否有变量，如果有返回true，否则返回false
 * 2. toString()，将表达式转换为字符串形式
 * 3. evaluate()，计算表达式的值，若表达式中的变量还没有赋值，则抛出异常；若表达式中的变量已经赋值，则返回表达式的值；evaluate(x)，计算当x=x时，表达式的值。
 * 4. getDerivative()，计算表达式的导数，返回一个新的表达式指针
 * 5. alwaysZero()，判断表达式是否永远为0，如果是，返回true，否则返回false
 * 6. clone()，深度复制(deepcopy)表达式
 */

class BaseExpr {
   public:
    virtual bool alwaysZero() const;
    virtual std::string toString() const = 0;
    virtual bool hasVariable() const = 0;
    virtual double evaluate() const = 0;
    virtual double evaluate(double x) const = 0;
    virtual int type() const = 0;
    virtual BaseExpr* getDerivative() const = 0;
    virtual ~BaseExpr() = default;
    virtual BaseExpr* clone() const = 0;
};

class Constant : public BaseExpr {
   public:
    explicit Constant(double value) : value(value) {}
    bool hasVariable() const final { return false; }
    std::string toString() const final {
        std::ostringstream oss;
        oss << std::setprecision(PRECISION) << value;
        return oss.str();
    }
    int type() const final {return 0;}
    double evaluate() const final { return value; }
    double evaluate(double x) const final { return value; }
    BaseExpr* getDerivative() const final { return new Constant(0); }
    BaseExpr* clone() const final { return new Constant(value); }

   private:
    double value;
};

class Variable : public BaseExpr {
   public:
    Variable() = default;
    bool hasVariable() const final { return true; }
    std::string toString() const final { return "x"; }
    int type() const final {return 1;}
    double evaluate() const final { throw std::runtime_error("x is not set"); }
    double evaluate(double x) const final { return x; }
    BaseExpr* getDerivative() const final { return new Constant(1); }
    BaseExpr* clone() const final { return new Variable(); }
};

#endif  // BASE_EXPR_H
