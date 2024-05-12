#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"polynomial.h"
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_plus_clicked();

    void on_minus_clicked();

    void on_multiply_clicked();

    void on_calculus_clicked();

private:
    Ui::Widget *ui;
    calculator c;
    QString strup;
    QString strdown;

};
#endif //
