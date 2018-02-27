#include "widget.h"
#include "ui_widget.h"
#include "dtitlewidget.h"
#include <QVBoxLayout>
#include <QPainter>
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
    m_titleWidget->resize(this->width(), 35);

    QPainter painter(this);
    QPainterPath backPath;
    backPath.setFillRule(Qt::WindingFill);
    backPath.addRoundedRect(QRectF(0, 0, this->width(), this->height()), 5, 5);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(backPath, QBrush(QColor(220, 220, 220)));

    QWidget::paintEvent(event);
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

