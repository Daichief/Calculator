#include "normalcalculator.h"
#include<QPushButton>
#include<QButtonGroup>
#include<QList>
#include<QDebug>
#include<QStack>
#include<QMap>
#include<QMessageBox>

NormalCalculator::NormalCalculator(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initUi();
}

NormalCalculator::~NormalCalculator()
{
}

void NormalCalculator::initUi()
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
        this, &NormalCalculator::onButtonGroupClicked);

}

void NormalCalculator::onButtonGroupClicked(QAbstractButton* btn)
{
    ui.lineEdit_2->clear();
    QString btnStr = btn->text();
    qDebug() << btnStr;
    //=
    if (btnStr == "=")
    {
        //表达式为空
        if (m_lineEditExp.isEmpty())
        {
            ui.lineEdit->setText("");
        }
        //括号匹配，且不是操作符
        else if (bracketEqual() && !isOperator((QString)m_lineEditExp[m_lineEditExp.length() - 1]))
        {
            ui.lineEdit_2->setText(m_lineEditExp + "=");
            getExpVec();
            double temp = expressionHandle();
            m_expression.clear();
            m_lineEditExp.clear();
            ui.lineEdit->setText(QString::number(temp));
        }
        else
        {
            error("The expression is wrong!");
        }
    }
    //del
    else if (btnStr == "del")
    {
        m_lineEditExp.remove(m_lineEditExp.length() - 1, 1);
        ui.lineEdit->setText(m_lineEditExp);
    }
    //C
    else if (btnStr == "C")
    {
        m_lineEditExp.clear();
        m_expression.clear();
        ui.lineEdit->setText(m_lineEditExp);
    }
    // 1/x 
    else if (btnStr == "1/x")
    {
        if (!m_lineEditExp.isEmpty() && isNumber(m_lineEditExp))
        {
            double temp = m_lineEditExp.toDouble();
            if (temp != 0.0)
            {
                ui.lineEdit->setText(QString::number(1 / temp));
                ui.lineEdit_2->setText("1/" + QString::number(temp) + "=");
            }

            else
                error("The divisor cannot be 0!");
        }
        else
            error("The expression is wrong!");
        m_lineEditExp.clear();
    }
    //X^2
    else if (btnStr == "X^2")
    {
        if (!m_lineEditExp.isEmpty() && isNumber(m_lineEditExp))
        {
            double temp = m_lineEditExp.toDouble();
            ui.lineEdit->setText(QString::number(temp * temp));
            ui.lineEdit_2->setText(QString::number(temp) + "^2" + "=");
        }
        else
            error("The expression is wrong!");
        m_lineEditExp.clear();
    }
    //X^0.5
    else if (btnStr == "X^0.5")
    {
        if (!m_lineEditExp.isEmpty() && isNumber(m_lineEditExp))
        {
            double temp = m_lineEditExp.toDouble();
            if (temp >= 0.0)
            {
                ui.lineEdit->setText(QString::number(sqrt(temp)));
                ui.lineEdit_2->setText(QString::fromLocal8Bit("√") + QString::number(temp) + "=");
            }
            else
                error("The root needs to be greater than or equal to 0!");
        }
        else
            error("The expression is wrong!");
        m_lineEditExp.clear();
    }
    //() % ÷ × + -  +/_  . 0-9
    else
    {
        addStr(btnStr);
        ui.lineEdit->setText(m_lineEditExp);
    }



}

void NormalCalculator::addStr(QString btnStr)
{
    int length = m_lineEditExp.length();
    QString lastStr = "";
    QString nextLastStr = "";
    if (length > 0)
        lastStr = (QString)m_lineEditExp[length - 1];   //表达式最后一个元素
    if (length > 1)
        nextLastStr = (QString)m_lineEditExp[length - 2];    //表达式倒数第二个元素
    //0-9
    if (isNumber(btnStr))
    {
        //表达式字符串为空
        if (m_lineEditExp.isEmpty())
            m_lineEditExp.append(btnStr);
        //表达式字符串以0结尾，替换0
        else if (m_lineEditExp.endsWith('0'))
            if (length == 1)
                m_lineEditExp[0] = btnStr[0];
            else if (isOperator(nextLastStr) || nextLastStr == "(")
                m_lineEditExp[length - 1] = btnStr[0];
            else
                m_lineEditExp.append(btnStr);

        //表达式最后为）不追加数字
        else if (lastStr == ")") {}
        else
            m_lineEditExp.append(btnStr);
    }
    //"()"
    else if (btnStr == "( )")
    {
        if (m_lineEditExp.isEmpty())
        {
            m_lineEditExp.append("(");
        }
        //如果最后一个是运算符或（，添加"("
        else if (isOperator(lastStr) || lastStr == "(")
        {
            m_lineEditExp.append("(");
        }
        //最后一位是数字或），添加")"
        else if (isNumber(lastStr) || lastStr == ")")
        {
            if (!bracketEqual())
                m_lineEditExp.append(")");
        }
    }
    //"."
    else if (btnStr == ".")
    {
        if (length > 0 && isNumber(lastStr))
        {
            int i = length - 2;
            for (; i >= 0; i--)    //寻找小数点，看最后一个数字是不是已经是小数
            {
                if (isOperator((QString)m_lineEditExp[i]))
                    break;
                if (m_lineEditExp[i] == '.')
                    break;
            }
            if (m_lineEditExp[i < 0 ? 0 : i] != '.')
                m_lineEditExp.append(btnStr);
        }
    }
    //  +/_
    else if (btnStr == "+/_")
    {
        if (length > 0 && isNumber(lastStr))
        {
            int i = length - 2;
            for (; i >= 0; i--)
            {
                if (isOperator((QString)m_lineEditExp[i]))
                    break;
                if (m_lineEditExp == "(" || m_lineEditExp[i] == ")")
                    break;
            }
            if (m_lineEditExp[i < 0 ? 0 : i] != "%") //不能对负数取余
                m_lineEditExp.insert(i + 1, "-");
        }
    }
    //+ - * / %
    else
    {
        if (isNumber(lastStr) || lastStr == ")") //数字或者），追加运算符
            m_lineEditExp.append(btnStr);
    }

}

