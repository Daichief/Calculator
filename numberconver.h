#ifndef __NUMBERCONVER_H__
#define __NUMBERCONVER_H__


#include <QWidget>
#include "ui_numberconver.h"
#include<QMap>
#include<QDebug>
#include<QMessageBox>


class NumberConver : public QWidget
{
	Q_OBJECT

public:
	NumberConver(QWidget *parent = Q_NULLPTR);
	~NumberConver();
	void initUi();

public slots:
	void onButtonGroupClicked(QAbstractButton* btn);

	void error(const QString& str);

	void handelNumber()const;

	void addNumber(const QString& str);

private:
	Ui::NumberConver ui;
	QString m_type = "DEC";   //��ǰ��������
	QString m_number;         //��Ҫת������
};

#endif // !__NUMBERCONVER_H__
