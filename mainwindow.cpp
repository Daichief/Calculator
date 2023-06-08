#include "mainwindow.h"
#include<QStackedWidget>
#include<QLabel>
#include<QMenuBar>
#include<QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    /*=============================初始化=========================================*/
    m_normalCal = new NormalCalculator(this);
    m_numCovCal = new NumberConver(this);
    this->setWindowIcon(QIcon(":/images/images/calculator3.png"));
    this->setWindowTitle(QStringLiteral("计算器"));


    /*===========================设置菜单栏=========================================*/
    //创建菜单
    QMenuBar* menubar = new QMenuBar(this);
    QMainWindow::setMenuBar(menubar);
    QMenu* menu = menubar->addMenu(QStringLiteral("菜单"));
    //添加子菜单
    QAction* action_1 = new QAction(QStringLiteral("标准计算器"), this);
    QAction* action_2 = new QAction(QStringLiteral("进制计算器"), this);
    menu->addAction(action_1);
    menu->addAction(action_2);
    //添加页面切换QStackedWidget控件
    QStackedWidget* stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    //QWidget* normalCal = new QWidget(this); //标准计算器
    QWidget* dataCal = new QWidget(this);   //日期计算器
    stackedWidget->addWidget(m_normalCal);
    stackedWidget->addWidget(m_numCovCal);
    stackedWidget->addWidget(dataCal);


    /*================================添加信号与槽===========================================*/
    connect(action_1, &QAction::triggered, [=]() {stackedWidget->setCurrentIndex(0);});
    connect(action_2, &QAction::triggered, [=]() {stackedWidget->setCurrentIndex(1); });

}
