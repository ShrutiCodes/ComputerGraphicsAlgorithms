#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

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

int MainWindow::Sign(float f){
    if(f>0)
        return 1;
    else if(f<0)
        return -1;
    else if(f==0)
        return 0;
}

QImage MainWindow::DDALine(float x1,float y1,float x2,float y2, QImage image){
    int dx, dy, length;
    float X=x1, Y=y1, incx, incy;

    dx=x2-x1;
    dy=y2-y1;

    if(abs(dx)>=abs(dy))
        length=dx;
    else
        length=dy;

    incx=dx/(float)length;
    incy=dy/(float)length;

    for(int i=0; i<length; i++){
        X+=incx;
        Y+=incy;
        image.setPixel(X,Y,qRgb(255,255,255));
    }
    return image;
}

QImage MainWindow :: drawCircle(int xc, int yc, int x, int y, QImage image){
    //For all 8 Octants
    int value=qRgb(255,255,255);

    image.setPixel(xc+x,yc+y,value);
    image.setPixel(xc-x,yc+y,value);
    image.setPixel(xc+x,yc-y,value);
    image.setPixel(xc-x,yc-y,value);
    image.setPixel(xc+y,yc+x,value);
    image.setPixel(xc-y,yc+x,value);
    image.setPixel(xc+y,yc-x,value);
    image.setPixel(xc-y,yc-x,value);

    return image;
}

QImage MainWindow::BresenhamCircle(int xc, int yc, int r, QImage image){
    int x=0, y=r;
    int d=3-2*r;
    image=drawCircle(xc, yc, x, y, image);
    while(y>=x){
        x++;
        if(d>0){
            y--;
            d+=(4*(x-y)+10);
        }
        else
            d+=(4*x+6);
        image=drawCircle(xc, yc, x, y, image);
    }
    return image;
}
QImage MainWindow::DDACircle(int x, int y, int radius, QImage Q){

   float x1,x2,y1,y2,eps,sx,sy;
   int val,i=0;

   x1=radius;
   y1=0;
   sx=x1;
   sy=y1;

   do{
      val=pow(2,i);
      i++;
   }while(val<radius);

   eps = 1/pow(2,i-1);

   do{
       x2 = x1 + y1*eps;
       y2 = y1 - eps*x2;
       Q.setPixel(x+x2,y-y2,qRgb(255,255,255));
       x1=x2;
       y1=y2;
   }while((y1-sy)<eps || (sx-x1)>eps);

   return Q;
}

void MainWindow::on_pushButton_clicked()
{
    x=ui->T_x->toPlainText().toFloat();
    y=ui->T_y->toPlainText().toFloat();
    radius=ui->T_r->toPlainText().toFloat();

    QImage Q(450,350,QImage::Format_RGB888);

    Q=BresenhamCircle(x,y,radius,Q);

    float deg=30*3.141592/180;
    float x1=x-radius*cos(deg),y1=y+radius*sin(deg);
    float x2=x+radius*cos(deg),y2=y+radius*sin(deg);
    float x3=x,y3=y-radius;
    float r2=radius*sin(deg);

    Q=DDALine(x3,y3,x2,y2,Q);
    Q=DDALine(x3,y3,x1,y1,Q);
    Q=DDALine(x1,y1,x2,y2,Q);

    Q=DDACircle(x,y,r2,Q);

    ui->L->setPixmap(QPixmap::fromImage(Q));
}
