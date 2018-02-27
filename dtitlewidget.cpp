#include "dtitlewidget.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

DTitleWidget::DTitleWidget(QWidget *parent) :
    QWidget(parent),
    m_titleIco(new QLabel()),
    m_titleContent(new QLabel()),
    m_minBtn(new QPushButton()),
    m_maxBtn(new QPushButton()),
    m_closeBtn(new QPushButton()),
    m_strTitleContent("Widget"),
    m_isMax(false),
    m_isPress(false)
{
    initControl();
}

void DTitleWidget::setTitle(const QString &title)
{
    m_titleContent->setText(title);
    m_titleContent->setStyleSheet("QLabel{font-family:Times;\
                                          font-size:16px;\
                                          font-weight:bold;\
                                          color:#00ff00;}");
    m_strTitleContent = title;
}

void DTitleWidget::setIcon(const QString &fileName)
{
    QPixmap pixmap(fileName);
    m_titleIco->setPixmap(pixmap.scaled(SIZE_CONTROL,SIZE_CONTROL));
}

void DTitleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath backPath;
    backPath.setFillRule(Qt::WindingFill);
    backPath.addRoundedRect(QRectF(0, 0, this->width(), this->height()), 0, 0);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(backPath, QBrush(QColor(255, 255, 255)));

    QWidget::paintEvent(event);
}

void DTitleWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit maxWindow();
    return QWidget::mouseDoubleClickEvent(event);
}

void DTitleWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && !m_isMax)
    {
        m_startPoint = event->globalPos();
        m_isPress = true;
    }
    return QWidget::mousePressEvent(event);
}

void DTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPress)
    {
        QPoint offset = event->globalPos() - m_startPoint;
        QPoint parentPos = this->parentWidget()->pos();
        m_startPoint = event->globalPos();
        this->parentWidget()->move(parentPos.x() + offset.x(), parentPos.y() + offset.y());
    }
    return QWidget::mouseMoveEvent(event);
}

void DTitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPress = false;
    return QWidget::mouseReleaseEvent(event);
}

void DTitleWidget::initControl()
{
    this->setIcon(":/images/png/image/ico.png");
    this->setTitle("Title!");
    m_minBtn->setIcon(QIcon(":/images/png/image/min.png"));
    m_maxBtn->setIcon(QIcon(":/images/png/image/normal.png"));
    m_closeBtn->setIcon(QIcon(":/images/png/image/close.png"));

    m_titleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_minBtn->setFixedSize(QSize(SIZE_CONTROL, SIZE_CONTROL));
    m_maxBtn->setFixedSize(QSize(SIZE_CONTROL, SIZE_CONTROL));
    m_closeBtn->setFixedSize(QSize(SIZE_CONTROL, SIZE_CONTROL));
    this->setWindowFlags(Qt::FramelessWindowHint); //
    initLayout();
    initConnect();
}

void DTitleWidget::initLayout()
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_titleIco);
    layout->addWidget(m_titleContent);
    layout->addWidget(m_minBtn);
    layout->addWidget(m_maxBtn);
    layout->addWidget(m_closeBtn);
    this->setFixedHeight(35);
}

void DTitleWidget::initConnect()
{
    connect(m_minBtn, SIGNAL(clicked()), this, SLOT(onMinBtnClicked()));
    connect(m_maxBtn, SIGNAL(clicked()), this, SLOT(onMaxBtnClicked()));
    connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
}

void DTitleWidget::onMinBtnClicked()
{
    emit minWindow();
}

void DTitleWidget::onMaxBtnClicked()
{
    emit maxWindow();
}

void DTitleWidget::onCloseBtnClicked()
{
    emit closeWindow();
}

void DTitleWidget::onChangeBtnIcon(bool max)
{
    if(max)
    {
        m_maxBtn->setIcon(QIcon(":/images/png/image/max.png"));
        m_isMax = true;
    }
    else
    {
        m_maxBtn->setIcon(QIcon(":/images/png/image/normal.png"));
        m_isMax = false;
    }

}
