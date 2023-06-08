#ifndef __NORMALCALCULATOR_H__
#define __NORMALCALCULATOR_H__


#include <QWidget>
#include "ui_normalcalculator.h"

class NormalCalculator : public QWidget
{
	Q_OBJECT
public:

	void initUi();

    bool bracketEqual() const;                 //判断括号匹配

    bool isOperator(const QString& str) const; //判断是否是运算符

    bool isNumber(const QString& str) const;   //判断是否是数字

    double expressionHandle();                 //计算表达式数组

    void error(const QString& str);            //错误提示

    void addStr(QString str);                  //向表达式添加字符

    void getExpVec();                          //将字符串表达式处理为数组

public slots:
    void onButtonGroupClicked(QAbstractButton* btn);

public:
	NormalCalculator(QWidget *parent = Q_NULLPTR);
	~NormalCalculator();

private:
	Ui::NormalCalculator ui;

    QVector<QString> m_expression;

    QString m_lineEditExp;
};

#endif // !__NORMALCALCULATOR_H__
