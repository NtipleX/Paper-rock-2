#ifndef SIDECHAT_H
#define SIDECHAT_H

#include "ui_SideChat.h"
#include <QWidget>


class A
{
};

namespace Ui {
class SideChat;
}

class SideChat: public QWidget
{
    Q_OBJECT
public:
    Ui::SideChat *ui;
    SideChat();
    QString text;


    ~SideChat();
private:

};
class btnLabel: public QLabel
{
    Q_OBJECT
public:
    btnLabel(SideChat* wd);
    SideChat* wid;
signals:
    void btnLabelclick();
protected:
    bool event(QEvent *myEvent);

};







#endif // SIDECHAT_H
