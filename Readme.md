# Readme

##### 运行方式

```cmake
g++ ./main.cpp ./BaseExpr.cpp ./BinaryOP.cpp ./Expression.cpp ./Operation.cpp ./UnaryOP.cpp -o main

./main
```

##### 修改了BaseExpr与Constant, Unary, Binary

新增接口 

```c++
int type() const 
```

返回值对应类型：

0: Constant; 1: Variable; 2: Unary; 3:Binary

##### Unary中新增继承类

tan: 表示三角函数tan，求导为1/(cos()^2);

ln  :表示以e为底数的对数函数，求导为1/x;

exp:表示指数函数e^(x), 求导为exp(X);

其他函数如evaluate与已给出的函数类似

##### Binary中新增继承类

pow(x,n):表示指数函数x^n, 求导为n*x^(n-1);

log(x,y):表示以为y底数,x的对数，其值等于ln(x)/ln(y)，求导方式为除法Division(ln(x),ln(y)）的导数；

##### 新增Operation

新增：tan, exp, ln，分别生成对应计算方式的类，函数构造与sin等类似；

新增power, 生成power类型的对象，构造方式与其他二元运算类似

##### 在Expression中新增函数

新增tan, ln ,exp,返回对应类型的Expression类型的表达式类

新增log，^两个二元运算符，分别生成ln(x)/ln(y)，x^n两个类型的表达式类

并同时把上述函数添加为Expression的friend；

##### 一些其他改动

在+, -, *, / 中分别判断其中一个值为常数且为1或0的时候简化输出

判断二元运算符左右两边均为常数时计算出结果而非得出表达式

##### 测试

```c++
auto expr1 = tan(exp(X()))+log(ln(X()),(5*X())^3);
```

利用expr1进行测试，得到的结果与计算器输出一致