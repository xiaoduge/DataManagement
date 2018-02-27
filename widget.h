#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class DTitleWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void onCloseWindow();
    void onMinWindow();
    void onMaxWindow();

private:
    void init();

signals:
    void isMaxWindow(bool);

private:
    Ui::Widget *ui;
    DTitleWidget* m_titleWidget;
};

#endif // WIDGET_H
