#include "widget.h"
#include "ui_widget.h"
#include "dtitlewidget.h"
#include <QVBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_titleWidget(new DTitleWidget(this))
{
    ui->setupUi(this);
    init();
}

Widget::~Widget()
{
    qDebug() <<"~Widget()";
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    m_titleWidget->resize(this->width(), 35);
}

void Widget::onCloseWindow()
{
    this->close();
}

void Widget::onMinWindow()
{
    showMinimized();
}

void Widget::onMaxWindow()
{
    if(this->isMaximized())
    {
        showNormal();
        emit isMaxWindow(false);
    }
    else
    {
        showMaximized();
        emit isMaxWindow(true);
    }
}

void Widget::init()
{
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_titleWidget->move(0, 0);
    m_titleWidget->resize(this->width(), 35);
    connect(m_titleWidget, SIGNAL(closeWindow()), this, SLOT(onCloseWindow()));
    connect(m_titleWidget, SIGNAL(minWindow()), this, SLOT(onMinWindow()));
    connect(m_titleWidget, SIGNAL(maxWindow()), this, SLOT(onMaxWindow()));
    connect(this, SIGNAL(isMaxWindow(bool)), m_titleWidget, SLOT(onChangeBtnIcon(bool)));
}

