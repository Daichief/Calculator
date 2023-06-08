#ifndef __NORMALCALCULATOR_H__
#define __NORMALCALCULATOR_H__


#include <QWidget>
#include "ui_normalcalculator.h"

class NormalCalculator : public QWidget
{
	Q_OBJECT
public:

	void initUi();

    bool bracketEqual() const;                 //�ж�����ƥ��

    bool isOperator(const QString& str) const; //�ж��Ƿ��������

    bool isNumber(const QString& str) const;   //�ж��Ƿ�������

    double expressionHandle();                 //������ʽ����

    void error(const QString& str);            //������ʾ

    void addStr(QString str);                  //����ʽ����ַ�

    void getExpVec();                          //���ַ������ʽ����Ϊ����

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
