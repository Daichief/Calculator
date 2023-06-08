#include "mainwindow.h"
#include<QStackedWidget>
#include<QLabel>
#include<QMenuBar>
#include<QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    /*=============================��ʼ��=========================================*/
    m_normalCal = new NormalCalculator(this);
    m_numCovCal = new NumberConver(this);
    this->setWindowIcon(QIcon(":/images/images/calculator3.png"));
    this->setWindowTitle(QStringLiteral("������"));


    /*===========================���ò˵���=========================================*/
    //�����˵�
    QMenuBar* menubar = new QMenuBar(this);
    QMainWindow::setMenuBar(menubar);
    QMenu* menu = menubar->addMenu(QStringLiteral("�˵�"));
    //����Ӳ˵�
    QAction* action_1 = new QAction(QStringLiteral("��׼������"), this);
    QAction* action_2 = new QAction(QStringLiteral("���Ƽ�����"), this);
    menu->addAction(action_1);
    menu->addAction(action_2);
    //���ҳ���л�QStackedWidget�ؼ�
    QStackedWidget* stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    //QWidget* normalCal = new QWidget(this); //��׼������
    QWidget* dataCal = new QWidget(this);   //���ڼ�����
    stackedWidget->addWidget(m_normalCal);
    stackedWidget->addWidget(m_numCovCal);
    stackedWidget->addWidget(dataCal);


    /*================================����ź����===========================================*/
    connect(action_1, &QAction::triggered, [=]() {stackedWidget->setCurrentIndex(0);});
    connect(action_2, &QAction::triggered, [=]() {stackedWidget->setCurrentIndex(1); });

}
