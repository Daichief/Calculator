#include "numberconver.h"

NumberConver::NumberConver(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUi();


}

NumberConver::~NumberConver()
{
}

void NumberConver::initUi()
{
	QWidget::setWindowFlags(Qt::FramelessWindowHint);
	//1.构建按钮组
	QButtonGroup* buttonGroup = new QButtonGroup(this);
	QList<QPushButton*> btnList = findChildren<QPushButton*>();
	for (auto btn : btnList)
	{
		buttonGroup->addButton(btn);
	}
	//2.关联按钮组的点击信号
	connect(buttonGroup, static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked),
		this, &NumberConver::onButtonGroupClicked);
}


void NumberConver::onButtonGroupClicked(QAbstractButton* btn)
{
	QString btnStr = btn->text();
	QMap<int, QPushButton*> btnMap = { {0,ui.btn_0},{1,ui.btn_1},{2,ui.btn_2},{3,ui.btn_3},{4,ui.btn_4},{5,ui.btn_5},
		{6,ui.btn_6},{7,ui.btn_7}, {8,ui.btn_8}, {9,ui.btn_9}, {10,ui.btn_A}, {11,ui.btn_B}, {12,ui.btn_C}, {13,ui.btn_D}, 
		{14,ui.btn_E}, {15,ui.btn_F} };
	qDebug() << btnStr;
	if (btnStr == "HEX" || btnStr == "DEC" || btnStr == "QCT" || btnStr == "BIN")
	{
		QMap<QString, int> map = { {"HEX",16},{"DEC",10},{"QCT",8},{"BIN",2} };
		m_number.clear();
		ui.lineEdit_input->clear();
		m_type = btnStr;
		for (int i = 0; i < 16; i++)
		{
			if (i >= 0 && i < map[btnStr])
				btnMap[i]->setEnabled(true);
			else
				btnMap[i]->setEnabled(false);
		}
	}
	else if (btnStr == "=")
	{
		if (ui.lineEdit_input->text().isEmpty())
			error("The input field is empty!");
		else
			handelNumber();
	}
	else if (btnStr == "del")
	{
		m_number.remove(m_number.length() - 1, 1);
		ui.lineEdit_input->setText(m_number);
	}
	else if (btnStr == "clear")
	{
		m_number.clear();
		ui.lineEdit_input->clear();
		ui.lineEdit_bin->clear();
		ui.lineEdit_dec->clear();
		ui.lineEdit_hex->clear();
		ui.lineEdit_qct->clear();
	}
	else
	{
		addNumber(btnStr);
		ui.lineEdit_input->setText(m_number);
	}

}


void NumberConver::error(const QString& str)
{
	QMessageBox::question(this, "warning", str, QMessageBox::Yes);
}

void NumberConver::handelNumber() const
{
	int number = 0;
	int length = m_number.length();
	QMap<QString, int> numberMap = { {"A",10},{"B",11},{"C",12}, {"D",13}, {"E",14} ,{"F",15},
		 {"0",0},{"1",1},{"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},{"9",9}};
	QMap<QString, int> typeMap = { {"HEX",16},{"DEC",10},{"QCT",8},{"BIN",2} };
	for (int i = 0;i < length;i++)
	{
		number += numberMap[m_number[i]] * pow(typeMap[m_type], length - 1 - i);
	}
	ui.lineEdit_dec->setText(QString::number(number));

	//将十进制数转换为其他进制
	QVector<QString> result = {"","",""};
	int index = 0;
	for (auto val : { 2,8,16 })
	{
		int tempNumber = number;
		do
		{
			int temp = tempNumber % val;
			result[index].prepend(numberMap.key(temp));
			//result[index].append(numberMap.key(temp));

			tempNumber /= val;
		} while (tempNumber != 0);
		index++;
	}
	for (auto val : result)
	{
		qDebug() << "res:" << val;
	}
	ui.lineEdit_hex->setText(result[2]);
	ui.lineEdit_qct->setText(result[1]);
	ui.lineEdit_bin->setText(result[0]);


}

void NumberConver::addNumber(const QString& str)
{
	
	if (m_number.length() == 1 && m_number == "0")
		m_number[0] = str[0];
	else
		m_number.append(str);
	qDebug() << m_number;
}