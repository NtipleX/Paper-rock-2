#include "profilen.h"
#include "ui_profilen.h"
#include <processthreadsapi.h>
Profilen::Profilen()
{

}
Profilen::Profilen(QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profilen)
{
    ui->setupUi(this);
    QPixmap px("Resources\\avatar.png");
    px.scaled(ui->photo->size());
    ui->photo->setPixmap(px);
    setWindowFlags( Qt::CustomizeWindowHint );

    srand(time(NULL));
    ui->label->setText("<html><head/><body><p><span style=\" font-size:7pt; text-decoration: underline;\">Кількість входів в акаунт: "+QString::number(rand()%25+5)+"</span></p></body></html>");
    ui->label_2->setText("<html><head/><body><p><span style=\" font-size:7pt; text-decoration: underline;\">Остання активність: "+QString::number(rand()%25)+" хв"+"</span></p></body></html>");

    ui->label_3->setText("<html><head/><body><p><span style=\" font-size:7pt; text-decoration: underline;\">Зіграно ігор: "+QString::number(rand()%48)+"</span></p></body></html>");
    ui->label_4->setText("<html><head/><body><p><span style=\" font-size:7pt; text-decoration: underline;\">Із них перемог: "+QString::number(rand()%30+7)+"</span></p></body></html>");
    ui->label_5->setText("<html><head/><body><p><span style=\" font-size:7pt; text-decoration: underline;\">Зіграно раундів в пат: "+QString::number(rand()%13)+"</span></p></body></html>");
    ui->label_6->setText("<html><head/><body><p><span style=\" font-size:7pt; text-decoration: underline;\">Повідомлень в чаті: "+QString::number(rand()%8)+"</span></p></body></html>");
    /*
    ui->label->setText(ui->label->text()+" "+QString::number(rand()%25+5));
    ui->label_2->setText(ui->label_2->text()+" "+QString::number(rand()%25)+" хв");
    ui->label_3->setText(ui->label_3->text()+" "+QString::number(rand()%48));
    ui->label_4->setText(ui->label_4->text()+" "+QString::number(rand()%30+7));
    ui->label_5->setText(ui->label_5->text()+" "+QString::number(rand()%13));
    ui->label_6->setText(ui->label_6->text()+" "+QString::number(rand()%8));
    */
    ui->name->setText(name);

}

Profilen::~Profilen()
{
    delete ui;
}

void Profilen::on_pushButton_2_clicked()
{
    this->hide();
}

void Profilen::on_pushButton_clicked()
{
    TerminateProcess(NULL,0);
}
