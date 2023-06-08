## 基于Qt计算器程序设计

- **编译器**
  - VS2019

- **基本框架**

该计算器包含两个功能，标准计算器和进制计算器，使用Menu控件切换。标准计算器和进制计算器分别为不同的widget，使用QStackedWidget控件封装。最后使用信号与槽实现widget切换。

- **标准计算器实现**

<img src="/images/标准模式.png" style="zoom:50%;" />

1.通过按钮输入需要计算的表达式，存储为QString类型

2.将QString类型的表达式分割为数组，即运算符、括号和数字分离

3.表达式数组为中缀表达式，改为逆波兰表达式，即后缀表达式

4.对逆波兰表达式进行计算，

5.得到运算结果

- **进制计算器实现**

<img src="/images/进制模式.png" style="zoom:50%;" />

1.根据按钮切换需要输入的进制数

2.将当前输入进制数改为十进制

3.将十进制数通过除数取余来得到其他进制数

4.得到运算结果
