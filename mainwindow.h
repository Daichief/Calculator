#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "normalcalculator.h"
#include "numberconver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;

    NormalCalculator* m_normalCal;   //标准计算器

    NumberConver* m_numCovCal;       //进制计算器
};

#endif // !__MAINWINDOW_H__

