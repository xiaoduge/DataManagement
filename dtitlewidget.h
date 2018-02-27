#ifndef DTITLEWIDGET_H
#define DTITLEWIDGET_H

#include <QWidget>
class QLabel;
class QPushButton;

const int SIZE_CONTROL = 25;

class DTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DTitleWidget(QWidget *parent = 0);

    void setTitle(const QString& title);
    void setIcon(const QString& fileName);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void initControl();
    void initLayout();
    void initConnect();

private slots:
    void onMinBtnClicked();
    void onMaxBtnClicked();
    void onCloseBtnClicked();
    void onChangeBtnIcon(bool max);

signals:
    void closeWindow();
    void minWindow();
    void maxWindow();
    void normalWindow();

private:
    QLabel* m_titleIco;
    QLabel* m_titleContent;
    QPushButton* m_minBtn;
    QPushButton* m_maxBtn;
    QPushButton* m_closeBtn;
    QString m_strTitleContent;
    QPoint m_startPoint;
    bool m_isMax; //记录是否已最大化
    bool m_isPress; //记录鼠标是否已按下
};

#endif // DTITLEWIDGET_H
