#ifndef PROFILEN_H
#define PROFILEN_H

#include <QDialog>

namespace Ui {
class Profilen;
}

class Profilen : public QDialog
{
    Q_OBJECT

public:
    Profilen();
    explicit Profilen(QString,QWidget *parent = nullptr);
    ~Profilen();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Profilen *ui;
};

#endif // PROFILEN_H
