#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}
QImage MainWindow :: DDA(int x1, int y1, int x2, int y2, QImage image, int n){
    int dx, dy, count;
    float X, Y, inc_x, inc_y;

    dx=x2-x1;
    dy=y2-y1;

    if(abs(dx)>=abs(dy))
        count = dx;

    else
        count=dy;

    inc_x=dx/(float)count;
    inc_y=dy/(float)count;

    X=x1;
    Y=y1;

    for(int i=0; i<count; i++){
        X+=inc_x;
        Y+=inc_y;

        image=Draw(X,Y,i,image,n);
    }
    return image;
}

QImage MainWindow :: Draw(float X, float Y,int i, QImage image, int n){
    switch(n)
    {
    case 1:image.setPixel(X,Y,value);
           image.setPixel(X,Y-1,value);
           image.setPixel(X+1,Y,value);
           break;
    case 2:if(i%2!=0)
            image.setPixel(X,Y,value);
           break;
    case 3:if(i%5!=0)
            image.setPixel(X,Y,value);
           break;
    case 4:if(i%9==4 || i%9==5 || i%9==7 || i%9==8){
            }
            else if(i%9==5)
                image.setPixel(X,Y,value);
            else
                image.setPixel(X,Y,value);
            break;
        }
    return image;
}

QImage MainWindow :: Preset(QImage image){
    x1=ui->T_x1->toPlainText().toInt();
    y1=ui->T_y1->toPlainText().toInt();
    x2=ui->T_x2->toPlainText().toInt();
    y2=ui->T_y2->toPlainText().toInt();

    value  = qRgb(255,255,255);
    black=qRgb(0,0,0);
    image.fill(black);
    return image;
}

void MainWindow::on_pushButton_clicked()
{
    QImage image(180, 200, QImage :: Format_RGB888);
    image = Preset(image);
    image=DDA(x1,y1,x2,y2,image,1);
    ui->L_thick->setPixmap(QPixmap :: fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    QImage image(180, 200, QImage :: Format_RGB888);
    image = Preset(image);

    image=DDA(x1,y1,x2,y2,image,2);
    ui->L_dashed->setPixmap(QPixmap :: fromImage(image));
}

void MainWindow::on_pushButton_3_clicked()
{
    QImage image(180, 200, QImage :: Format_RGB888);
    image = Preset(image);

    image=DDA(x1,y1,x2,y2,image,3);
    ui->L_dotted->setPixmap(QPixmap :: fromImage(image));
}

void MainWindow::on_pushButton_4_clicked()
{
    QImage image(180, 200, QImage :: Format_RGB888);
    image = Preset(image);

    image=DDA(x1,y1,x2,y2,image,4);
    ui->L_dashdot->setPixmap(QPixmap :: fromImage(image));
}

