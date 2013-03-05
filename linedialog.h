#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>

class LineDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LineDialog(QWidget *parent = 0);
    
signals:
    void lineStyle(Qt::PenStyle);
    void lineCapStyle(Qt::PenCapStyle);
    void polyLineEnabled(bool);
    void lineWidth(int);
public slots:
    
};

#endif // LINEDIALOG_H