bool NormalCalculator::bracketEqual() const
{
    return m_lineEditExp.count("(") == m_lineEditExp.count(")");
}

bool NormalCalculator::isOperator(const QString& str) const
{
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "%")
        return true;
    else
        return false;
}

bool NormalCalculator::isNumber(const QString& str) const
{
    for (auto val : str)
    {
        if (val == '+' || val == '-' || val == '*' || val == '/' || val == "%" || val == '(' || val == ')' || val == '.')
        {
            return false;
        }
    }
    return true;
}

double NormalCalculator::expressionHandle()
{
    QStack<double> numStack; //数字栈
    QVector<QString> polishExp; //逆波兰表达式
    QStack<QString> opStack; //运算符栈

    //定义运算符优先级
    QMap<QString, int> priority;
    priority["+"] = 1;
    priority["-"] = 1;
    priority["*"] = 2;
    priority["/"] = 2;
    priority["%"] = 2;
    priority["("] = 0;

    int len = m_expression.size();

    for (int i = 0; i < len; i++)
    {
        //如果是"("直接压栈
        if (m_expression[i] == "(")
            opStack.push_back("(");
        //如果是运算符
        else if (isOperator(m_expression[i]))
        {
            QString opStr = m_expression[i];
            //运算符栈为空，直接压栈
            if (opStack.isEmpty())
                opStack.push(opStr);
            //栈不为空，且当前运算符优先级高于栈顶运算符
            else if (priority[opStr] > priority[opStack.top()])
                opStack.push(opStr);
            //栈不为空，当前运算符优先级小于等于栈顶运算符
            else
            {
                while (!opStack.isEmpty())
                {
                    QString tempStr = opStack.pop();
                    polishExp.push_back(tempStr);
                    if (opStack.isEmpty())
                    {
                        opStack.push(opStr);
                        break;
                    }
                    else if (priority[opStr] > priority[opStack.top()])
                    {
                        opStack.push(opStr);
                        break;
                    }
                }
            }
        }
        //如果是")",就将运算符栈"("之后的元素弹出，
        else if (m_expression[i] == ")")
        {
            while (!opStack.isEmpty())
            {
                QString tempStr = opStack.pop();
                if (tempStr == "(")
                    break;
                polishExp.push_back(tempStr);
            }
        }
        else
        {
            polishExp.push_back(m_expression[i]);
        }
    }
    //把其他的运算符弹出栈
    while (!opStack.isEmpty())
    {
        polishExp.push_back(opStack.pop());
    }


    /*for(auto val:polishExp)
    {
        qDebug() << val << " ";
    }*/

    //计算逆波兰表达式
    for (int i = 0; i < polishExp.size(); i++)
    {
        QString& str = polishExp[i];
        //是数字
        if (!isOperator(str))
            numStack.push(str.toDouble());
        else
        {
            double rightNum = numStack.pop();
            double leftNum = numStack.pop();
            switch (str[0].toLatin1())
            {
            case '+':
                numStack.push(leftNum + rightNum);
                break;
            case '-':
                numStack.push(leftNum - rightNum);
                break;
            case '*':
                numStack.push(leftNum * rightNum);
                break;
            case '/':
                if (0 == rightNum)
                {
                    error("The divisor cannot be zero!");
                    numStack.push(0);
                }
                else
                    numStack.push(leftNum / rightNum);
                break;
            case '%':
                numStack.push((int)leftNum % (int)rightNum);
                break;
            default:
                break;
            }

        }
    }
    return numStack.top();

}

void NormalCalculator::error(const QString& str)
{
    QMessageBox::question(this, "warning", str, QMessageBox::Yes);
}

void NormalCalculator::getExpVec()
{
    QString buff;
    bool isNegative = false;

    for (int i = 0; i < m_lineEditExp.size(); i++)
    {

        QString str = (QString)m_lineEditExp[i];

        if (str == "-" && (i == 0 || m_lineEditExp[i - 1] == "(" || isOperator((QString)m_lineEditExp[i - 1])))
        {
            isNegative = true;
        }
        else if (isNumber(str) || str == ".")   //数字小数点
        {
            buff += str;
        }
        else
        {
            if (!buff.isEmpty())
            {
                if (isNegative)
                {
                    buff = "-" + buff;
                    isNegative = false;
                }
                m_expression.push_back(buff);
                buff.clear();
            }
            m_expression.push_back(str);
        }

    }
    //添加最后一个数字到数组
    if (!buff.isEmpty())
    {
        if (isNegative)
            buff = "-" + buff;
        m_expression.push_back(buff);
    }

}