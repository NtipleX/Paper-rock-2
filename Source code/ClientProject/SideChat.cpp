#include <SideChat.h>
#include <Qt>


SideChat::SideChat():
ui(new Ui::SideChat),text("")
{
    ui->setupUi(this);
    this->setMinimumSize(1,1);
    this->resize(100,400);
    QPixmap px;
    px=px.scaled(ui->sendbtn->size(),Qt::KeepAspectRatio);
    px.load("Resources/send.png");
    px=px.scaled(ui->sendbtn->size(),Qt::KeepAspectRatio);
    ui->sendbtn->setPixmap(px);

    px.load("Resources/emote.png");
    px=px.scaled(ui->emote->size(),Qt::KeepAspectRatio);
    ui->emote->setPixmap(px);
    px=px.scaled(ui->background->size(),Qt::KeepAspectRatio);
    btnLabel* l=new btnLabel(this);
    l->setPixmap(ui->sendbtn->pixmap());
    l->setGeometry(ui->sendbtn->geometry());
    ui->sendbtn->hide();
    l->setParent(this);
    l->show();
    ui->chat->setAlignment(Qt::AlignBottom);
    this->show();
}

SideChat::~SideChat()
{

}

btnLabel::btnLabel(SideChat* wd):wid(wd){}

void btnLabelclick()
{

}

bool btnLabel::event(QEvent *myEvent){
    {
        switch(myEvent->type())
        {
            case(QEvent :: MouseButtonRelease):   // Identify Mouse press Event
            {
                emit btnLabelclick();
                //wid->ui->chat->setText(wid->ui->chat->text()+"\n"+"You: "+wid->ui->input->text());
                wid->text=wid->ui->input->text();
                wid->ui->input->clear();
                break;
            }
        }
        return QWidget::event(myEvent);
    }
}
