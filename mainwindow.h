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

    NormalCalculator* m_normalCal;   //��׼������

    NumberConver* m_numCovCal;       //���Ƽ�����
};

#endif // !__MAINWINDOW_H__

