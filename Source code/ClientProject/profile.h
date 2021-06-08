#ifndef PROFILE_H
#define PROFILE_H



#include <QWidget>
#include "ui_profile.h"

namespace Ui {
class Profile;
}
class Profile: public QWidget
{
    Q_OBJECT
public:
    Profile();
    Ui::Profile* ui;
    ~Profile();
};
#endif // PROFILE_H
